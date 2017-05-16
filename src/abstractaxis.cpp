#include "abstractaxis.h"
#include <QDebug>

AbstractAxis::AbstractAxis(QQuickItem *parent) :
    QQuickItem(parent), pAxisPen{new ChartPen(this)}, pGridLines{new ChartPen(this)},
    pLabelsVisible{true}
{
    pLabelsFont.setPointSize(9);
}

void AbstractAxis::setLabelsVisible(bool value)
{
    pLabelsVisible = value;
    emit labelsVisibleChanged();
}

bool AbstractAxis::labelsVisible() const
{
    return pLabelsVisible;
}

void AbstractAxis::setLabelsColor(const QColor &value)
{
    pLabelsColor = value;
    emit labelsColorChanged();
}

const QColor &AbstractAxis::labelsColor() const
{
    return pLabelsColor;
}

void AbstractAxis::setLabelsFont(QFont &value)
{
    pLabelsFont = value;
    emit labelsFontChanged();
}

QFont AbstractAxis::labelsFont() const
{
    return pLabelsFont;
}

void AbstractAxis::setGridLines(ChartPen *value)
{
    if(value){
        pGridLines->deleteLater();
        pGridLines=value;
        emit gridLinesChanged();
    }
}

ChartPen *AbstractAxis::gridLines() const
{
    return pGridLines;
}

void AbstractAxis::setAxisLine(ChartPen *value)
{
    if(value){
        pAxisPen->deleteLater();
        pAxisPen=value;
        emit axisLineChanged();
    }
}

ChartPen *AbstractAxis::axisLine() const
{
    return pAxisPen;
}

void AbstractAxis::setLabels(QList<QString> in)
{
    pLabels = std::move(in);
    calculateWidthOfLongestLabel();
    emit labelsChanged();
}

const QList<QString>& AbstractAxis::labels() const
{
    return pLabels;
}

double AbstractAxis::getWidthOfLongestLabel()
{
    return widthOfLongestLabel;
}

void AbstractAxis::calculateWidthOfLongestLabel()
{
    int labelWidth;
    widthOfLongestLabel = 0;
    QFontMetrics fm = QFontMetrics(pLabelsFont);
    for(int i=0;i<pLabels.length();++i){
        labelWidth = fm.width(pLabels[i]);
        if(labelWidth > widthOfLongestLabel)
            widthOfLongestLabel = labelWidth;
    }
    widthOfLongestLabel += 10;
}
