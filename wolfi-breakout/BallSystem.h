/*
 * Wolfi Breakout
 * 
 * Copyright (c) 2021 Wolfgang Schwendtbauer. All rights reserved.
 */

#pragma once

// loacl includes
#include "GameEvent.h"

// AST Utilities includes
#include <AstuECS.h>
#include <AstuInput.h>
#include <AstuSuite2D.h>
#include <Math/Random.h>

class BallSystem 
  : public astu::BaseService
  , private astu::IteratingEntitySystem
  , private astu2d::CollisionListener
  , private astu::SignalEmitter<GameEvent>
  , private astu::TimeClient
{
public:

  // Constructor.
  BallSystem(int updatePriority = astu::Priority::Normal);

private:
  // The family of entities this system processes
  static const astu::EntityFamily FAMILY;

  // The action controlling the shoting of the ball
  std::shared_ptr<astu::ActionBinding> tiltBallAction;

  // Should the ball be ejected on the next update
  float lastBallTilt;
  bool tiltBall;
  bool allowTilt;

  void HandleCollision(astu::Entity& ball, astu::Entity& other);

  // Inherited via BaseService
  virtual void OnStartup() override;
  virtual void OnShutdown() override;

  // Inherited via IteratingEntitySystem
  virtual void ProcessEntity(astu::Entity& entity) override;
  
  // Inherited via CollisionListener
  virtual bool OnCollision(astu::Entity& entityA, astu::Entity& entityB) override;
};