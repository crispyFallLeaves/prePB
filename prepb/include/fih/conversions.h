#pragma once
#include <string>
const double PI = 3.141592653589793;

double cartridgeToRatio(std::string cart);
double degToInch(double degrees, double cart, double gearRatio, double wheel);