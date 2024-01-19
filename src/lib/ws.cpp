//
// Created by netsbit on 1/18/24.
//

#include "ws.h"
#include "controller.h"
#include "lib/globals.h"


Socket::Socket(const int port)
{
    socket = WebSocketsServer(port);
    socket.begin();

    socket.onEvent([this](const uint8_t num, const WStype_t type, uint8_t* payload, size_t length)
    {
        switch (type)
        {
        case WStype_DISCONNECTED: // if the websocket is disconnected
            {
                Serial.printf("[%u] Disconnected!\n", num);
                if (socket.connectedClients() == 0)
                    controller.connected = false;
            }
            break;
        case WStype_CONNECTED:
            {
                // if a new websocket connection is established
                IPAddress ip = socket.remoteIP(num);
                Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
                controller.connected = true;
            }
            break;
        case WStype_TEXT:
            {
                controller.ws_handler(payload);
            }
        default: break;
        }
    });
}

void Socket::send_message(const char* payload)
{
    socket.sendTXT(0, payload);
}
