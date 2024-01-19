//
// Created by netsbit on 1/19/24.
//

#include "SG90.h"

SG90::SG90(const int pin)
{
    servo.attach(pin);
}

void SG90::engage_parachute()
{
    servo.write(500);
}

void SG90::disengage_parachute()
{
    servo.write(2500);
}
