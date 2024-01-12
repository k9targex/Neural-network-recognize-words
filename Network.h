#ifndef NETWORK_H
#define NETWORK_H

#pragma once
#include <QMessageBox>
#include<iostream>
#include"Matrix.h"
#include"ActivateFunction.h"

class Network
{
    int layers;
    int* neurons_on_layer;
    ActivateFunction function;
    Matrix* weight;
    double** neurons;
    double** error_of_neurons;
    double* bias;
    double** bias_weight;
public:
    double ForwardFeed();
    void BackPropogation(double predict);
    void WeightsUpdater(double lr);
    void PrintValues(int L);
    void NetworkInit(int conf);
    void DataInput(double* picture, int train);
    double SearchMaxIndex();
    void SaveWeight();
    int ReadWeight(int conf);

};

#endif // NETWORK_H
