/*
 * Wolfi Breakout
 *
 * Copyright (c) 2021 Wolfgang Schwendtbauer. All rights reserved.
 */

#pragma once

// Local includes
#include "BrickEvent.h"
#include "../GameEvent.h"

// AST Utilities includes
#include <AstuECS.h>
#include <AstuServices.h>

/**
 * Owns the brick lifecycle. Listens for BrickEvent::Hit signals and updates
 * the corresponding brick's health, score, and visual state. Destroys the
 * brick entity once its health is depleted.
 */
class BrickSystem : public astu::BaseService,
                    private astu::ISignalListener<BrickEvent>,
                    private astu::SignalEmitter<GameEvent> {
public:
    BrickSystem();

private:
    // Inherited via BaseService
    virtual void OnStartup() override;
    virtual void OnShutdown() override;

    // Inherited via ISignalListener
    virtual bool OnSignal(const BrickEvent& signal) override;

    void HandleHit(astu::Entity& brick);
};
