#ifndef CALC_H
#define CALC_H

#include <cmath>
#include <QVector2D>

class Calc
{
  public:
    static int vertexContInCircleSegment(double r, double startAngle, double endAngle);
    static int segmentContInCircleSegment(double r, double startAngle = 0, double endAngle = 2 * M_PI);
    static double calculateOrderOfMagnitude(double x);

    static QVector2D vector(QPointF a, QPointF b);
    static QVector2D vectorBisector(QVector2D a, QVector2D b);
};

#endif // CALC_H
