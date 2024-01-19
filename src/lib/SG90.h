//
// Created by netsbit on 1/19/24.
//

#ifndef SG90_H
#define SG90_H

#include <ESP32Servo.h>

class SG90 {
    Servo servo;
public:
    explicit SG90(int pin);
    void engage_parachute();
    void disengage_parachute();
};



#endif //SG90_H
