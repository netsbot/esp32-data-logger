//
// Created by netsbit on 1/18/24.
//

#ifndef BMP280_H
#define BMP280_H
#include <Adafruit_BMP280.h>


class BMP280
{
    float baseline_hpa;
    Adafruit_BMP280 bmp;

public:
    explicit BMP280(float hpa, uint8_t i2c_addr);
    void calibrate();
    float read_altitude();
};

#endif //BMP280_H
