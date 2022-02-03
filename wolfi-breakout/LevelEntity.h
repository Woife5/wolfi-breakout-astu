/*
 * Wolfi Breakout
 * 
 * Copyright (c) 2021 Wolfgang Schwendtbauer. All rights reserved.
 */

#pragma once

#include <string.h>
#include <AstuMath.h>

/**
 * A signal which represents a game events.
 */
class LevelEntity {
public:

    /** The location of the level entity. */
    astu::Vector2f position;

    /** Prototype String for the entity. */
    std::string protoString;

    /**
     * Constructor.
     * 
     * @param t the type of this event
     * @param p the position of this event
     */
    LevelEntity(std::string proto, const astu::Vector2f& p = astu::Vector2f::Zero)
        : protoString(proto), position(p)
    {
        // Intentionally left empty.
    }

    static LevelEntity createOneHitBrick(const astu::Vector2f& p) {
        LevelEntity result = LevelEntity("1HBrick", p);
        return result;
    }

    static LevelEntity createTwoHitBrick(const astu::Vector2f& p) {
        return LevelEntity("2HBrick", p);
    }

    static LevelEntity createThreeHitBrick(const astu::Vector2f& p) {
        return LevelEntity("3HBrick", p);
    }
};
