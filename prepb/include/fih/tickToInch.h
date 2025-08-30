#pragma once
#include <string>

double cartToTick(std::string cart);

double tickToInch(double ticks, std::string cart, double wheelDia, double gearRatio);