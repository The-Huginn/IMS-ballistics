/**
 * @author Rastislav Budinsky
 * @file Missile.cc
 * @brief This file implements class Missile
*/
#include "Missile.h"
#include <iostream>

const double g_ = 9.81;
const double R = 6378000;

Missile::Missile(double initialVelocity, double initialAngle, double initialY, double _c, double projectileWeight, double fuelWeight, double boostersWeight) :
    ConditionDown(y),
    y(engine.vy, initialY),
    x(engine.vx, 0),
    totalWeight(projectileWeight + boostersWeight),
    attachedBooster(0),
    engine(initialVelocity, initialAngle, _c, fuelWeight, &y) {}

// We remove the weight of the booster, which should calculate with it's weigth on it's own
void Missile::activateBooster() {
    if (boostersSize <= attachedBooster) {
        engine.enginesOff();
        return;
    }
    Print("# Activating Booster %d \n", attachedBooster);

    boosters[attachedBooster]->activate();
}

void Missile::releaseBooster() {
    Print("# Releasing Booster %d \n", attachedBooster);

    engine.thrust.SetState(0.0);
    totalWeight = totalWeight.Value() - boosters[attachedBooster]->getBoosterWeight();

    attachedBooster++;
    activateBooster();
}

double Missile::getTotalWeight() {
    return totalWeight.Value() + engine.fuel.Value();
}

void Missile::Action() {
    if (!engine.liftoff) {
        if (engine.vy.Value() < 0.0)
            engine.vy.SetState(0.0);
        y.SetState(0.1);
        engine.vx.SetState(0.0);
        engine.vx.SetInput(0.001);
        x.SetState(0.0);
        return;
    }

    Out();
    Stop();
}

void Missile::Out() {
    Print("%-9.3f % -9.3g % -9.3g % -9.3g % -9.3g % -9.3g % -9.3g % -9.3g\n",
            T.Value(), y.Value(), x.Value(), engine.vy.Value(), engine.vx.Value(), engine.thrust.Value(), getTotalWeight(), !engine.liftoff ? engine.initialAngle : engine.angle.Value());
    boosters[attachedBooster]->Out();
}

Missile::Engine::Engine(double initialVelocity, double initialAngle_, double c_, double fuelWeight, Integrator *y) :
    ConditionUp(vy),
    c(c_),
    initialAngle(initialAngle_ * PI / 180),
    g(Max(0.5, g_ * (1 - 2* (*y) / R))),    // considering at least 0.5 ms of g
    constantVy(-g - c*vy),
    constantVx(-c*vx),
    angle(ATan(vy/vx)),
    fuel(0.0, fuelWeight),
    vy(constantVy + thrust * Sin(initialAngle), (initialVelocity <= 0) ? 0.001 : initialVelocity * sin(initialAngle)),
    vx(constantVx + thrust * ((initialAngle >= PI / 2 - 0.001 && initialAngle <= PI / 2 + 0.001) ? 0.0 : Cos(angle)), (initialAngle >= PI / 2 - 0.001 && initialAngle <= PI / 2 + 0.001 ) ? 0.0 : initialVelocity * cos(initialAngle))   // special case for rounding problem
    {}

void Missile::Engine::enginesOff() {
    vy.SetInput(constantVy);
    vx.SetInput(constantVx);
    thrust.SetState(0.0);
    thrust.SetInput(0.0);
    fuel.SetState(0.0);
    fuel.SetInput(0.0);
}

void Missile::Engine::Liftoff() {
    std::cerr << T.Value();
    
    vy.SetInput(constantVy + thrust * Sin(angle));
    vx.SetState(vy.Value()/tan(initialAngle));
    vx.SetInput(constantVx + thrust * Cos(angle));
}

void Missile::Engine::Action() {
    liftoff = true;
    Liftoff();
}