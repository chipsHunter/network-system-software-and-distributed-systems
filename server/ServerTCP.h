//
// Created by hvorostok on 02.03.2025.
//

#ifndef SERVER_SERVERTCP_H
#define SERVER_SERVERTCP_H

#include "includes.h"


class ServerTCP {
public:
    ServerTCP();
    ~ServerTCP();
    void start();
    void close();
    void set_port(unsigned short port);
    unsigned short get_port();
private:
    unsigned short port;
};


#endif //SERVER_SERVERTCP_H
