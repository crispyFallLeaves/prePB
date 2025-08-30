#include "fih/tickToInch.h"

double cartToTick(std::string cart)
{
    if (cart == "blue" || cart == "Blue")
    {
        return 300;
    }
    if (cart == "green" || cart == "Green")
    {
        return 900;
    }
    return 1800;
}

double tickToInch(double ticks, std::string cart, double wheelDia, double gearRatio)
{
    double ticksPerRotation = cartToTick(cart);
    double rotations = (ticks / ticksPerRotation);
    double wheelRotations = rotations * gearRatio;
    double inches = wheelRotations * wheelDia * 3.14159265;
    return inches;
}