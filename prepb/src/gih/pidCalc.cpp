#include "fih/pidCalc.h"
#include "fih/sgn.h"

double kPTurn = 0;
double kDTurn = 0;
double FFTurn = 0;

void setkPTurn(int kPT)
{
    kPTurn = kPT;
}
void setkDTurn(int kDT)
{
    kDTurn = kDT;
}

void setFFTurn(int FFT)
{
    FFTurn = FFT;
};

double angularCalc(double error, double prevError)
{
    return (error * kPTurn + (prevError-error) * kDTurn + sgn(error) * FFTurn);
}