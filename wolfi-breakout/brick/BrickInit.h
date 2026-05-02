/*
 * Wolfi Breakout
 *
 * Copyright (c) 2021 Wolfgang Schwendtbauer. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <AstuECS.h>

/**
 * Initializes a freshly spawned brick with a starting amount of health and
 * applies the matching color to its scene representation.
 *
 * The brick is expected to already have a CBrickComponent and a CScene with
 * a Polyline spatial.
 *
 * @param brick     the brick entity
 * @param health    the initial (max) health of the brick
 */
void InitBrick(astu::Entity& brick, int health);

/**
 * Applies the color matching the given remaining health to a brick's scene
 * representation. Used both during initialization and when re-coloring a
 * brick after it has been hit.
 *
 * @param brick             the brick entity
 * @param remainingHealth   the brick's remaining health (must be >= 1)
 */
void ApplyBrickColor(astu::Entity& brick, int remainingHealth);
