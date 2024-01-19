//
// Created by netsbit on 1/18/24.
//

#include "network.h"

#include <ESPmDNS.h>
#include <WiFi.h>

void Network::setup()
{
    if (AP_MODE)
    {
        while (!WiFi.softAP(AP_SSID, AP_PWD))
        {
            Serial.printf("Can't create AP with SSID: %s, password: %s", AP_SSID, AP_PWD);
            Serial.println("Retrying...");
            delay(1000);
        }
        Serial.printf("Created AP with SSID: %s, password: %s, IP: %s", AP_SSID, AP_PWD,
                      WiFi.localIP().toString().c_str());
    }
    else
    {
        while (!WiFi.begin(STA_SSID, STA_PWD))
        {
            Serial.printf("Can't connect AP with SSID: %s, password: %s", AP_SSID, AP_PWD);
            Serial.println("Retrying...");
            delay(1000);
        }
        Serial.printf("Connected to AP with SSID: %s, password: %s, IP: %s", STA_SSID, STA_PWD,
                      WiFi.localIP().toString().c_str());
    }

    setup_mdns();
}

void Network::setup_mdns()
{
    while (!MDNS.begin(MDNS_HOSTNAME))
    {
        Serial.println("Error setting up MDNS responder!");
    }
    Serial.println("mDNS responder started");
}
