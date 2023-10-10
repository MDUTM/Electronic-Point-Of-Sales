#ifndef _TOUCH_H
#define _TOUCH_H 1

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#include "point.h"

class Touch {
public:
    enum BoardType {
        BoardType_BLACK,
        BoardType_BLUE
    };

    Touch(const char *dev = "/dev/input/event0", enum BoardType type = BoardType_BLACK);
    ~Touch() { close(_fd); }

    Point wait();

private:
    int _fd;
    enum BoardType _type;
};

#endif /* _TOUCH_H */