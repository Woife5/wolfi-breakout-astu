/*
 * Wolfi Breakout
 * 
 * Copyright (c) 2021 Wolfgang Schwendtbauer. All rights reserved.
 */

#pragma once

// local includes
#include "GameEvent.h"

// AST Utilities includes
#include <AstuECS.h>
#include <AstuInput.h>
#include <AstuSuite2D.h>

class PaddleSystem 
    : public astu::BaseService
    , private astu::IteratingEntitySystem
    , private astu2d::CollisionListener
    , private astu::SignalListener<GameEvent>
	, private astu::SignalEmitter<GameEvent>
{
public:

    // Constructor.
    PaddleSystem(int updatePriority = astu::Priority::Normal);

private:
    // The family of entities this system processes
    static const astu::EntityFamily FAMILY;

    // The axis binding for controlling the paddle.
    std::shared_ptr<astu::AxisBinding> paddleAxis;

    // The action controlling the shoting of the ball
    std::shared_ptr<astu::ActionBinding> fireBallAction;

    // Should the ball be ejected on the next update
    bool initialBallFired;
    bool fireInitialBall;

    // Main paddle position
    float mainPaddlePositionX;

    void HandleCollision(astu::Entity& paddle, astu::Entity& other);

    // Inherited via BaseService
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    // Inherited via IteratingEntitySystem
    virtual void ProcessEntity(astu::Entity& entity) override;

    // Inherited via CollisionListener
    virtual bool OnCollision(astu::Entity& entityA, astu::Entity& entityB) override;

    // Inherited via private astu::SignalListener<GameEvent>
    virtual bool OnSignal(const GameEvent & signal) override;
};