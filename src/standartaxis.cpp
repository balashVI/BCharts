#include "standartaxis.h"
#include <QPainter>

StandartAxis::StandartAxis(QQuickItem *parent) :
    AbstractAxis(parent)
{
}

void StandartAxis::drawVertical(QPainter *painter, double xAxisPosY, double yAxisPosX, double axisLength, double scaleHop)
{
    painter->setPen(pAxisPen->getPen());
    painter->drawLine(yAxisPosX, xAxisPosY+5, yAxisPosX, 5);
    painter->setPen(pGridLines->getPen());
    for(int i=1;i<pLabels.length();++i){
        painter->drawLine(yAxisPosX-3,xAxisPosY-i*scaleHop, yAxisPosX+axisLength+5,
                          xAxisPosY-i*scaleHop);
    }
    painter->setFont(pLabelsFont);
    int labelsHeight {QFontMetrics(pLabelsFont).height()};
    for(int i=0;i<pLabels.length();++i){
        painter->drawText(yAxisPosX-10-widthOfLongestLabel, xAxisPosY-i*scaleHop-labelsHeight/2,
                          widthOfLongestLabel, labelsHeight, Qt::AlignRight, pLabels[i]);
    }
}

void StandartAxis::drawHorizontal(QPainter *painter, double xAxisPosY, double yAxisPosX, double axisLength, double scaleHop)
{
    painter->setPen(pAxisPen->getPen());
    painter->drawLine(yAxisPosX-5,xAxisPosY, yAxisPosX+pLabels.length()*scaleHop,
                      xAxisPosY);
    painter->setPen(pGridLines->getPen());
    for(int i=1;i<pLabels.length();i++){
        painter->drawLine(yAxisPosX+i*scaleHop, xAxisPosY+4, yAxisPosX+i*scaleHop,5);
    }
    painter->setFont(pLabelsFont);
    int labelsHeight {QFontMetrics(pLabelsFont).height()};
    for(int i=0;i<pLabels.length();i++){
        painter->drawText(yAxisPosX+i*scaleHop-scaleHop/2.0, xAxisPosY+3, scaleHop,
                          labelsHeight, Qt::AlignCenter, pLabels[i]);
    }
}
