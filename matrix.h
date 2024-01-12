#ifndef MATRIX_H
#define MATRIX_H

#include<iostream>
#include<stdio.h>
class Matrix
{
    double** matrix;
    int row, column;
public:
    static void Multipl(Matrix& mas, double* neurons, double* Mult_Matrix, int numb_neurons, int start, int end);
    static void MultiTrans(Matrix& mas, double* neyrons, double* Mult_Matrix, int numb_neurons);
    static void Sum(double* bias, double* Mult_Matrix, int numb_of_hid_neurons);
    double& operator()(int i, int j);
    double& GetElement(int i, int j);
    void Init(int numb_of_hid_neurons, int numb_of_input_neurons);
    void Rand();
};


#endif // MATRIX_H
