#include "lcd.h"

using namespace std;

Lcd *Lcd::instance = nullptr;
struct fb_var_screeninfo vinfo;

Lcd::Lcd(const char *dev)
{
    fd = open(dev, O_RDWR);
    if (fd == -1)
    {
        perror("打开液晶屏失败");
        exit(EXIT_FAILURE);
    }

    ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
    width = vinfo.xres;
    height = vinfo.yres;
    bpp = vinfo.bits_per_pixel;
    size = width * height * 4;

    addr = reinterpret_cast<char *>(mmap(nullptr, size, PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0));
    if (addr == MAP_FAILED)
    {
        perror("LCD映射内存失败");
        close(fd);
        exit(EXIT_FAILURE);
    }

    memset(addr, 0, size);
}

Lcd::~Lcd()
{
    munmap(addr, size);
}

Lcd *Lcd::getInstance()
{
    if (!instance)
        instance = new Lcd;

    return instance;
}

char *Lcd::getAddr()
{
    return addr;
}

int Lcd::getFd()
{
    return fd;
}

int Lcd::getWidth()
{
    return width;
}

int Lcd::getHeight()
{
    return height;
}

int Lcd::getBpp()
{
    return bpp;
}

int Lcd::getSize()
{
    return size;
}