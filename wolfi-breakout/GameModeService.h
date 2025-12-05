/*
 * Wolfi Breakout
 *
 * Copyright (c) 2021 Wolfgang Schwendtbauer. All rights reserved.
 */

#pragma once

// local includes
#include "GameEvent.h"

// AST-Utilities includes
#include <AstuECS.h>
#include <AstuServices.h>
#include <AstuSuite2D.h>

class GameModeService : public astu::BaseService,
                        private astu2d::CameraClient,
                        private astu::SignalListener<GameEvent>,
                        private astu::SignalEmitter<GameEvent> {
public:
  /**
   * Constructor.
   */
  GameModeService();

private:
  // Game variables and constants
  int numLives;
  int numBricks;
  int numBalls;
  int levelId;
  int score;

  /**
   * Adds an entity to the game world.
   *
   * @param proto     the name of the entity prototype
   * @param x         the x-coordinate of the spawn point
   * @param y         the y-coordinate of the spawn point
   * @param phiDeg    the orientation angle in degrees
   * @return the newly added entity
   */
  std::shared_ptr<astu::Entity> AddEntity(const std::string &proto, float x,
                                          float y, float phiDeg = 0);

  void LoadLevel(int level);

  // Inherited via BaseService
  virtual void OnStartup() override;
  virtual void OnShutdown() override;

  // Inherited via private astu::SignalListener<GameEvent>
  virtual bool OnSignal(const GameEvent &signal) override;
};
