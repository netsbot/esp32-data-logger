#include <Arduino.h>

#include "lib/network.h"
#include "lib/globals.h"
#include "lib/controller.h"

Controller controller;
Socket socket(81);
Data data;

void setup()
{
    Serial.println("Config activated!");

    Serial.begin(9600);
    controller = Controller();
    socket = Socket(81);
    data = Data();

    Network::setup();

    Serial.print("Finished setup\n");
}

void loop()
{
    controller.loop();
}
