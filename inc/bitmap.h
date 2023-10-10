#ifndef __bitmap_h__
#define __bitmap_h__

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>
#include "truetype.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef char s8;
typedef short s16;
typedef int s32;
typedef long long s64;



typedef struct{
	stbtt_fontinfo *info;
	u8 *buffer;
	float scale;
}font;


#define wchar s32
#define wchar_to_str(wc) ((char *)(wc))


#define color u32
#define getColor(a, b, c, d) (a|b<<8|c<<16|d<<24)

#define getA(c) ((c>> 0)&0x000000ff)
#define getR(c) ((c>> 8)&0x000000ff)
#define getG(c) ((c>>16)&0x000000ff)
#define getB(c) ((c>>24)&0x000000ff)

typedef struct{
	u32 height;
	u32 width;
	u32 byteperpixel;
	u8 *map;
}bitmap;

bitmap *createBitmap(u32 width, u32 height, u32 byteperpixel);

void destroyBitmap(bitmap *bm);

color getPixel(bitmap *bm, u32 x, u32 y);

void setPixel(bitmap *bm, u32 x, u32 y, color c);

bitmap *createBitmapWithInit(u32 width, u32 height, u32 byteperpixel, color c);

u32 wstrlen(wchar *ws);
wchar *utf8_to_ucs2(char *code);

void fontPrint(font *f, bitmap *screen, s32 x, s32 y, char *text, color c, s32 maxWidth);
void fontSetSize(font *f, s32 pixels);
font *fontLoad(char *fontPath);
void fontUnload(font *f);

#endif
