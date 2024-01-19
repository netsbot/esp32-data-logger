//
// Created by netsbit on 1/18/24.
//

#include "MPU6050.h"

MPU6050::MPU6050()
{
    mpu = Adafruit_MPU6050();
    const auto status = mpu.begin();

    if (!status)
    {
        Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    }

    mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
}

mpu6050_data MPU6050::get_data()
{
    sensors_event_t accel, gyro, temp;
    mpu.getEvent(&accel, &gyro, &temp);

    return mpu6050_data{accel, gyro, temp};
}
