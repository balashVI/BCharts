#ifndef LINESERIES_H
#define LINESERIES_H

#include "barseries.h"

class LineSeries : public BarSeries
{
    Q_OBJECT
public:
    explicit LineSeries(QQuickItem *parent = 0);

    Q_PROPERTY(bool drawPoints READ drawPoints WRITE setDrawPoints NOTIFY drawPointsChanged)

    void setDrawPoints(bool value);
    bool drawPoints() const;

protected:
    bool pDrawPoints;

signals:
    void drawPointsChanged();

};

#endif // LINESERIES_H
