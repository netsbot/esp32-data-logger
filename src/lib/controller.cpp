//
// Created by netsbit on 1/18/24.
//
#include "MovingAverageFilter.h"

#include "controller.h"
#include "lib/globals.h"
#include "config.h"

MovingAverageFilter MAF_altitude(10);

Controller::Controller() = default;

void Controller::ws_handler(uint8_t* payload)
{
    Serial.printf("Message: %s\n", reinterpret_cast<char*>(payload));
    switch (payload[0])
    {
    case 'S':
        {
            set_recording(true);
            break;
        }
    case 'T':
        {
            set_recording(false);
            break;
        }
    case 'R':
        {
            // set refresh rate
            // Get all chars behind the first charactor
            if (payload[1] == 'U')

                set_upload_refresh_rate(atoi(reinterpret_cast<const char*>(payload + 2)));
            else
                set_record_refresh_rate(atoi(reinterpret_cast<const char*>(payload + 2)));
            break;
        }
    case 'C':
        {
            bmp.calibrate();
            break;
        }
    case 'K':
        {
            const auto connect_ts = strtoull(reinterpret_cast<const char*>(payload) + 1,
                                             nullptr,
                                             10);
            data.set_boot_timestamp(connect_ts - millis());
            break;
        }
    case 'M':
        switch (payload[1])
        {
        case 'C':
            state = CONNECTED;
            Serial.println("State: Connected");
            break;
        case 'A':
            state = ASCENT;
            Serial.println("State: Ascent");
            break;
        case 'M':
            state = MECU;
            Serial.println("State: MECU");
            break;
        case 'P':
            state = APOGEE;
            Serial.println("State: Apogee");
            break;
        case 'D':
            state = DESCENT;
            Serial.println("State: Descent");
            break;
        case 'L':
            state = LANDED;
            Serial.println("State: Landed");
            break;
        default: break;
        }
    default:
        {
            Serial.println("Invalid command");
            break;
        }
    }
}

void Controller::set_upload_refresh_rate(const int rate)
{
    upload_refresh_rate = rate;
}

void Controller::set_record_refresh_rate(const int rate)
{
    record_refresh_rate = rate;
}

void Controller::set_recording(const bool state)
{
    if (recording == true)
        data.upload_recording_data();
    else
        data.clear_recording_data();

    recording = state;
}

void Controller::set_calibration(const unsigned long long connected_ts)
{
    calibration = connected_ts - millis();
}

float Controller::get_speed(const float current_altitude)
{
    if (speed_timer.hasPassed(speed_refresh_rate))
    {
        last_speed = (current_altitude - last_altitude) / speed_refresh_rate;
        last_altitude = current_altitude;
    }
    return last_speed;
}

bool Controller::is_apogee(const float current_altitude)
{
    if (current_altitude < max_altitude)
    {
        if (apogee_timer.hasPassed(100))
            return true;
        return false;
    }
    return false;
}


void Controller::loop()
{
    const float altitude = MAF_altitude.process(bmp.read_altitude());
    float speed = 0;
    const mpu6050_data mpu_data = mpu.get_data();

    switch (state)
    {
    case IDLE:
        break;
    case CONNECTED:
        {
            sg90.engage_parachute();
            if ((mpu_data.accel.acceleration.x - EARTH_ACCEL) >= LAUNCH_ACCEL_THRESHOLD || altitude >=
                LIFTOFF_ALTITUDE_THRESHOLD)
            {
                if (liftoff_timer.hasPassed(launch_accel_time_threshold))
                {
                    state = ASCENT;
                    Serial.println("Liftoff");
                }
            }
        }
    case ASCENT:
        {
            const auto totalAccel = sqrt(
                sq(mpu_data.accel.acceleration.x) + sq(mpu_data.accel.acceleration.y) + sq(
                    mpu_data.accel.acceleration.z));

            if (totalAccel <= ACCEL_UNPOWERED_THRESHOLD)
            {
                state = MECU;
                Serial.println("MECU");
            }
        }
    case MECU:
        if (is_apogee(altitude))
        {
            state = APOGEE;
            Serial.println("Apogee");
        }
        break;
    case APOGEE:
        sg90.disengage_parachute();
        Serial.println("Parachute");
        state = DESCENT;
        break;
    case DESCENT:
        if (altitude <= LIFTOFF_ALTITUDE_THRESHOLD)
        {
            state = LANDED;
            Serial.println("Landed");
        }
        state = LANDED;
    case LANDED:
        break;
    }


    if (recording && record_timer.hasPassed(record_refresh_rate))
    {
        speed = get_speed(altitude);

        data.add_new_data(altitude, speed, calibration + millis());
    }

    if (connected && upload_timer.hasPassed(upload_refresh_rate))
    {
        data.upload_live_data(altitude, speed, calibration + millis());
    }
}
