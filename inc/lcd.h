/**
 * @file    lcd.h
 * @version 1.0
 * @brief   LCD类
 * 
 * @author  MDUTM  MDUTM@outlook.com
 * @date    2023-09-26
 * 
 * @copyright Copyright (c) 2023 MDUTM
 */
#ifndef _LCD_H
#define _LCD_H 1

#include <iostream>
#include <cstring>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fb.h>

class Lcd
{
    Lcd(const char *dev = "/dev/fb0");
    virtual ~Lcd();

public:
    static Lcd *getInstance();
    char *getAddr();
    int getFd();
    int getWidth();
    int getHeight();
    int getBpp();
    int getSize();

private:
    static Lcd *instance;
    char *addr;
    int fd;
    int width;
    int height;
    int bpp;
    int size;
};

#endif /* _LCD_H */