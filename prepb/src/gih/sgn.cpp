#include "fih/sgn.h"

int sgn(double val)
{
    if (val > 0)
    {
        return 1;
    }
    if (val < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}