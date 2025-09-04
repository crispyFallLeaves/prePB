#include "fih/getDistance.h"


int getDistance(pros::Distance &distance)
{
    std::vector<int> distMeasurements;
    int loops = 10;
    for (int i = 0; i < loops; i++)
    {
        distMeasurements.push_back(distance.get());
        pros::delay(5);
    }
    if (loops % 2) // odd number
    {
        std::nth_element(distMeasurements.begin(), distMeasurements.begin() + (loops / 2), distMeasurements.end());
        return distMeasurements.at(loops / 2);
    }
    else
    { // even number
        std::nth_element(distMeasurements.begin(), distMeasurements.begin() + (loops / 2), distMeasurements.end());
        std::nth_element(distMeasurements.begin(), distMeasurements.begin() + (loops / 2) - 1, distMeasurements.end());
        return (distMeasurements.at((loops / 2)) + distMeasurements.at((loops / 2) - 1)) / 2;
    }
}