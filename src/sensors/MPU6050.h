//
// Created by netsbit on 1/18/24.
//

#ifndef MPU6050_H
#define MPU6050_H

#include <Adafruit_MPU6050.h>

struct mpu6050_data
{
    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t temp;
};

class MPU6050
{
    Adafruit_MPU6050 mpu;

public:
    MPU6050();
    mpu6050_data get_data();
};


#endif //MPU6050_H
