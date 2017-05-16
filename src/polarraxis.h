#ifndef POLARRAXIS_H
#define POLARRAXIS_H

#include "abstractaxis.h"

class PolarRAxis : public AbstractAxis
{
    Q_OBJECT
public:
    explicit PolarRAxis(QQuickItem *parent = 0);

    Q_PROPERTY(bool drawLabelsBackground READ drawLabelsBackground WRITE setDrawLabelsBackground NOTIFY drawLabelsBackgroundChanged)

    Q_PROPERTY(QColor labelsBackgroundColor READ labelsBackgroundColor WRITE setLabelsBackgroundColor NOTIFY labelsBackgroundColorChanged)

    QColor labelsBackgroundColor() const;
    void setLabelsBackgroundColor(QColor value);

    bool drawLabelsBackground() const;
    void setDrawLabelsBackground(bool value);

private:
    bool pShowLabelsBackground;
    QColor pLabelsBackgroundColor;

signals:
    void drawLabelsBackgroundChanged();
    void labelsBackgroundColorChanged();

public slots:
};

#endif // POLARRAXIS_H
