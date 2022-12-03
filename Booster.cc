/**
 * @author Rastislav Budinsky
 * @file Booster.cc
 * @brief This file implements class Booster
*/
#include "Booster.h"
#include "Missile.h"
#include <iostream>

Booster::Booster(Stage stage_, Missile *missile_) :
    ConditionDown(fuel),
    stage(stage_),
    missile(missile_),
    fuel(0.0, stage.fuelWeight) {}

void Booster::Action() {
    missile->releaseBooster();
}

void Booster::activate() {
    fuel.SetInput(-stage.burnRate);
    missile->engine.fuel.SetInput(-stage.burnRate);
    missile->engine.vy.SetInput(missile->engine.constantVy + (stage.burnRate * stage.ve / (missile->getTotalWeight() + fuel)) / 2.0 * (missile->engine.liftoff ? Sin(missile->engine.angle) : Sin(missile->engine.initialAngle)));
    missile->engine.vx.SetInput(missile->engine.constantVx + (stage.burnRate * stage.ve / (missile->getTotalWeight() + fuel)) / 2.0 * (missile->engine.liftoff ? Cos(missile->engine.angle) : ((missile->engine.initialAngle >= missile->PI / 2 - 0.001 && missile->engine.initialAngle <= missile->PI / 2 + 0.001 ? 0.0 : Cos(missile->engine.initialAngle)))));
}

double Booster::getBoosterWeight() {
    return stage.boosterWeight;
}

void Booster::Out() {
    // Print("%.3f\n", stage.burnRate * stage.ve / missile->getTotalWeight());
}