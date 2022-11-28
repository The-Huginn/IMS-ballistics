/**
 * @author Rastislav Budinsky
 * @file Booster.h
 * @brief This file contains template for class Booster
*/
#ifndef BOOSTER_H
#define BOOSTER_H

#include "simlib.h"
#include "Stage.h"

class Missile;

class Booster : public ConditionDown {
    Stage stage;
    Missile *missile;
    Integrator fuel;

    public :
        Booster(Stage stage_, Missile *missile_);

        void Action() override;
        void activate();
        double getBoosterWeight();
        void Out();
};

#endif /* BOOSTER_H */