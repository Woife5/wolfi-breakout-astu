/*
 * Wolfi Breakout
 *
 * Copyright (c) 2021 Wolfgang Schwendtbauer. All rights reserved.
 */

// Local includes
#include "PaddleSystem.h"
#include "CBallComponent.h"
#include "CPaddleComponent.h"
#include "Constants.h"

// AST Utilities includes
#include <AstuSuite2D.h>

using namespace astu2d;
using namespace astu;
using namespace std;

// add types of entity components to the family e.g.,
// EntityFamily::Create<astu2d::CPose, astu2d::CBody>();

const EntityFamily PaddleSystem::FAMILY = EntityFamily::Create<CPaddleComponent>();

PaddleSystem::PaddleSystem(int updatePriority)
    : BaseService("PaddleSystem")
    , IteratingEntitySystem(FAMILY, updatePriority)
{
    // Intentionally left empty.
}

void PaddleSystem::OnStartup()
{
    paddleAxis = ASTU_SERVICE(InputMappingService).BindAxis("Paddle");
    fireBallAction = ASTU_SERVICE(InputMappingService).BindAction("FireBall");
    fireBallAction->SetDelegate([this](ActionBinding& binding) {
        if (binding.IsPressed()) {
            fireInitialBall = true;
        }
    });
    fireInitialBall = false;
    initialBallFired = false;
}

void PaddleSystem::OnShutdown()
{
    ASTU_SERVICE(InputMappingService).RemoveAxisBinding(paddleAxis);
    paddleAxis = nullptr;
    ASTU_SERVICE(InputMappingService).RemoveActionBinding(fireBallAction);
    fireBallAction = nullptr;
}

void PaddleSystem::ProcessEntity(Entity& entity)
{
    // Get body component of the paddle.
    auto& paddle = entity.GetComponent<CPaddleComponent>();
    auto& pose = entity.GetComponent<CPose>();

    if (!initialBallFired && paddle.maxSpeed == -1.0f) {
        // If the initial ball should be fired, do so now.
        if (fireInitialBall) {
            initialBallFired = true;
            // Get the ball component.
            EmitSignal(GameEvent(GameEvent::Type::BallFired, pose.transform.GetTranslation()));

            // Remove the dummy ball entity.
            GetEntityService().RemoveEntity(entity);

            fireInitialBall = false;

        } else {
            // If the ball is not fired, update the ball position.
            pose.transform.SetTranslationX(mainPaddlePositionX);
        }
        return;
    }

    float paddleForce = paddleAxis->GetValue() * paddle.maxSpeed;

    // Apply force to the paddle.
    float oldPos = pose.transform.GetTranslationX();

    // Check if the paddle is out of bounds.
    if (oldPos + paddleForce > paddle.maxX) {
        paddleForce = paddle.maxX - oldPos;
    } else if (oldPos + paddleForce < paddle.minX) {
        paddleForce = paddle.minX - oldPos;
    }
    pose.transform.SetTranslationX(oldPos + paddleForce);
    mainPaddlePositionX = pose.transform.GetTranslationX();
}

bool PaddleSystem::OnCollision(Entity& entityA, Entity& entityB)
{
    if (entityA.HasComponent<CPaddleComponent>()) {
        HandleCollision(entityA, entityB);
    } else if (entityB.HasComponent<CPaddleComponent>()) {
        HandleCollision(entityB, entityA);
    }
    return false;
}

void PaddleSystem::HandleCollision(Entity& paddle, Entity& other)
{
    if (other.HasComponent<CBallComponent>()) {
        // Handle collision between ball and paddle.
        auto& paddlePose = paddle.GetComponent<CPose>();
        auto& ballPose = other.GetComponent<CPose>();
        auto& ballBody = other.GetComponent<CBody>();

        // Calculate the offset in X-axis between the paddle and the ball.
        float offset = paddlePose.transform.GetTranslationX() - ballPose.transform.GetTranslationX();
        // Normalize offset
        offset /= PADDLE_WIDTH / 2;

        // Calculate the new ball velocity.
        Vector2f velocity = ballBody.GetLinearVelocity();
        float speed = velocity.Length();
        velocity.Normalize();
        velocity.x = -offset;
        velocity.SetLength(speed);

        // Set new ball velocity
        ballBody.SetLinearVelocity(velocity);
    }
}

bool PaddleSystem::OnSignal(const GameEvent& signal)
{
    switch (signal.type) {

    case GameEvent::Type::ResetBall:
        initialBallFired = false;
        fireInitialBall = false;
        break;

    default:
        break;
    }

    return false;
}
