#pragma once

// Turn PID constants
extern double kPTurn;
extern double kDTurn;
extern double FFTurn;

// Linear PID constants
extern double kPLinear;
extern double kDLinear;
extern double FFLinear;

// Turn PID functions
void setkPTurn(double kPT);
void setkDTurn(double kDT);
void setFFTurn(double FFT);
double angularCalc(double error, double prevError);

// Linear PID functions
void setkPLinear(double kPL);
void setkDLinear(double kDL);
void setFFLinear(double FFL);
double linearCalc(double error, double prevError);