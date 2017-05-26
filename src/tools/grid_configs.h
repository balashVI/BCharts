#ifndef GRID_CONFIGS_H
#define GRID_CONFIGS_H

#include <QObject>
#include <QColor>

class GridConfigs : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(uint lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:
    explicit GridConfigs(QObject *parent = 0);

    bool visible() const;
    void setVisible(bool visible);

    uint lineWidth() const;
    void setLineWidth(uint width);

    QColor color() const;
    void setColor(QColor color);

signals:
    void visibleChanged(bool visible);
    void lineWidthChanged(uint width);
    void colorChanged(QColor color);

private:
    bool pVisible;
    uint pLineWidth;
    QColor pColor;
};

#endif // GRID_CONFIGS_H
