//
// Created by netsbit on 1/19/24.
//

#ifndef DATA_H
#define DATA_H
#include <vector>

struct data_point
{
    float altitude;
    float speed;
    unsigned long long timestamp;
};


class Data
{
    unsigned long long time_calibration = 0;
    unsigned long long connect_timestamp = 0;
    unsigned long long boot_timestamp = 0;
    std::vector<data_point> contents = {};

public:
    Data();
    void add_new_data(float altitude, float speed, unsigned long long timestamp);
    void upload_live_data(float altitude, float speed, unsigned long long timestamp);
    void upload_recording_data() const;
    void set_boot_timestamp(unsigned long long timestamp);
    void clear_recording_data();
};
#endif //DATA_H
