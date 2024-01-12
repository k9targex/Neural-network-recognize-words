#include"Matrix.h"
#include<time.h>
void Matrix::Init(int numb_of_hid_neurons, int numb_of_input_neurons)
{
    row = numb_of_hid_neurons;
    column = numb_of_input_neurons;
    matrix = new double* [row];
    for (int i = 0; i < row; i++)
    {
        matrix[i] = new double[column];
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            matrix[i][j] = 0;
        }
    }
}
void Matrix::Rand()
{
    srand(time(NULL));
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            matrix[i][j] = ((rand() % 100) * 0.03) / (row + 35);
        }
    }
}
void Matrix::Multipl(Matrix& mas, double* neurons, double* Mult_Matrix, int numb_neurons, int start, int end)
{
    if (mas.column != numb_neurons)
    {
        throw std::out_of_range("we cant multiplie matrix!!!");
    }
    double tmp = 0;
    for (int i = start; i < end; i++)
    {
        for (int j = 0; j < mas.column; j++)
        {
            tmp += mas.matrix[i][j] * neurons[j];
        }
        Mult_Matrix[i] = tmp;
        tmp = 0;
    }
}
void Matrix::MultiTrans(Matrix& mas, double* neyrons, double* Mult_Matrix, int numb_neurons)
{
    if (mas.row != numb_neurons)
    {
         throw std::out_of_range("we cant multiplie matrix!!!");
    }
    double tmp = 0;
    for (int i = 0; i < mas.column; i++)
    {
        for (int j = 0; j < mas.row; j++)
        {
            tmp += mas.matrix[j][i] * neyrons[j];
        }
        Mult_Matrix[i] = tmp;
        tmp = 0;
    }
}
void Matrix::Sum(double* bias, double* Mult_Matrix, int numb_of_hid_neurons)
{
    for (int i = 0; i < numb_of_hid_neurons; i++)
    {
        Mult_Matrix[i] += bias[i];
    }
}
double& Matrix::GetElement(int i, int j) {
    return matrix[i][j];
}
