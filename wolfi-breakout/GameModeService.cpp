/*
 * Wolfi Breakout
 *
 * Copyright (c) 2021 Wolfgang Schwendtbauer. All rights reserved.
 */

// Local includes
#include "GameModeService.h"
#include "brick/BrickInit.h"
#include "Constants.h"
#include "LevelData.h"

using namespace astu2d;
using namespace astu;
using namespace std;

GameModeService::GameModeService()
    : BaseService("Game Mode Service")
{
    // Intentionally left empty.
}

void GameModeService::OnStartup()
{
    // Configure camera.
    GetCamera().ShowFitting(VIEW_WIDTH, VIEW_HEIGHT);

    // Configure game mode.
    score = 0;
    numLives = 3;
    levelId = 0;

    // Load first level.
    LoadLevel(levelId);
}

void GameModeService::OnShutdown()
{
    ASTU_SERVICE(EntityService).RemoveAll();
}

shared_ptr<Entity> GameModeService::AddEntity(const string& proto, float x, float y, float phiDeg)
{
    auto entity = ASTU_SERVICE(EntityFactoryService).CreateEntity(proto);
    auto& pose = entity->GetComponent<CPose>();
    pose.transform.SetTranslation(x, y);
    if (phiDeg != 0) {
        pose.transform.SetRotationDeg(phiDeg);
    }

    ASTU_SERVICE(EntityService).AddEntity(entity);
    return entity;
}

void GameModeService::LoadLevel(int level)
{
    ASTU_SERVICE(EntityService).RemoveAll();

    FireSignal(GameEvent::Type::ResetBall);

    // Add world boundaries.
    float vRadius = VIEW_HEIGHT / 2 + BOUNDARY_THICKNESS / 2;
    float hRadius = VIEW_WIDTH / 2 + BOUNDARY_THICKNESS / 2;
    AddEntity("HBoundary", 0, -vRadius);
    AddEntity("BottomBoundary", 0, vRadius);
    AddEntity("VBoundary", -hRadius, 0);
    AddEntity("VBoundary", hRadius, 0);

    // Add paddle and ball.
    AddEntity("Paddle", PADDLE_START_X, PADDLE_START_Y);
    AddEntity("BallIndicator", PADDLE_START_X, PADDLE_START_Y - BALL_RADIUS * 2);
    numBalls = 1;

    const auto& layout = levels[level];
    numBricks = 0;

    for (int i = 0; i < layout.size(); i++) {
        for (int j = 0; j < layout[i].size(); j++) {

            char tile = layout[i][j];

            if (tileToHp.count(tile)) {
                float x = -7.0f + j;
                float y = -3.5f + (i / 2.0f);

                auto entity = AddEntity("RegularBrick", x, y);
                InitBrick(*entity, tileToHp[tile]);
                numBricks++;
            }
        }
    }
}

bool GameModeService::OnSignal(const GameEvent& signal)
{
    switch (signal.type) {

    case GameEvent::Type::BallDestroyed:
        numBalls -= 1;

        if (numBalls <= 0) {
            EmitSignal(GameEvent::CreateLifeUpdate(-1));
        }
        break;

    case GameEvent::Type::BrickDestroyed:
        numBricks -= 1;

        if (numBricks <= 0) {
            LoadLevel(++levelId);
        }
        break;

    case GameEvent::Type::LifeUpdate:
        numLives += signal.intValue;

        if (numLives <= 0) {
            std::cout << "Game over" << std::endl;
            std::cout << "Final score: " << score << std::endl;
            break;
        }

        // Reset ball
        FireSignal(GameEvent::Type::ResetBall);
        AddEntity("BallIndicator", PADDLE_START_X, PADDLE_START_Y - BALL_RADIUS * 2);

        break;

    case GameEvent::Type::ScoreUpdate:
        score += signal.intValue;
        break;

    case GameEvent::Type::BallFired:
        // Make the ball start at the correct position.
        AddEntity("Ball", signal.position.x, signal.position.y);
        break;

    case GameEvent::Type::ResetBall:
        break;
    }

    return false;
}
