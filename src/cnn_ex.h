#ifndef __CNN_EX_H__
#define __CNN_EX_H__
#include<iostream>
#include<fstream>
#include<iomanip>
#include <math.h>

#include "cnn.h"
#include "bitmap_image.h"
//#define TEST
#define N_IMG 10
#define TOP_N 3
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
	
enum cifar_l
{
airplane 	= 0,
automobile 	= 1,
bird		= 2,
cat		= 3,
deer		= 4,
dog		= 5,
frog		= 6,
horse		= 7,
ship		= 8,
truck		= 9
};

#ifdef TEST
void CNN_test(tansor< 32, 32, 3, float >  &,tansor< 1, 1, 10, float >  &);
#else
void CNN(tansor< 32, 32, 3, float >  &,tansor< 1, 1, 10, float >  &);
#endif
#endif
