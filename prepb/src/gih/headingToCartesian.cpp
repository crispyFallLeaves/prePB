#include <cmath>
#include "fih/headingToCartesian.h"

double headingToCartesian(double headingDeg)
{
    // convert to radians
    return (90.0 - headingDeg) * M_PI / 180.0;
}