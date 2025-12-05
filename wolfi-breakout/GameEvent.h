/*
 * Wolfi Breakout
 *
 * Copyright (c) 2021 Wolfgang Schwendtbauer. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <AstuMath.h>
#include <AstuServices.h>

/**
 * A signal which represents a game events.
 */
class GameEvent {
public:
  /** The various types of game events. */
  enum class Type {
    BallDestroyed,
    BrickDestroyed,
    LifeUpdate,
    ScoreUpdate,
    BallFired,
    ResetBall
  };

  /** The type of this game event. */
  Type type;

  /** The location where the game event has occurred. */
  astu::Vector2f position;

  /** Integer value required for some game events. */
  int intValue;

  /**
   * Constructor.
   *
   * @param t the type of this event
   * @param p the position of this event
   */
  GameEvent(Type t, const astu::Vector2f &p = astu::Vector2f::Zero)
      : type(t), position(p) {
    // Intentionally left empty.
  }

  static GameEvent CreateLifeUpdate(int numLifes) {
    GameEvent result = GameEvent(Type::LifeUpdate);
    result.intValue = numLifes;
    return result;
  }

  static GameEvent CreateScoreUpdate(int score) {
    GameEvent result = GameEvent(Type::ScoreUpdate);
    result.intValue = score;
    return result;
  }
};

using GameEventService = astu::SignalService<GameEvent>;
