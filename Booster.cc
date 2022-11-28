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
    missile->engine.thrust.SetInput(stage.burnRate * stage.ve / missile->getTotalWeight());
}

double Booster::getBoosterWeight() {
    return stage.boosterWeight;
}

void Booster::Out() {

}