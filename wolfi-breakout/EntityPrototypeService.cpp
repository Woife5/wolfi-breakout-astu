/*
 * Wolfi Breakout
 *
 * Copyright (c) 2021 Wolfgang Schwendtbauer. All rights reserved.
 */

// Local includes
#include "EntityPrototypeService.h"
#include "CBallComponent.h"
#include "brick/CBrickComponent.h"
#include "CLethalBoundaryComponent.h"
#include "CPaddleComponent.h"
#include "Constants.h"

// AST-Utilities includes
#include <AstuSuite2D.h>

using namespace astu2d;
using namespace astu;
using namespace std;

#define PADDLE_CATEGORY 0x0001
#define BALL_CATEGORY 0x0002
#define BRICK_CATEGORY 0x0004
#define BOUNDARY_CATEGORY 0x0008

EntityPrototypeService::EntityPrototypeService(bool debug)
    : BaseService("Entity Prototype Service"), debug(debug) {
  // Intentionally left empty.
}

void EntityPrototypeService::OnStartup() {
  // Create and register entity prototypes.
  auto &entityFactory = ASTU_SERVICE(EntityFactoryService);

  // Register boundary entity prototypes.
  entityFactory.RegisterPrototype(
      "HBoundary", CreateBoundary(VIEW_WIDTH, BOUNDARY_THICKNESS));
  entityFactory.RegisterPrototype(
      "BottomBoundary", CreateBoundary(VIEW_WIDTH, BOUNDARY_THICKNESS, true));
  entityFactory.RegisterPrototype(
      "VBoundary", CreateBoundary(BOUNDARY_THICKNESS, VIEW_HEIGHT));

  // Register paddle entity prototype.
  entityFactory.RegisterPrototype("Paddle", CreatePaddle());
  entityFactory.RegisterPrototype("Ball", CreateBall());
  entityFactory.RegisterPrototype("BallIndicator", CreateBallIndicator());

  // Register a single, HP-agnostic brick prototype. Health and color are set
  // post-spawn via InitBrick().
  entityFactory.RegisterPrototype("RegularBrick", CreateBrick());
}

void EntityPrototypeService::OnShutdown() {
  // Cleanup.
  ASTU_SERVICE(EntityFactoryService).DeregisterAllPrototypes();
}

shared_ptr<Entity> EntityPrototypeService::CreateBoundary(float w, float h,
                                                          bool lethal) {
  auto entity = make_shared<Entity>();
  entity->AddComponent(make_shared<CPose>());

  if (debug) {
    entity->AddComponent(make_shared<CScene>(
        PolylineBuilder()
            .Color(BOUNDARY_COLOR)
            .VertexBuffer(ShapeGenerator().GenRectangle(w, h))
            .Build()));
  }

  if (lethal) {
    entity->AddComponent(make_shared<CLethalBoundaryComponent>());
  }

  entity->AddComponent(CBodyBuilder().Type(CBody::Type::Static).Build());

  entity->AddComponent(CPolygonColliderBuilder()
                           .Polygon(ShapeGenerator().GenRectangle(w, h))
                           .Restitution(GENERAL_RESTITUTION)
                           .Friction(GENERAL_FRICTION)
                           .CategoryBits(BOUNDARY_CATEGORY)
                           .MaskBits(BALL_CATEGORY)
                           .Build());

  return entity;
}

shared_ptr<Entity> EntityPrototypeService::CreatePaddle() {
  auto entity = make_shared<Entity>();
  entity->AddComponent(make_shared<CPose>());

  entity->AddComponent(
      make_shared<CScene>(PolylineBuilder()
                              .Color(PADDLE_COLOR)
                              .VertexBuffer(ShapeGenerator().GenRectangle(
                                  PADDLE_WIDTH, PADDLE_HEIGHT))
                              .Build()));

  entity->AddComponent(CBodyBuilder().Type(CBody::Type::Kinematic).Build());

  entity->AddComponent(
      CPolygonColliderBuilder()
          .Polygon(ShapeGenerator().GenRectangle(PADDLE_WIDTH, PADDLE_HEIGHT))
          .Restitution(GENERAL_RESTITUTION)
          .Friction(GENERAL_FRICTION)
          .CategoryBits(PADDLE_CATEGORY)
          .MaskBits(BALL_CATEGORY)
          .Build());

  // Calc max and min positions for the paddle.
  float maxX = ((VIEW_WIDTH / 2) - PADDLE_WIDTH / 2) -
               0.01f; // -0.01f to keep all pixels on screen.
  float minX = -(VIEW_WIDTH / 2) + PADDLE_WIDTH / 2;

  entity->AddComponent(make_shared<CPaddleComponent>(minX, maxX, PADDLE_SPEED));

  return entity;
}

shared_ptr<Entity> EntityPrototypeService::CreateBall() {
  auto entity = make_shared<Entity>();
  entity->AddComponent(make_shared<CPose>());

  entity->AddComponent(make_shared<CScene>(
      PolylineBuilder()
          .Color(BALL_COLOR)
          .VertexBuffer(ShapeGenerator().GenCircle(BALL_RADIUS))
          .Build()));

  entity->AddComponent(CBodyBuilder()
                           .Type(CBody::Type::Dynamic)
                           .LinearVelocity(2.5f, -3.0f)
                           .Build());

  entity->AddComponent(
      CCircleColliderBuilder()
          .Radius(BALL_RADIUS)
          .Restitution(GENERAL_RESTITUTION)
          .Friction(GENERAL_FRICTION)
          .CategoryBits(BALL_CATEGORY)
          .MaskBits(PADDLE_CATEGORY | BRICK_CATEGORY | BOUNDARY_CATEGORY)
          .Build());

  entity->AddComponent(make_shared<CBallComponent>(BALL_MAX_SPEED));

  return entity;
}

shared_ptr<Entity> EntityPrototypeService::CreateBallIndicator() {
  auto entity = make_shared<Entity>();
  entity->AddComponent(make_shared<CPose>());

  entity->AddComponent(make_shared<CScene>(
      PolylineBuilder()
          .Color(BALL_COLOR)
          .VertexBuffer(ShapeGenerator().GenCircle(BALL_RADIUS))
          .Build()));

  entity->AddComponent(CBodyBuilder().Type(CBody::Type::Static).Build());

  // Calc max and min positions for the paddle.
  float maxX = ((VIEW_WIDTH / 2) - PADDLE_WIDTH / 2) -
               0.01f; // -0.01f to keep all pixels on screen.
  float minX = -(VIEW_WIDTH / 2) + PADDLE_WIDTH / 2;

  entity->AddComponent(make_shared<CPaddleComponent>(0, 0, -1.0f));

  return entity;
}

shared_ptr<Entity> EntityPrototypeService::CreateBrick() {
  auto entity = make_shared<Entity>();
  entity->AddComponent(make_shared<CPose>());

  // Initial color is a placeholder; InitBrick() will set the real color
  // matching the brick's starting health.
  entity->AddComponent(
      make_shared<CScene>(PolylineBuilder()
                              .Color(BRICK_1_COLOR)
                              .Name("Brick")
                              .VertexBuffer(ShapeGenerator().GenRectangle(
                                  BRICK_WIDTH, BRICK_HEIGHT))
                              .Build()));

  entity->AddComponent(CBodyBuilder().Type(CBody::Type::Static).Build());

  entity->AddComponent(
      CPolygonColliderBuilder()
          .Polygon(ShapeGenerator().GenRectangle(BRICK_WIDTH, BRICK_HEIGHT))
          .Restitution(GENERAL_RESTITUTION)
          .Friction(GENERAL_FRICTION)
          .CategoryBits(BRICK_CATEGORY)
          .MaskBits(BALL_CATEGORY)
          .Build());

  entity->AddComponent(make_shared<CBrickComponent>(1));

  return entity;
}
