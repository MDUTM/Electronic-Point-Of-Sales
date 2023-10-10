#include "fontUtil.h"

using namespace std;
font *Font::_f = nullptr;

Font::Font(s32 pixels, std::string fontName)
{
    _pixels = pixels;
    _f = fontLoad(const_cast<char *>(fontName.data())); 
}

void Font::show(std::string str, int width, int height, int x, int y, color fontColor, color bgColor)
{
    fontSetSize(_f, _pixels);
    bitmap *bm = createBitmapWithInit(width, height, 4, bgColor);
    fontPrint(_f, bm, 0, 3, const_cast<char *>(str.data()), fontColor, 0);

    Lcd *lcd = Lcd::getInstance();
    char *addr = lcd->getAddr() + (x + y*lcd->getWidth())*lcd->getBpp()/8;

    for (int row = 0, loffset = 0, foffset = 0; (row < height) && (row < lcd->getHeight()); row++)
    {
        foffset = bm->width * bm->byteperpixel * row;
        loffset = lcd->getWidth() * lcd->getBpp()/8 * row;
        for (int col = 0; (col < width) && (col < lcd->getWidth()); col++)
            memcpy(addr + col * 4 + loffset, bm->map + col * bm->byteperpixel + foffset, bm->byteperpixel);
    }

    destroyBitmap(bm);
}