#include "ActivateFunction.h"
void ActivateFunction::ModRelu(double* NeuronValue, int NeuronsOnLayer)
{
    for (int i = 0; i < NeuronsOnLayer; i++)
    {
        if (NeuronValue[i] < 0)
            NeuronValue[i] *= 0.01;
        if (NeuronValue[i] > 1)
            NeuronValue[i] = 1 + 0.01 * (NeuronValue[i] - 1.);

    }
}
void ActivateFunction::ModReluDerivate(double* NeuronValue, int NeuronsOnLayer)
{
    for (int i = 0; i < NeuronsOnLayer; i++)
    {
        if (NeuronValue[i] < 0 ||
            NeuronValue[i] > 1)
            NeuronValue[i] = 0.01;
        else
            NeuronValue[i] = 1;
    }

}

double ActivateFunction::ModReluDerivate(double NeuronValue)
{
    if (NeuronValue < 0 ||
        NeuronValue > 1)
        return 0.01;
    else
        return NeuronValue;
}
