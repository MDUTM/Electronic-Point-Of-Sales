#include <iostream>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "bmp.h"
#include "touch.h"

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cout << "请指定桌号!" << std::endl;
        exit(EXIT_FAILURE);
    }

begin:
    Bmp *pic_epos = new Bmp;
    Touch *ts_epos = new Touch;

    pic_epos->setBmp("res/ui/welcome.bmp");
    pic_epos->display();

    ts_epos->wait();

    if (fork() == 0)
        execl("main", "main", argv[1], NULL);
    else
        wait(NULL);

    delete pic_epos;
    delete ts_epos;

    goto begin;
    return 0;
}
