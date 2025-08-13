#pragma once

extern double kPTurn;
extern double kDTurn;
extern double FFTurn;

void setkPTurn(double kPT);
void setkDTurn(double kDT);
void setFFTurn(double FFT);

double angularCalc(double error, double prevError);