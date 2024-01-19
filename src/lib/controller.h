//
// Created by netsbit on 1/18/24.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Chrono.h>


#include "SG90.h"
#include "ws.h"
#include "sensors/BMP280.h"
#include "sensors/MPU6050.h"

enum data_state
{
    IDLE,
    CONNECTED,
    ASCENT,
    MECU,
    APOGEE,
    DESCENT,
    LANDED
};

class Controller
{

    BMP280 bmp = BMP280(1018, 0x76);
    MPU6050 mpu = MPU6050();
    Socket socket = Socket(80);
    SG90 sg90 = SG90(8);

    Chrono liftoff_timer;
    Chrono upload_timer;
    Chrono record_timer;
    Chrono speed_timer;
    Chrono apogee_timer;

    int upload_refresh_rate = 0;
    int record_refresh_rate = 0;
    int launch_accel_time_threshold = 30;
    int speed_refresh_rate = 1000;

    float last_altitude = 0;
    float last_speed = 0;
    float max_altitude = 0;

    unsigned long long calibration = 0;
    bool recording = false;
    data_state state = IDLE;

public:
    bool connected = false;
    Controller();
    void ws_handler(uint8_t* payload);
    void set_upload_refresh_rate(int rate);
    void set_record_refresh_rate(int rate);
    void set_recording(bool state);
    void set_calibration(unsigned long long connected_ts);
    float get_speed(float current_altitude);
    bool is_apogee(float current_altitude);
    void loop();
};


#endif //CONTROLLER_H
