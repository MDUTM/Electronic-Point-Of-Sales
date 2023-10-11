#include <iostream>
#include <string>
#include <cstring>

#include <time.h>

#include "udp.h"

using namespace std;

int main()
{
    time_t t = time(nullptr);
    struct tm today = *localtime(&t);

    char *fileName = new char[11]();
    sprintf(fileName, "%d-%02d-%02d", today.tm_year + 1900, today.tm_mon + 1, today.tm_mday);
    FILE *fp = fopen(fileName, "a+");
    if (fp == nullptr)
        perror("error");

    string *str = new string(100 * 1024, '\0');
    Udp *server = new Udp(std::string("192.168.2.35"));

    while (1)
    {
        server->recvMsg(*str);
        fwrite(str->data(), str->length(), 1, fp);
        fwrite("\n", 1, 1, fp);
    }

    return 0;
}