#include "Network.h"
#include <QColorDialog>
#include <QFileDialog>
#include <fstream>
using namespace std;

void Network::NetworkInit(int conf)
{
    srand(time(NULL));
        if(conf==1) {
            layers = 3;
            neurons_on_layer = new int[layers];
            neurons_on_layer[0] = 784;
            neurons_on_layer[1] = 128;
            neurons_on_layer[2] = 26;
        }
        else if(conf==2){
            layers = 4;
            neurons_on_layer = new int[layers];
            neurons_on_layer[0] = 784;
            neurons_on_layer[1] = 512;
            neurons_on_layer[2] = 64;
            neurons_on_layer[3]=  26;
        }
        else if(conf==3)
        {
            layers = 6;
            neurons_on_layer = new int[layers];
            neurons_on_layer[0] = 784;//28*28
            neurons_on_layer[1] = 512;
            neurons_on_layer[2] = 256;
            neurons_on_layer[3] = 128;
            neurons_on_layer[4] = 64;
            neurons_on_layer[5] = 26;
        }
    weight = new Matrix[layers - 1];
    bias_weight = new double* [layers - 1];
    bias = new double[layers - 1];
    neurons = new double* [layers];
    error_of_neurons = new double* [layers];
    for (int i = 0; i < layers; i++)
    {
        neurons[i] = new double[neurons_on_layer[i]];
        error_of_neurons[i] = new double[neurons_on_layer[i]];
        if (i < layers - 1)
        {
            weight[i].Init(neurons_on_layer[i + 1], neurons_on_layer[i]);
            bias_weight[i] = new double[neurons_on_layer[i + 1]];
            weight[i].Rand();
            bias[i] = 1;
            for (int j = 0; j < neurons_on_layer[i + 1]; j++)
            {
                bias_weight[i][j] = ((rand() % 50) * 0.06) / (neurons_on_layer[i + 1] + 15);;
            }
        }
    }
}
void Network::DataInput(double* picture, int train)
{
    int DropOut;
    for (int i = 0; i < neurons_on_layer[0]; i++)
    {
        neurons[0][i] = picture[i];
        if (train)
        {
            DropOut = rand() % 100;
            if (DropOut < 20)
            {
                neurons[0][i] = 0;
            }
        }
    }

}
double Network::ForwardFeed()
{
    try {
        for (int i = 1; i < layers; i++)
        {


            int neuronsonlayer = neurons_on_layer[i];
            Matrix::Multipl(weight[i - 1], neurons[i - 1], neurons[i], neurons_on_layer[i - 1], 0, neuronsonlayer);
            Matrix::Sum(bias_weight[i - 1], neurons[i], neurons_on_layer[i]);
            function.ModRelu(neurons[i], neurons_on_layer[i]);
        }
        double predict_letter = SearchMaxIndex();
        return predict_letter;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        exit(1);
    }
    return 0;
}

void Network::BackPropogation(double predict)
{
    for (int i = 0; i < neurons_on_layer[layers - 1]; i++) {
        if (i != predict)
            error_of_neurons[layers - 1][i] =2* (-neurons[layers - 1][i] * function.ModReluDerivate(neurons[layers - 1][i]));
        else
            error_of_neurons[layers - 1][i] = 2*((1.0 - neurons[layers - 1][i]) * function.ModReluDerivate(neurons[layers - 1][i]));
    }
    for (int k = layers - 2; k > 0; k--) {
        Matrix::MultiTrans(weight[k], error_of_neurons[k + 1], error_of_neurons[k], neurons_on_layer[k + 1]);

        for (int j = 0; j < neurons_on_layer[k]; j++)
            error_of_neurons[k][j] *= function.ModReluDerivate(neurons[k][j]);
    }
}
void Network::PrintValues(int L) {
    for (int j = 0; j < neurons_on_layer[layers]; j++) {
        std::cout << j << " " << neurons[L][j] << std::endl;
    }
}
void Network::WeightsUpdater(double learning_rate) {
    for (int i = 0; i < layers - 1; ++i) {
        for (int j = 0; j < neurons_on_layer[i + 1]; ++j) {
            for (int k = 0; k < neurons_on_layer[i]; ++k) {
                weight[i].GetElement(j, k) += neurons[i][k] * error_of_neurons[i + 1][j] * learning_rate;
            }
        }
    }
    for (int i = 0; i < layers - 1; i++) {
        for (int k = 0; k < neurons_on_layer[i + 1]; k++) {
            bias_weight[i][k] += error_of_neurons[i + 1][k] * learning_rate;
        }
    }
}
double Network::SearchMaxIndex()
{
    double max = neurons[layers - 1][0], tmp;
    double index = 0;
    char c;

    for (int i = 1; i < neurons_on_layer[layers - 1]; i++)
    {
        tmp = neurons[layers - 1][i];
        //c = i + 65;
        //std::cout << c << ':' << tmp << std::endl;
        if (tmp > max)
        {
            max = tmp;
            index = i;
        }
    }
    return index;
}
void Network::SaveWeight()
{
    std::ofstream out;
    out.open("weight.txt");
    if (out.is_open())
    {
        for (int i = 0; i < layers - 1; i++)
        {
            for (int j = 0; j < neurons_on_layer[i + 1]; j++)
            {
                for (int k = 0; k < neurons_on_layer[i]; k++)
                {
                    out << weight[i].GetElement(j, k) << " ";
                    //std::cout << weight[i].GetElement(j, k);/
                }

            }
        }
        for (int i = 0; i < layers - 1; i++) {
            for (int k = 0; k < neurons_on_layer[i + 1]; k++) {
                out << bias_weight[i][k] << " ";
            }
        }

    }
    else
    {
        std::cout << "Cant open file";
    }
}
int Network::ReadWeight(int conf)
{
    std::ifstream out;
    if(conf==1)
    {
        QString fileName = "weight1.txt";
        QString currentDir = QDir::currentPath();
        QString filePath = currentDir + "/" + fileName;
        out.open(filePath.toStdString());
    }
    else if(conf==2)
    {
        QString fileName = "weight2.txt";
        QString currentDir = QDir::currentPath();
        QString filePath = currentDir + "/" + fileName;
        out.open(filePath.toStdString());
    }
    else if(conf==3)
    {
        QString fileName = "weight3.txt";
        QString currentDir = QDir::currentPath();
        QString filePath = currentDir + "/" + fileName;
        out.open(filePath.toStdString());
    }
    if (out.is_open())
    {
        for (int i = 0; i < layers - 1; i++)
        {
            for (int j = 0; j < neurons_on_layer[i + 1]; j++)
            {
                for (int k = 0; k < neurons_on_layer[i]; k++)
                {

                    out >> weight[i].GetElement(j, k);
                }

            }
        }
        for (int i = 0; i < layers - 1; i++) {
            for (int k = 0; k < neurons_on_layer[i + 1]; k++) {
                out >> bias_weight[i][k];
            }
        }
    }
    else
    {
        return 0;
//        std::cout << "Cant open file";
    }
    return 1;
}
