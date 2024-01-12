#ifndef ACTIVATEFUNCTION_H
#define ACTIVATEFUNCTION_H

#pragma once
#include <iostream>
class ActivateFunction
{
public:
    void ModRelu(double* NeuronValue, int NeuronsOnLayer);
    void ModReluDerivate(double* NeuronValue, int NeuronsOnLayer);
    double ModReluDerivate(double NeuronValue);
};

#endif // ACTIVATEFUNCTION_H
