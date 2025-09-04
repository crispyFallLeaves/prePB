#include "fih/angleDistance.h"

double angleDistance(double a1, double a2)
{
    double angle = a1 - a2;
    while (angle > 180)
    {
        angle += -360;
    }
    while (angle < -180)
    {
        angle += 360;
    }
    return angle;
}