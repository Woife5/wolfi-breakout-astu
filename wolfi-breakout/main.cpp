/*
 * Wolfi Breakout
 * 
 * Copyright (c) 2021 Wolfgang Schwendtbauer. All rights reserved.
 */

// Local includes
#include "EntityPrototypeService.h"	
#include "GameModeService.h"
#include "Constants.h"
#include "PaddleSystem.h"
#include "BallSystem.h"
#include "GameEvent.h"

// ASTU/Box2D includes
#include <AstuBox2D.h>

// AST-Utilities includes
#include <AstuSuiteSDL.h>
#include <AstuInput.h>
#include <AstuECS.h>
#include <AstuSuite2D.h>

using namespace astu2d;
using namespace astu;
using namespace std;

// Main entry point of the application.
int main()
{
	SdlApplication app;

	// Cameras do the world-to-screen transform and used by the scene graph.
	ASTU_CREATE_AND_ADD_SERVICE(CameraService);

	// Add services for debugging.
	if(DEBUG) {
		ASTU_CREATE_AND_ADD_SERVICE(CameraControlService);
	}

	// Add Services and Systems required ECS.
	ASTU_CREATE_AND_ADD_SERVICE(EntityService);
	ASTU_CREATE_AND_ADD_SERVICE(EntityFactoryService);	
	ASTU_CREATE_AND_ADD_SERVICE(Box2DPhysicsSystem);
	ASTU_CREATE_AND_ADD_SERVICE(CollisionSignalService);
	ASTU_CREATE_AND_ADD_SERVICE(SceneSystem);

	// Let's add our main service that runs the application.
	ASTU_CREATE_AND_ADD_SERVICE(EntityPrototypeService, DEBUG);
	ASTU_CREATE_AND_ADD_SERVICE(GameModeService);
	ASTU_CREATE_AND_ADD_SERVICE(PaddleSystem);
	ASTU_CREATE_AND_ADD_SERVICE(BallSystem);
	ASTU_CREATE_AND_ADD_SERVICE(GameEventService);

	ASTU_SERVICE(PhysicsSystem).SetGravityVector(GRAVITY);

	// Configure input controls (Axis and Actions)
	auto& inputMapping = ASTU_SERVICE(InputMappingService);
	inputMapping.AddAxisMapping("Paddle", Keys::GamepadLeftThumbstickX);
	inputMapping.AddAxisMapping("Paddle", Keys::Right, 1.0f);
	inputMapping.AddAxisMapping("Paddle", Keys::Left, -1.0f);
	inputMapping.AddActionMapping("FireBall", Keys::SpaceBar);
	inputMapping.AddActionMapping("FireBall", Keys::GamepadFaceButtonBottom);
	inputMapping.AddActionMapping("TiltBall", Keys::T);
	inputMapping.AddActionMapping("TiltBall", Keys::GamepadFaceButtonRight);

	// Configure application.
	app.SetApplicationName("Wolfi Breakout");
	app.SetVersionString("1.0.1");
	app.SetResolution(Resolution::WXGA);
	app.SetFullscreen(false);

	// Run the application.
	return app.Run();
}
