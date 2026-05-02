/*
 * Wolfi Breakout
 *
 * Copyright (c) 2021 Wolfgang Schwendtbauer. All rights reserved.
 */

// AST Utilities includes
#include <AstuECS.h>

class CBrickComponent : public astu::EntityComponent {
public:
  // Amount of times the brick has been hit.
  int hits;
  // Amount of times the brick can be hit before it is destroyed.
  int health;

  /**
   * Constructor.
   */
  CBrickComponent(int health = 1) : hits(0), health(health) {
    // Intentionally left empty.
  }

  // Inherited via EntityComponent
  virtual std::shared_ptr<EntityComponent> Clone() override {
    // Create copy using copy-constructor.
    return std::make_shared<CBrickComponent>(*this);
  }
};
