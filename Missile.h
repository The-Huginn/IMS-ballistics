/**
 * @author Rastislav Budinsky
 * @file Missile.h
 * @brief This file contains base class for simulating Ballistic missile
*/
#ifndef MISSILE_H
#define MISSILE_H

#include "simlib.h"
#include "Booster.h"

#include <math.h>
#include <iostream>

extern unsigned int boostersSize;
extern Booster **boosters;

class Missile : public ConditionDown {
    Integrator y, x;
    Variable totalWeight;
    unsigned int attachedBooster;

    class Engine : public ConditionUp {
            const double c;

        public:
            const double initialAngle;
            bool liftoff = false;
            Expression constantVy, constantVx, angle, g;
            Integrator vx, vy;
            Integrator fuel;

            Engine(double initialVelocity, double initialAngle_, double c_, double fuelWeight, Integrator *y);
            void Liftoff();
            void enginesOff();
            bool Test() override { return vy.Value() >= 10.0 && !liftoff; };
            void Action() override;
    };


    public:
        static constexpr double PI = 3.1415;
        Engine engine;
        Missile(double initialVelocity, double initialAngle, double initialY, double _c, double projectileWeight, double fuelWeight, double boostersWeight);

        void Action() override;
        void activateBooster();
        void releaseBooster();
        void Out();
        double getTotalWeight();
};

#endif /* MISSILE_H */