/*
 * Wolfi Breakout
 * 
 * Copyright (c) 2021 Wolfgang Schwendtbauer. All rights reserved.
 */

#pragma once

// AST-Utilities includes
#include <AstuServices.h>
#include <AstuECS.h>
#include <AstuGraphics.h>

class EntityPrototypeService : public astu::BaseService
{
public:

	// Constructor.
	EntityPrototypeService(bool debug = false);

private:
  // Whether debug mode is activated.
  bool debug;

  // Inherited via BaseService
  virtual void OnStartup() override;
  virtual void OnShutdown() override;

  std::shared_ptr<astu::Entity> CreateBoundary(float w, float h, bool lethal = false);
  std::shared_ptr<astu::Entity> CreatePaddle();
  std::shared_ptr<astu::Entity> CreateBall();
  std::shared_ptr<astu::Entity> CreateBallIndicator();
  std::shared_ptr<astu::Entity> CreateBrick(int hits = 1, astu::Color4f color = astu::RalColors::TrafficWhite);

};