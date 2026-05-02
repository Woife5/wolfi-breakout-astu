/*
 * Wolfi Breakout
 *
 * Copyright (c) 2021 Wolfgang Schwendtbauer. All rights reserved.
 */

// Local includes
#include "BrickSystem.h"
#include "BrickInit.h"
#include "CBrickComponent.h"

// AST Utilities includes
#include <AstuSuite2D.h>

using namespace astu;
using namespace astu2d;

BrickSystem::BrickSystem()
    : BaseService("BrickSystem")
{
    // Intentionally left empty.
}

void BrickSystem::OnStartup()
{
    ASTU_SERVICE(BrickEventService).AddListener(*this);
}

void BrickSystem::OnShutdown()
{
    ASTU_SERVICE(BrickEventService).RemoveListener(*this);
}

bool BrickSystem::OnSignal(const BrickEvent& signal)
{
    switch (signal.type) {
    case BrickEvent::Type::Hit:
        if (signal.brick != nullptr) {
            HandleHit(*signal.brick);
        }
        break;
    }
    return false;
}

void BrickSystem::HandleHit(Entity& brick)
{
    if (!brick.HasComponent<CBrickComponent>()) {
        return;
    }

    auto& brickComp = brick.GetComponent<CBrickComponent>();
    brickComp.hits += 1;

    EmitSignal(GameEvent::CreateScoreUpdate(1));

    int remaining = brickComp.health - brickComp.hits;

    if (remaining <= 0) {
        EmitSignal(GameEvent(GameEvent::Type::BrickDestroyed,
            brick.GetComponent<CPose>().transform.GetTranslation()));
        ASTU_SERVICE(EntityService).RemoveEntity(brick);
        return;
    }

    // Recolor the existing brick in place rather than respawning it.
    ApplyBrickColor(brick, remaining);
}
