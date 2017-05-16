#include "chartpen.h"

ChartPen::ChartPen(QQuickItem *parent) :
    QQuickItem(parent)
{
    pen.setColor("#444444");
}

Qt::PenCapStyle ChartPen::capStyle() const
{
    return pen.capStyle();
}

void ChartPen::setCapStyle(Qt::PenCapStyle value)
{
    pen.setCapStyle(value);
    emit capStyleChanged();
}

int ChartPen::width() const
{
    return pen.width();
}

void ChartPen::setWidth(int newWidth)
{
    pen.setWidth(newWidth);
    emit widthChanged();
}

QColor ChartPen::color() const
{
    return pen.color();
}

void ChartPen::setColor(const QColor &newColor)
{
    pen.setColor(newColor);
    emit colorChanged();
}

double ChartPen::dashOffset() const
{
    return pen.dashOffset();
}

void ChartPen::setDashOffset(double offset)
{
    pen.setDashOffset(offset);
    emit dashOffsetChanged();
}

QList<double> ChartPen::dashPattern() const
{
    return QList<double>::fromVector(pen.dashPattern());
}

void ChartPen::setDashPattern(const QList<double> &pattern)
{
    pen.setDashPattern(QVector<double>::fromList(pattern));
    emit dashPatternChanged();
}

Qt::PenJoinStyle ChartPen::joinStyle() const
{
    return pen.joinStyle();
}

void ChartPen::setJoinStyle(Qt::PenJoinStyle style)
{
    pen.setJoinStyle(style);
    emit joinStyleChanged();
}

double ChartPen::miterLimit() const
{
    return pen.miterLimit();
}

void ChartPen::setMiterLimit(double limit)
{
    pen.setMiterLimit(limit);
    emit miterLimitChanged();
}

Qt::PenStyle ChartPen::style() const
{
    return pen.style();
}

void ChartPen::setStyle(Qt::PenStyle style)
{
    pen.setStyle(style);
    emit styleChanged();
}

const QPen &ChartPen::getPen() const
{
    return pen;
}
