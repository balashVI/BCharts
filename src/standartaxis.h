#ifndef STANDARTAXIS_H
#define STANDARTAXIS_H

#include "abstractaxis.h"
//#include ""

class StandartAxis : public AbstractAxis
{
    Q_OBJECT
public:
    explicit StandartAxis(QQuickItem *parent = 0);

    void drawVertical(QPainter *painter, double xAxisPosY, double yAxisPosX, double axisLength, double scaleHop);
    void drawHorizontal(QPainter *painter, double xAxisPosY, double yAxisPosX, double axisLength, double scaleHop);

signals:

public slots:

};

#endif // STANDARTAXIS_H
