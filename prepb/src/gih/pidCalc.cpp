#include "fih/pidCalc.h"
#include "fih/sgn.h"

// Turn PID constants
double kPTurn = 0;
double kDTurn = 0;
double FFTurn = 0;

// Linear PID constants  
double kPLinear = 0;
double kDLinear = 0;
double FFLinear = 0;

// Turn PID functions
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
}

double angularCalc(double error, double prevError)
{
    return (error * kPTurn + (error - prevError) * kDTurn + sgn(error) * FFTurn);
}


void setkPLinear(double kPL) 
{
    kPLinear = kPL; 
}

void setkDLinear(double kDL) 
{
    kDLinear = kDL;
}

void setFFLinear(double FFL)
{
    FFLinear = FFL;
}

double linearCalc(double error, double prevError)
{
    return (error * kPLinear + (error - prevError) * kDLinear + sgn(error) * FFLinear);
}