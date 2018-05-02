#ifndef __DITHER_EX_H__
#define __DITHER_EX_H__
#include<ac_int.h>
#include<ac_channel.h>
#include<iostream>
#include<fstream>
#include<iomanip>
#include <math.h>

#include "cnn.h"
#include "bitmap_image.h"

#define N_IMG 2
#define WIDTH 512
#define HIEGHT 512
#define BIT_INP 8
#define BIT_OUT 1
#define EXP 2.71828182846
struct cifar10
{
char lable;
unsigned char r[1024];
unsigned char g[1024];
unsigned char b[1024];
};

void CNN(tansor< 32, 32, 3, float >  &,tansor< 1, 1, 10, float >  &);

#endif
