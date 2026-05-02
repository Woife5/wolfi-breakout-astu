/*
 * Wolfi Breakout
 *
 * Copyright (c) 2021 Wolfgang Schwendtbauer. All rights reserved.
 */

// AST Utilities includes
#include <AstuECS.h>

class CPaddleComponent : public astu::EntityComponent {
public:
    float momentum;
    float maxSpeed;
    float maxX;
    float minX;

    /**
     * Constructor.
     */
    CPaddleComponent(float minX, float maxX, float maxSpeed = 0.1f)
        : momentum(0.0f)
        , maxX(maxX)
        , minX(minX)
        , maxSpeed(maxSpeed)
    {
        // Intentionally left empty.
    }

    CPaddleComponent(const CPaddleComponent& other)
        : momentum(other.momentum)
        , maxX(other.maxX)
        , minX(other.minX)
        , maxSpeed(other.maxSpeed)
    {
        // Intentionally left empty.
    }

    // Inherited via EntityComponent
    virtual std::shared_ptr<EntityComponent> Clone() override
    {
        // Create copy using copy-constructor.
        return std::make_shared<CPaddleComponent>(*this);
    }
};
