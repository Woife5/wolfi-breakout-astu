/*
 * Wolfi Breakout
 * 
 * Copyright (c) 2021 Wolfgang Schwendtbauer. All rights reserved.
 */

#pragma once

// AST Utilities includes
#include <AstuGraphics.h>
#include <AstuInput.h>

/////////////////////////////////////////////////
/////// General constants
/////////////////////////////////////////////////
#define VIEW_WIDTH                  16.0f
#define VIEW_HEIGHT                 9.0f
#define BOUNDARY_THICKNESS          0.5f
#define BACKGROUND_COLOR            astu::RalColors::TrafficBlack
#define BOUNDARY_COLOR              astu::RalColors::TrafficGreen
#define MOUSE_CONTROL               false
#define DEBUG                       false

/////////////////////////////////////////////////
/////// Game constants
/////////////////////////////////////////////////
#define BALL_TILT_TIMEOUT           10.0f
#define BALL_RADIUS                 0.15f
#define BALL_INITIAL_SPEED          0.5f
#define BALL_MAX_SPEED              3.0f
#define BALL_COLOR                  astu::RalColors::TrafficWhite
#define PADDLE_COLOR                astu::RalColors::TrafficWhite
#define PADDLE_WIDTH                1.7f
#define PADDLE_HEIGHT               0.2f
#define PADDLE_SPEED                0.1f
#define PADDLE_START_X              0.0f
#define PADDLE_START_Y              4.1f

#define BRICK_WIDTH                 0.9f
#define BRICK_HEIGHT                0.4f
#define BRICK_3_COLOR               astu::RalColors::TrafficRed
#define BRICK_2_COLOR               astu::RalColors::TrafficYellow
#define BRICK_1_COLOR               astu::RalColors::TrafficGreen

/////////////////////////////////////////////////
/////// Physics constants
/////////////////////////////////////////////////
#define GRAVITY                     astu::Vector2f(0.0, 0.0f)
#define GENERAL_RESTITUTION         1.0f
#define GENERAL_FRICTION            0.0f

/////////////////////////////////////////////////
/////// Constants for game entities
/////////////////////////////////////////////////
#define TEST_ENTITY_SIZE            1.0f
#define TEST_ENTITY_COLOR           RalColors::TrafficOrange
