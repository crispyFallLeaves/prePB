#include "fih/centidegreeToInch.h"

double centidegreeToInch(double centidegree, double wheelDia)
{
    double rotations = centidegree / 36000;
    return rotations * wheelDia;
}