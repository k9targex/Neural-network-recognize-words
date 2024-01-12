#ifndef SOURCE_H
#define SOURCE_H
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <QMessageBox>
//#include "mymessagebox.h"
#include "Network.h"
#include "Convert.h"
#include <fstream>
#include <string>
#include <conio.h>
#include <time.h>
#include <stdio.h>
#include "math.h"
#include <vector>
#include <algorithm>
#include <random>

using namespace std;
using namespace cimg_library;
//int examples = 387400;
struct data_picture
{
    double* picture;
    double letter;
};
int Mama();
data_picture* ReadPicture();
QString Study(Network object,data_picture* base);
void Recognition(Network object, double* mas, int size,bool space,string &finalstr);
void Test(Network object, data_picture* base);
data_picture* OurData();
data_picture* DataTest();

string ReadWord(Network T800,string path);
#endif // SOURCE_H
