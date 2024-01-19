//
// Created by netsbit on 1/18/24.
//
#include "BMP280.h"

BMP280::BMP280(const float hpa, const u_int8_t i2c_addr)
{
    bmp = Adafruit_BMP280();
    baseline_hpa = hpa;

    const auto status = bmp.begin(i2c_addr);
    if (!status)
    {
        Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
            "try a different address!"));
        Serial.print("SensorID was: 0x");
        Serial.println(bmp.sensorID(), 16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
    }

    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL, /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2, /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X8, /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X8, /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_1);

    calibrate();
}

void BMP280::calibrate()
{
    baseline_hpa = bmp.readPressure() / 100.0F;
    Serial.println("Recalibrated pressure");
}

float BMP280::read_altitude()
{
    return bmp.readAltitude(baseline_hpa);
}
