/**
 * @author Rastislav Budinsky
 * @file Stage.h
 * @brief This file contains struct "trait" for Booster
*/
#ifndef STAGE_H
#define STAGE_H

typedef struct {
    const double boosterWeight, fuelWeight, ve, burnRate;
}Stage;

#endif /* STAGE_H */