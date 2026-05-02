/*
 * Wolfi Breakout
 *
 * Copyright (c) 2021 Wolfgang Schwendtbauer. All rights reserved.
 */

// Local includes
#include "BallSystem.h"
#include "CBallComponent.h"
#include "CBrickComponent.h"
#include "CLethalBoundaryComponent.h"

// AST Utilities includes
#include <AstuSuite2D.h>
#include <Math/Random.h>

#include "Constants.h"

using namespace astu2d;
using namespace astu;
using namespace std;

const EntityFamily BallSystem::FAMILY = EntityFamily::Create<CBallComponent>();

BallSystem::BallSystem(int updatePriority)
    : BaseService("BallSystem")
    , IteratingEntitySystem(FAMILY, updatePriority)
{
    // Intentionally left empty.
}

void BallSystem::OnStartup()
{
    tiltBallAction = ASTU_SERVICE(InputMappingService).BindAction("TiltBall");
    tiltBallAction->SetDelegate([this](ActionBinding& binding) {
        if (binding.IsPressed()) {
            tiltBall = true;
        }
    });
    tiltBall = false;
    lastBallTilt = 0.0f;
    allowTilt = true;
}

void BallSystem::OnShutdown()
{
    ASTU_SERVICE(InputMappingService).RemoveActionBinding(tiltBallAction);
    tiltBallAction = nullptr;
}

void BallSystem::ProcessEntity(Entity& entity)
{
    auto& body = entity.GetComponent<CBody>();

    // Sometimes the ball gets stuck in a vertical or horizontal position when it
    // hits an object with too little speed If this happens vertically, its no
    // problem since the ball will come back to the ground eventually If it
    // happens horizonatlly, the ball needs to be given a litte push in order to
    // keep playing the game
    if (abs(body.GetLinearVelocity().y) < 0.1f) {
        lastBallTilt = GetAbsoluteTime();
        allowTilt = false;
        std::cout << "Auto-tilt has been activated!" << std::endl;

        auto& pose = entity.GetComponent<CPose>();
        float yPos = pose.transform.GetTranslationY();

        if (yPos >= 0) {
            body.ApplyForce(Vector2f(0.0f, -5.0f));
        } else {
            body.ApplyForce(Vector2f(0.0f, 5.0f));
        }
    }

    if (!allowTilt && GetAbsoluteTime() > lastBallTilt + BALL_TILT_TIMEOUT) {
        allowTilt = true;
        tiltBall = false;
        std::cout << "Tilting is allowed again" << std::endl;
    }

    if (allowTilt && tiltBall) {
        lastBallTilt = GetAbsoluteTime();
        allowTilt = false;
        tiltBall = false;

        // Get a random force to apply to the ball.
        float forceX = Random::GetInstance().NextFloat(-4.0f, 4.0f);
        float forceY = Random::GetInstance().NextFloat(4.0f, 6.0f);

        std::cout << "applied force: " << forceX << ", " << forceY << std::endl;

        body.ApplyForce(Vector2f(forceX, forceY));
    }
}

void BallSystem::HandleCollision(Entity& ball, Entity& other)
{
    if (other.HasComponent<CBrickComponent>()) {

        auto& brick = other.GetComponent<CBrickComponent>();
        brick.hits += 1;
        EmitSignal(GameEvent::CreateScoreUpdate(1));

        // Destroy Brick
        GetEntityService().RemoveEntity(other);

        if (brick.hits >= brick.health) {
            EmitSignal(
                GameEvent(GameEvent::Type::BrickDestroyed,
                    other.GetComponent<CPose>().transform.GetTranslation()));
            return;
        }

        // Add a new brick with a different color
        // This is done because i cannot figure out how to change the color of an
        // entity Ideally i would just change the bricks color and only remove it
        // once it is completley destroyed
        auto& position = other.GetComponent<CPose>().transform.GetTranslation();

        int health = brick.health - brick.hits;
        auto entity = ASTU_SERVICE(EntityFactoryService).CreateEntity(to_string(health) + "HBrick");
        auto& pose = entity->GetComponent<CPose>();
        pose.transform.SetTranslation(position.x, position.y);

        GetEntityService().AddEntity(entity);

    } else if (other.HasComponent<CLethalBoundaryComponent>()) {
        const auto& pos = ball.GetComponent<CPose>().transform.GetTranslation();
        EmitSignal(GameEvent(GameEvent::Type::BallDestroyed, pos));
        GetEntityService().RemoveEntity(ball);
    }
}

bool BallSystem::OnCollision(Entity& entityA, Entity& entityB)
{
    if (entityA.HasComponent<CBallComponent>()) {
        HandleCollision(entityA, entityB);
    } else if (entityB.HasComponent<CBallComponent>()) {
        HandleCollision(entityB, entityA);
    }
    return false;
}
