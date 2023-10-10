#include "touch.h"

Touch::Touch(const char *dev, enum BoardType type)
{
    _fd = open(dev, O_RDWR);
    if (_fd == -1)
    {
        perror("打开触摸设备失败");
        return;
    }

    _type = type;
}

Point Touch::wait()
{
    int x = 0, y = 0;
    struct input_event info;

    while (1)
    {
        struct input_event info;

        read(_fd, &info, sizeof(struct input_event));

        if (info.type == EV_ABS && info.code == ABS_X)
            x = info.value;
        if (info.type == EV_ABS && info.code == ABS_Y)
            y = info.value;

        if (info.type == EV_KEY && info.code == BTN_TOUCH && info.value == 0)
        {
            // 如果你的板子是黑色的，那么需要进行坐标转换(1024,600) ---(800,480)
            if (_type == BoardType_BLACK)
            {
                x = (x * 1.0) * 800 / 1024;
                y = (y * 1.0) * 480 / 600;
            }

            // printf("(%d,%d)\n", x, y);
            break;
        }
    }

    return Point(x, y);
}
