#ifndef GLU_H
#define GLU_H
#include<GL/glu.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include<stdio.h>
#endif

#ifndef STUDLIB_H
#define STUDLIB_H
#include<stdlib.h>
#endif

class Bmp
{
public:
    GLint     ImageWidth;
    GLint     ImageHeight;
    GLint     PixelLength;
    GLubyte* PixelData;
};

int Read(char *name,Bmp &p)
{
    FILE* pFile = fopen(name, "rb");
     if( pFile == 0 )
         exit(0);
     // 读取图象的大小信息
     fseek(pFile,18, SEEK_SET);
     fread(&p.ImageWidth, sizeof(p.ImageWidth), 1, pFile);
     fread(&p.ImageHeight, sizeof(p.ImageHeight), 1, pFile);
     // 计算像素数据长度
     p.PixelLength = p.ImageWidth * 3;
     while( p.PixelLength % 4 != 0 )
         ++p.PixelLength;
     p.PixelLength *=p.ImageHeight;
     // 读取像素数据
     p.PixelData = (GLubyte*)malloc(p.PixelLength);
     if( p.PixelData == 0 )
         exit(0);
     fseek(pFile, 54, SEEK_SET);
     fread(p.PixelData,p.PixelLength, 1, pFile);
     // 关闭文件
     fclose(pFile);
     return 0;
}

