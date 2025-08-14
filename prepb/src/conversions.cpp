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
        return 1 / 36;
    }
    if (cart == "green")
    {
        return 1 / 18;
    }
    if (cart == "blue")
    {
        return 1 / 6;
    }
    return 0;
}

double degToInch(double degrees, double cart, double gearRatio, double wheel)
{
    return degrees/360 * cart * gearRatio * wheel * PI;
}