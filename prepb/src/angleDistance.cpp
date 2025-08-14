#include "fih/angleDistance.h"

double angleDistance(double a1, double a2)
{
    double angle = a1 - a2;
    if (angle > 180)
    {
        angle += -360;
    }
    else if (angle < -180)
    {
        angle += 360;
    }
    return angle;
}