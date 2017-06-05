#ifndef CALC_H
#define CALC_H

#include <cmath>

class Calc
{
  public:
    static int vertexContInCircleSegment(double r, double startAngle, double endAngle);
    static int segmentContInCircleSegment(double r, double startAngle = 0, double endAngle = 2 * M_PI);
    static double calculateOrderOfMagnitude(double x);
};

#endif // CALC_H
