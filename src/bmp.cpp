#include "bmp.h"

Bmp::Bmp(const char *fileName)
{
    this->name = new char[strlen(fileName)+1]();
    strcpy(this->name, fileName);

    setInfo();
}

Bmp::Bmp()
{
    name = nullptr;
}

Bmp::~Bmp()
{
    if (name)
        delete[] name;
}

void Bmp::display(int x, int y)
{
    FILE *fp = fopen(this->name, "r");
    if (!fp)
    {
        perror("打开图片失败");
        return;
    }
    fseek(fp, 54, SEEK_SET);

    int pad = (4-(width*bpp/8)%4)%4; // 每行末尾的无效数据的字节数
    char *rgb = (char *)calloc(1, (width*bpp/8+pad)*height);

    // 读取图片RGB内容
    while(1)
    {
        int n = fread(rgb, (width*bpp/8+pad)*height, 1, fp);

        if(n < 1) // 可能遇到文件尾，或者遇到错误
        {
            if(feof(fp))
            {
                break;
            }

            if(ferror(fp))
            {
                perror("读取图片数据失败");
                fclose(fp);
                return ;
            }
        }
    }

     // 让rgb指向图片的末行的首字节
    char *tmp = rgb + (width*bpp/8+pad)*(height-1);

    Lcd *lcd = Lcd::getInstance();

    char *temp_lcd = lcd->getAddr() + (x + y*lcd->getWidth()) *lcd->getBpp() / 8;

    // 将rgb中的图像数据，妥善地拷贝到显存中
    for(int j=0, lcd_offset = 0, rgb_offset = 0; j<height && j<lcd->getHeight(); j++)
    {
        // 让p指向下一行，rgb指向下一行
        lcd_offset = lcd->getWidth()*lcd->getBpp() / 8 * j;
        rgb_offset = (width*bpp/8 + pad)*j;

        // 从左到右显示一行图像
        for(int i=0; i<width && i<lcd->getWidth(); i++)
        {
            memcpy(temp_lcd +4*i + lcd_offset, tmp+3*i - rgb_offset, 3);
        }
    }

    free(rgb);
    fclose(fp);
}

char *Bmp::getRGB()
{
    FILE *fp = fopen(this->name, "r");
    if (!fp)
    {
        perror("打开图片失败");
        return nullptr;
    }
    fseek(fp, 54, SEEK_SET);

    int pad = (4-(width*bpp/8)%4)%4; // 每行末尾的无效数据的字节数
    char *rgb = (char *)calloc(1, (width*bpp/8+pad)*height);

    // 读取图片RGB内容
    while(1)
    {
        int n = fread(rgb, (width*bpp/8+pad)*height, 1, fp);

        if(n < 1) // 可能遇到文件尾，或者遇到错误
        {
            if(feof(fp))
            {
                break;
            }

            if(ferror(fp))
            {
                perror("读取图片数据失败");
                fclose(fp);
                return  nullptr;
            }
        }
    }

    char *photo = new char[width*height*3]();

     // 让rgb指向图片的末行的首字节
    char *tmp = rgb + (width*bpp/8+pad)*(height-1);

    // 将rgb中的图像数据，妥善地拷贝到photo中
    for(int j=0, photo_offset = 0, rgb_offset = 0; j<height; j++)
    {
        // 让p指向下一行，rgb指向下一行
        photo_offset = width*3*j;
        rgb_offset = (width*bpp/8 + pad)*j;

        // 从左到右显示一行图像
        for(int i=0; i<width; i++)
        {
            memcpy(photo +3*i + photo_offset, tmp+3*i - rgb_offset, 3);
        }
    }

    free(rgb);
    fclose(fp);

    return photo;
}

void Bmp::setBmp(const char *fileName)
{
    if (this->name)
        delete[] name;

    this->name = new char[strlen(fileName)+1]();
    strcpy(this->name, fileName);

    setInfo();
}

void Bmp::setInfo()
{
    FILE *fp = fopen(this->name, "r");
    if (!fp)
    {
        perror("打开图片失败");
        return;
    }

    // 读取图片格式头，获取其尺寸信息
    struct bitmap_header head;
    struct bitmap_info info;
    struct rgb_quad quad;

    fread(&head, sizeof(head), 1, fp);
    fread(&info, sizeof(info), 1, fp);
    if (info.compression)
        fread(&quad, sizeof(quad), 1, fp);

    this->width = info.width;
    this->height = info.height;
    this->bpp = info.bit_count;

    fclose(fp);
}
