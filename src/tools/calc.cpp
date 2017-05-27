#include "calc.h"

#include <cmath>

int Calc::vertexContInCircleSegment(double r, double startAngle, double endAngle)
{
    double l = r * (endAngle - startAngle);
    int segmentsCount = ceil(l / 5.0); // 1 segment each 5 pixels

    return segmentsCount + 2;
}

double Calc::calculateOrderOfMagnitude(double x)
{
    return floor(log(x) / log(10));
}
