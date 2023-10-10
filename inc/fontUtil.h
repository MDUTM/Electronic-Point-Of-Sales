#ifndef _FONTUTIL_H
#define _FONTUTIL_H 1

#include <iostream>
#include <string>
#include <string.h>
#include "font.h"
#include "lcd.h"

class Font {
public:
    Font(s32 pixels = 12, std::string fontName = "res/fonts/simkai_GB2312.ttf");
    void show(std::string str, int width, int height, int x = 0, int y = 0, color fontColor = 0xFFFFFFFF, color bgColor = 0x3F3F3FFF);

private:
    static font *_f;
    s32 _pixels;

    // void showBitmap(bitmap *bm, int x = 0, int y = 0);
};

#endif /* _FONTUTIL_H */