#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include"gl/glut.h"
#include "texture.h"
#define BITMAP_ID 0x3D42
//读纹理图片  
unsigned char *LoadBitmapFile(const char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;    // 文件指针  
	BITMAPFILEHEADER bitmapFileHeader;    // bitmap文件头  
	unsigned char    *bitmapImage;        // bitmap图像数据  
	int    imageIdx = 0;        // 图像位置索引  
	unsigned char    tempRGB;    // 交换变量  

								// 以“二进制+读”模式打开文件filename   
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL) {
		printf("file not open\n");
		return NULL;
	}
	// 读入bitmap文件图  
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	// 验证是否为bitmap文件  
	if (bitmapFileHeader.bfType != BITMAP_ID) {
		fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
		return NULL;
	}
	// 读入bitmap信息头  
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	// 将文件指针移至bitmap数据  
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	// 为装载图像数据创建足够的内存  
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
	// 验证内存是否创建成功  
	if (!bitmapImage) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	// 读入bitmap图像数据  
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
	// 确认读入成功  
	if (bitmapImage == NULL) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}
	//由于bitmap中保存的格式是BGR，下面交换R和B的值，得到RGB格式  
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) {
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}
	// 关闭bitmap图像文件  
	fclose(filePtr);
	return bitmapImage;
}

GLuint LoadTexture(const string filename) {
	BITMAPINFOHEADER bitmapInfoHeader;                                 // bitmap信息头  
	unsigned char*   bitmapData;                                       // 纹理数据
	const char* fp = filename.c_str();
	bitmapData = LoadBitmapFile(fp, &bitmapInfoHeader);
	GLuint id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	GLenum image_format = GL_RGB;
	GLint internal_format = GL_BGRA_EXT;

	glTexImage2D(GL_TEXTURE_2D, 0, image_format, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight, 0, internal_format, GL_UNSIGNED_BYTE, bitmapData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	return id;
}


