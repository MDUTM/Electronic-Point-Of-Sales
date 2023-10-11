#include "udp.h"

Udp::Udp(std::string ip, int port)
{
    _sockfd = socket(AF_INET,    /*使用IPv4做网际通信*/
                        SOCK_DGRAM, /*使用数据报方式收发数据（帧同步）*/
                        0           /*使用数据报的默认协议，即UDP*/);
    
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    bzero(&addr, len);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.data());
    addr.sin_port = htons(port); // host to network short

    bind(_sockfd, (struct sockaddr *)&addr, len);
}

void Udp::sendMsg(std::string msg, std::string ip, int port)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    bzero(&addr, len);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.data());
    addr.sin_port = htons(port); // host to network short

    sendto(_sockfd, msg.data(), msg.length(), 0, (struct sockaddr *)&addr, len);
}

void Udp::recvMsg()
{
    char *msg = new char[1024*10]();

    // 对方的ip
    socklen_t len = sizeof(peeraddr);
    bzero(&peeraddr, len);

    recvfrom(_sockfd, msg, 1024*10, 0, (struct sockaddr *)&peeraddr, &len);
    cJSON *root = cJSON_Parse(msg);
    std::cout << cJSON_Print(root) << std::endl;

    delete[] msg;
    cJSON_Delete(root);
}

void Udp::recvMsg(std::string &str)
{
    char *msg = new char[str.size()]();

    // 对方的ip
    socklen_t len = sizeof(peeraddr);
    bzero(&peeraddr, len);

    recvfrom(_sockfd, msg, str.size(), 0, (struct sockaddr *)&peeraddr, &len);
    cJSON *root = cJSON_Parse(msg);
    std::cout << cJSON_Print(root) << std::endl;

    str = msg;

    delete[] msg;
    cJSON_Delete(root);
}

int Udp::getRecvMsgStatus()
{
    char ch;
    recvfrom(_sockfd, &ch, 1, 0, NULL, NULL);

    return atoi(&ch);
}
