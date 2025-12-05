/*
 * Wolfi Breakout
 *
 * Copyright (c) 2021 Wolfgang Schwendtbauer. All rights reserved.
 */

// AST Utilities includes
#include <AstuECS.h>

class CBallComponent : public astu::EntityComponent {
public:
  float maxSpeed;

  /**
   * Constructor.
   */
  CBallComponent(float maxSpeed = 0.1f) : maxSpeed(maxSpeed) {
    // Intentionally left empty.
  }

  // Inherited via EntityComponent
  virtual std::shared_ptr<EntityComponent> Clone() override {
    // Create copy using copy-constructor.
    return std::make_shared<CBallComponent>(*this);
  }
};
