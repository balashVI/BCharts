#include "calc.h"

#include <algorithm>

// deprecated
int Calc::vertexContInCircleSegment(double r, double startAngle, double endAngle)
{
    return segmentContInCircleSegment(r, startAngle, endAngle) + 2;
}

int Calc::segmentContInCircleSegment(double r, double startAngle, double endAngle)
{
    double l = r * (endAngle - startAngle);
    int segmentsCount = ceil(l / 5.0); // 1 segment each 5 pixels

    return std::max(1, segmentsCount);
}

double Calc::calculateOrderOfMagnitude(double x)
{
    return floor(log(x) / log(10));
}

QVector2D Calc::vector(QPointF a, QPointF b)
{
    double x = b.x() - a.x();
    double y = b.y() - a.y();
    return QVector2D(x, y);
}

#include <QDebug>
QVector2D Calc::vectorBisector(QVector2D a, QVector2D b)
{
    a.normalize();
    b.normalize();

    auto bisector = a + b;
    qDebug() << a <<b << bisector;
    return bisector.normalized();
}
