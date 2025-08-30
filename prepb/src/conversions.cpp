#include "fih/conversions.h"
#include <algorithm>
#include <cctype>
#include <string>

double cartridgeToRatio(std::string cart)
{
    std::transform(cart.begin(), cart.end(), cart.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });

    if (cart == "red")
    {
        return 1.0 / 36.0;
    }
    if (cart == "green")
    {
        return 1.0 / 18.0;
    }
    if (cart == "blue")
    {
        return 1.0 / 6.0;
    }
    return 0;
}

double degToInch(double degrees, std::string cart, double gearRatio, double wheel)
{
    return (degrees / 180) * cartridgeToRatio(cart) * gearRatio * wheel * PI;
}