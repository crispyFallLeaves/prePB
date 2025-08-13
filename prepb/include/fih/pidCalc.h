#pragma once

extern double kPTurn;
extern double kDTurn;
extern double FFTurn;

void setkPTurn(int kPT);
void setkDTurn(int kDT);
void setFFTurn(int FFT);

double angularCalc(double error, double prevError);