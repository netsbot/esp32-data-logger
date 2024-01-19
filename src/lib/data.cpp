//
// Created by netsbit on 1/19/24.
//
#include <ArduinoJson.h>

#include "data.h"
#include "lib/globals.h"

Data::Data()
= default;

void Data::add_new_data(const float altitude, const float speed, const unsigned long long timestamp)
{
    data_point data_point{};

    data_point.altitude = altitude;
    data_point.speed = speed;
    data_point.timestamp = timestamp;

    contents.push_back(data_point);
}

void Data::upload_live_data(const float altitude, const float speed, const unsigned long long timestamp)
{
    socket.send_message(("L" + String(altitude) + "," + String(timestamp) + "," + String(speed)).c_str());
}

void Data::upload_recording_data() const
{
    std::string output;
    JsonDocument doc;
    auto array = doc.to<JsonArray>();


    for (auto& d : contents)
    {
        JsonDocument data_point_doc;
        auto data_point_array = data_point_doc.to<JsonArray>();

        data_point_array.add(d.altitude);
        data_point_array.add(d.speed);
        data_point_array.add(d.timestamp);

        array.add(data_point_array);
    }

    serializeJson(doc, output);
    socket.send_message(output.c_str());
}

void Data::set_boot_timestamp(const unsigned long long timestamp)
{
    boot_timestamp = timestamp;
}

void Data::clear_recording_data()
{
    contents.clear();
}