#include "fih/curveFunction.h"
#include <cmath>

double curveFunction(int x, double t)
{
    double exp1 = std::exp(-t / 10.0);
    double exp2 = std::exp((std::abs(x) - 127) / 10.0);
    double result = (exp1 + exp2 * (1 - exp1)) * x;
    return result;
}
