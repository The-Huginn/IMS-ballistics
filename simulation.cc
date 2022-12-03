/**
 * @author Rastislav Budinsky
 * @file simulation.cc
 * @brief This is the main moduel for running simulation
*/

#include "simlib.h"
#include "Missile.h"
#include <iostream>
#include <memory>

/**
 * Drag force is considered stable during whole simulation
 *  this is simulated currently with a bullet-like drag, i.e. c = 0.000295
*/

Stage stages[] = {{2292.0, 20785.0, 2700.0, 346.416}};//, {700.0, 1000.0, 500.0, 9}};
Booster **boosters;
unsigned int boostersSize = sizeof(stages) / sizeof(Stage);

// Update the last 2 value2 as
//      sum of all stages' totalWeight without fuel
//      sum of all stages' fuel
Missile p(0.0, 89.5, 0.0, 0.000295, 1500.0, 2292.0, 20785.0);

void Sample() {
    p.Out();
}
Sampler s(Sample, 0.01);

int main() {
    boosters = (Booster**)malloc(boostersSize * sizeof(Booster*));
    for (unsigned int i = 0; i < boostersSize; i++)
        boosters[i] = new Booster(stages[i], &p);

    SetOutput("simulation.dat");
    Print("# Missile --- model of flying Missile\n");
    Print("# Time y x vy vx thrust weight angle\n");
    p.activateBooster();
    Init(0);
    SetStep(1e-10, 0.5);
    SetAccuracy(1e-5, 0.001);
    Run();
    SIMLIB_statistics.Output();
}