//
// Created by netsbit on 1/18/24.
//

#ifndef WS_H
#define WS_H
#include <WebSocketsServer.h>

class Socket
{
    WebSocketsServer socket = WebSocketsServer(80);
    bool connected = false;

public:
    explicit Socket(int port);
    void send_message(const char* payload);
};


#endif //WS_H
