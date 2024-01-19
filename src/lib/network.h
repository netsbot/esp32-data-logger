//
// Created by netsbit on 1/18/24.
//

#ifndef NETWORK_H
#define NETWORK_H

#define AP_MODE true

#define AP_SSID "YZY WR \"The College Dropout\""
#define AP_PWD "2hondaicodon"
#define STA_SSID "Hoang Minh 2.4GHz"
#define STA_PWD "hoangminh2310"
#define MDNS_HOSTNAME "esp32"

namespace Network
{
    void setup();
    void setup_mdns();
};


#endif //NETWORK_H
