#ifndef CONVERT_H
#define CONVERT_H

#pragma once
#include"CImg.h"
#include<iostream>
#include <stack>

#include<fstream>
struct pixel
{
    int letter;
    double black;
    int id;
    bool trash;

};

pixel** Init(double* img, int length, int width);
void _paint(int i, int j, int width, int height, pixel** mas, int ID, int* Xmax, int* Xmin, int* Ymax, int* Ymin, int* PixelCounter);
double* Centered(pixel** mas, int Xmax, int Xmin, int Ymax, int Ymin);
double* Convert(const char* file, int* length, int* width);
double GetBackground(const char* filename, int x, int y);


#endif
