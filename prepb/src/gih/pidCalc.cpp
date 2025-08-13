#include "fih/pidCalc.h"
#include "fih/sgn.h"

double kPTurn = 0;
double kDTurn = 0;
double FFTurn = 0;

void setkPTurn(double kPT)
{
    kPTurn = kPT;
}
void setkDTurn(double kDT)
{
    kDTurn = kDT;
}

void setFFTurn(double FFT)
{
    FFTurn = FFT;
};

double angularCalc(double error, double prevError)
{
    return (error * kPTurn + (error-prevError) * kDTurn + sgn(error) * FFTurn);
}