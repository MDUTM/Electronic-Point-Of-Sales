#include "font.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>


#define wchar s32
#define wchar_to_str(wc) ((char *)(wc))


#define color u32
#define getColor(a, b, c, d) (a|b<<8|c<<16|d<<24)
#define getA(c) ((c>> 0)&0x000000ff)
#define getR(c) ((c>> 8)&0x000000ff)
#define getG(c) ((c>>16)&0x000000ff)
#define getB(c) ((c>>24)&0x000000ff)


u32 wstrlen(wchar *ws);
wchar *utf8_to_ucs2(char *code);


extern int stbtt_InitFont(stbtt_fontinfo *info, const unsigned char *data, int offset);
// Given an offset into the file that defines a font, this function builds
// the necessary cached info for the rest of the system. You must allocate
// the stbtt_fontinfo yourself, and stbtt_InitFont will fill it out. You don't
// need to do anything special to free it, because the contents are pure
// value data with no additional data structures. Returns 0 on failure.



int stbtt_FindGlyphIndex(const stbtt_fontinfo *info, int unicode_codepoint);
float stbtt_ScaleForPixelHeight(const stbtt_fontinfo *info, float pixels);
float stbtt_ScaleForMappingEmToPixels(const stbtt_fontinfo *info, float pixels);
void stbtt_GetFontVMetrics(const stbtt_fontinfo *info, int *ascent, int *descent, int *lineGap);
void stbtt_GetFontBoundingBox(const stbtt_fontinfo *info, int *x0, int *y0, int *x1, int *y1);
void stbtt_GetCodepointHMetrics(const stbtt_fontinfo *info, int codepoint, int *advanceWidth, int *leftSideBearing);
int  stbtt_GetCodepointKernAdvance(const stbtt_fontinfo *info, int ch1, int ch2);
int stbtt_GetCodepointBox(const stbtt_fontinfo *info, int codepoint, int *x0, int *y0, int *x1, int *y1);
void stbtt_GetGlyphHMetrics(const stbtt_fontinfo *info, int glyph_index, int *advanceWidth, int *leftSideBearing);
int  stbtt_GetGlyphKernAdvance(const stbtt_fontinfo *info, int glyph1, int glyph2);
int  stbtt_GetGlyphBox(const stbtt_fontinfo *info, int glyph_index, int *x0, int *y0, int *x1, int *y1);
void stbtt_GetCodepointBitmapBox(const stbtt_fontinfo *font, int codepoint, float scale_x, float scale_y, int *ix0, int *iy0, int *ix1, int *iy1);
void stbtt_GetCodepointBitmapBoxSubpixel(const stbtt_fontinfo *font, int codepoint, float scale_x, float scale_y, float shift_x, float shift_y, int *ix0, int *iy0, int *ix1, int *iy1);
void stbtt_MakeCodepointBitmap(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, int codepoint);





bitmap *createBitmap(u32 width, u32 height, u32 byteperpixel){
	bitmap *bm = (bitmap *)malloc(sizeof(bitmap));
	bzero(bm, sizeof(bitmap));
	bm->height = height;
	bm->width = width;
	bm->byteperpixel = byteperpixel;
	bm->map = (u8 *)malloc(width*height*byteperpixel);
	bzero(bm->map, width*height*byteperpixel);
	return bm;
}

void destroyBitmap(bitmap *bm){
	bzero(bm->map, bm->height * bm->width * bm->byteperpixel);
	free(bm->map);
	bzero(bm, sizeof(bitmap));
	free(bm);
}

color getPixel(bitmap *bm, u32 x, u32 y){
	if(bm->byteperpixel == 3){
		u8 r = *(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 0);
		u8 g = *(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 1);
		u8 b = *(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 2);
		return getColor(0, r, g, b);
	}else if(bm->byteperpixel == 4){
		u8 r = *(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 0);
		u8 g = *(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 1);
		u8 b = *(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 2);
		u8 a = *(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 3);
		return getColor(a, r, g, b);
	}
	return 0;
}

void setPixel(bitmap *bm, u32 x, u32 y, color c){
	if(bm->byteperpixel == 3){
		*(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 0) = getR(c);
		*(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 1) = getG(c);
		*(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 2) = getB(c);
	}else if(bm->byteperpixel == 4){
		*(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 0) = getR(c);
		*(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 1) = getG(c);
		*(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 2) = getB(c);
		*(bm->map + y*bm->width*bm->byteperpixel + x*bm->byteperpixel + 3) = getA(c);
	}
}

bitmap *createBitmapWithInit(u32 width, u32 height, u32 byteperpixel, color c){
	bitmap *bm = createBitmap(width, height, byteperpixel);
	u32 x, y;
	for(y=0; y<height; y++){
		for(x=0; x<width; x++){
			setPixel(bm, x, y, c);
		}
	}
	return bm;
}

u32 wstrlen(wchar *ws){
	u32 len = 0;
	while(*(ws+len)!='\0')
		len++;
	return len;
}


wchar *utf8_to_ucs2(char *code){
	wchar *ucs2 = (wchar *)malloc((strlen(code)+2)*sizeof(wchar));
	bzero(ucs2, (strlen(code)+2)*sizeof(wchar));
	s16 com = 1<<7;
	u32 x;
	for(x=0; x<=strlen(code); x++){
		char utf = code[x];
		u32 size = 0;
		u32 i = 0;
		u32 index = (utf&com) != 0;
		u16 binary[16];
		if(index == 0){///0xxxxxxx ==> 00000000 0xxxxxxxx
			for(; i < 8; ++i){
				binary[i] = 0;
			}
			for(; i < 16; ++i){
				binary[i] = (utf & 1 << (15 - i)) != 0;
			}
		}else if(utf&(1 << 5) == 0){// 110xxxxx 10yyyyyy ==> 00000xxx xxyyyyyy
			for(; i < 5; ++i){
				binary[i] = 0;
			}
			for(; i < 10; ++i){
				binary[i] = (utf&(1 << (9 - i))) != 0;
			}
			x += 1;
			utf = code[x];
			for(; i < 16; ++i){
				binary[i] = (utf&(1 << (15 - i))) != 0;
			}
		}else{//1110xxxx 10yyyyyy 10zzzzzz ==> xxxxyyyy yyzzzzzz
			for(; i < 4; ++i){
				binary[i] = (utf & 1 << (3 - i)) != 0;
			}
			x += 1;
			utf = code[x];
			for(; i < 10; ++i){
				binary[i] = (utf & 1 << (9 - i)) != 0;
			}
			x += 1;
			utf = code[x];
			for(; i < 16; ++i){
				binary[i] = (utf & 1 << (15 - i)) != 0;
			}
		}
		wchar ch = 0;
		for(i=0; i <16; i++){
			ch <<= 1;
			ch |= binary[i];
		}
		u32 len = wstrlen(ucs2);
		ucs2[len] = ch;
		ucs2[len+1] = 0;
	}
	return ucs2;
}

void fontPrint(font *f, bitmap *screen, s32 x, s32 y, char *text, color c, s32 maxWidth){
	wchar *wText = utf8_to_ucs2(text);
	u8 *charRaster = NULL;
	s32 bx, by, bw, bh;
	s32 ascent, descent, lineGap;
	s32 sx = 0, sy = 0;
	stbtt_GetFontVMetrics(f->info, &ascent, &descent, &lineGap);

	ascent *= f->scale;
	descent *= f->scale;
	lineGap *= f->scale;

	u32 i;
	for(i=0; i<wstrlen(wText); i++){
		if(wText[i] == '\n'){
			sy += ascent - descent + lineGap;
			sx = 0;
			continue;
		}

		stbtt_GetCodepointBitmapBox(f->info, wText[i], f->scale, f->scale, &bx, &by, &bw, &bh);

		s32 charWidth = bw - bx;
		s32 charHeight = bh - by;
		s32 oy = ascent + by;

		if(maxWidth > 0 && sx + charWidth > maxWidth) {
			sy += ascent - descent + lineGap;
			sx = 0;
		}

		charRaster = (u8 *)realloc(charRaster, charWidth*charHeight);
		
		stbtt_MakeCodepointBitmap(f->info, charRaster, charWidth, charHeight, charWidth, f->scale, f->scale, wText[i]);


		
		s32 advance;
		stbtt_GetCodepointHMetrics(f->info, wText[i], &advance, 0);
		s32 kerning = stbtt_GetCodepointKernAdvance(f->info, wText[i], wText[i+1]);
		s32 printLength = advance * f->scale + kerning * f->scale;
		
		s32 mx;
		for(mx=0; mx<printLength; mx++){
			if(charWidth+mx < printLength-mx){
				continue;
			}
			break;
		}
		
		s32 ix, iy;
		for(iy=0; iy<charHeight; iy++){
			for(ix=0; ix<charWidth; ix++){
				s32 xpos = x + sx + ix + mx;// + (printLength-charWidth)/2;
				s32 ypos = (y + sy + oy + iy) - 1;
				if(charRaster[ix+iy*charWidth]!=0 && xpos<screen->width && ypos<screen->height){
					u32 alpha = charRaster[ix+iy*charWidth];
					u32 invAlpha = 255 - alpha;
					color bgc = getPixel(screen, xpos, ypos);
					u8 bgr = getR(bgc);
					u8 bgg = getG(bgc);
					u8 bgb = getB(bgc);

					u8 r = (alpha * getR(c) + invAlpha * bgr) >> 8;
					u8 g = (alpha * getG(c) + invAlpha * bgg) >> 8;
					u8 b = (alpha * getB(c) + invAlpha * bgb) >> 8;

					setPixel(screen, xpos, ypos, getColor(0, r, g, b));
				}
			}
		}
		
		bzero(charRaster, charWidth*charHeight);
	
		sx += printLength;
	}
	free(charRaster);
	free(wText);
}

void fontSetSize(font *f, s32 pixels){
	f->scale = stbtt_ScaleForPixelHeight(f->info, pixels);
}

font *fontLoad(char *fontPath){
	// 打开字体文件并读取
	s32 fd = open(fontPath, O_RDONLY);
	if(fd==-1)
		return NULL;
	u32 bufferSize = lseek(fd, 0, SEEK_END);
	u8 *buffer = (u8 *)malloc(bufferSize);
	lseek(fd, 0, SEEK_SET);
	read(fd, buffer, bufferSize);
	close(fd);

	// 从内存读取
	font *f = (font *)malloc(sizeof(font));
	f->info = (stbtt_fontinfo *)malloc(sizeof(stbtt_fontinfo));
	if(!buffer || bufferSize==0)
		return NULL;
	if(stbtt_InitFont(f->info, buffer, 0) != 1)
		return NULL;
	f->buffer = buffer;
	f->scale = stbtt_ScaleForPixelHeight(f->info, 16);

	// 返回
	return f;
}

void fontUnload(font *f){
	free(f->info);
	free(f->buffer);
	free(f);
}

