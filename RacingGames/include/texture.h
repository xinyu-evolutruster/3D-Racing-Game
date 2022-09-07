#ifndef _TEXTURE_H_
#define _TEXTURE_H_


#ifndef OS_LINUX
#include <Windows.h>
#pragma execution_character_set("utf-8")
#endif
#include "gl/glut.h"
#include "gl/glu.h"
#include "gL/gl.h"

#include <iostream>
#include <string>
#include <cmath>
#include "mymodel.h"
using namespace std;


const double PI = acos(-1);
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
GLuint LoadTexture(const string filename);


#endif