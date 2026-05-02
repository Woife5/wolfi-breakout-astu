/*
 * Wolfi Breakout
 *
 * Copyright (c) 2021 Wolfgang Schwendtbauer. All rights reserved.
 */

// Local includes
#include "BrickInit.h"
#include "CBrickComponent.h"
#include "../Constants.h"

// AST Utilities includes
#include <AstuSuite2D.h>

// C++ Standard Library includes
#include <array>

using namespace astu;
using namespace astu2d;

namespace {

// Lookup table mapping remaining health (1-based) to brick color.
// Index = remainingHealth - 1.
const std::array<Color4f, 3> brickColorByHp = {
    BRICK_1_COLOR,
    BRICK_2_COLOR,
    BRICK_3_COLOR,
};

const Color4f& ColorForHealth(int remainingHealth)
{
    int idx = remainingHealth - 1;
    if (idx < 0) {
        idx = 0;
    } else if (idx >= static_cast<int>(brickColorByHp.size())) {
        idx = static_cast<int>(brickColorByHp.size()) - 1;
    }
    return brickColorByHp[idx];
}

} // anonymous namespace

void ApplyBrickColor(Entity& brick, int remainingHealth)
{
    auto& scene = brick.GetComponent<CScene>();
    auto polyline = std::dynamic_pointer_cast<Polyline>(scene.spatial);
    if (polyline) {
        polyline->SetColor(ColorForHealth(remainingHealth));
    }
}

void InitBrick(Entity& brick, int health)
{
    auto& brickComp = brick.GetComponent<CBrickComponent>();
    brickComp.health = health;
    brickComp.hits = 0;
    ApplyBrickColor(brick, health);
}
