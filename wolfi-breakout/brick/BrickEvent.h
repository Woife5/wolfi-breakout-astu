/*
 * Wolfi Breakout
 *
 * Copyright (c) 2021 Wolfgang Schwendtbauer. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <AstuECS.h>
#include <AstuServices.h>

/**
 * A signal which represents brick-related events.
 *
 * Carries a raw pointer to the brick entity. The pointer is only valid for
 * the duration of the synchronous signal dispatch.
 */
class BrickEvent {
public:
    /** The various types of brick events. */
    enum class Type {
        Hit,
    };

    /** The type of this brick event. */
    Type type;

    /** The brick entity this event refers to. */
    astu::Entity* brick;
};

using BrickEventService = astu::SignalService<BrickEvent>;
