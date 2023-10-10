#ifndef _BMP_H
#define _BMP_H 1

#include <iostream>
#include <cstring>
#include "lcd.h"

class Bmp
{
    struct bitmap_header
    {
        int16_t type;
        int32_t size; // 图像文件大小
        int16_t reserved1;
        int16_t reserved2;
        int32_t offbits; // bmp图像数据偏移量
    } __attribute__((packed));

    struct bitmap_info
    {
        int32_t size;   // 本结构大小
        int32_t width;  // 图像宽
        int32_t height; // 图像高
        int16_t planes;

        int16_t bit_count; // 色深
        int32_t compression;
        int32_t size_img; // bmp数据大小，必须是4的整数倍
        int32_t X_pel;
        int32_t Y_pel;
        int32_t clrused;
        int32_t clrImportant;
    } __attribute__((packed));

    // 以下结构体不一定存在于BMP文件中，除非：
    // bitmap_info.compression为真
    struct rgb_quad
    {
        int8_t blue;
        int8_t green;
        int8_t red;
        int8_t reserved;
    } __attribute__((packed));

public:
    Bmp(const char *fileName);
    Bmp();
    virtual ~Bmp();

    void display(int x = 0, int y = 0);
    char *getRGB();
    void setBmp(const char *fileName);

private:
    char *name;
    int width;
    int height;
    int bpp;

    void setInfo();
};

#endif /* _BMP_H */