#ifndef _UDP_H
#define _UDP_H 1

#include <iostream>
#include <string>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>

#include "JsonUtil.h"

class Udp
{
    int _sockfd;
    struct sockaddr_in peeraddr;

public:
    Udp(std::string ip, int port = 54321);

    void recvMsg();
    void recvMsg(std::string &str);
    int getRecvMsgStatus();
    void sendMsg(std::string msg, std::string ip, int port = 54321);
};

#endif /* _UDP_H */