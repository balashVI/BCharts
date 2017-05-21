#include <QDebug>

#include "base_chart.h"

BaseChart::BaseChart(QQuickItem *parent) :
    QQuickItem(parent),
    mForceUpdate{false}
{
    setClip(true);
}

double BaseChart::calculateOrderOfMagnitude(double x)
{
    return qFloor(log(x)/log(10));
}

void BaseChart::calculateScale(double drawingHeight, double maxSteps, double minSteps, double maxValue, double minValue,
                                   int &numberOfSteps, double &stepValue, double &graphMin)
{
    double valueRange {maxValue - minValue};
    stepValue = pow(10, calculateOrderOfMagnitude(valueRange));
    graphMin = floor(minValue/stepValue)*stepValue;
    double graphMax {ceil(maxValue/stepValue)*stepValue};
    double graphRange {graphMax-graphMin};
    numberOfSteps = qRound(graphRange/stepValue);
    if(!numberOfSteps) numberOfSteps=1;
    while(numberOfSteps<minSteps || numberOfSteps>maxSteps){
        if(numberOfSteps<minSteps){
            stepValue /= 2.0;
            numberOfSteps = qRound(graphRange/stepValue);
        } else {
            stepValue *= 2.0;
            numberOfSteps = qRound(graphRange/stepValue);
        }
    }
}

QList<QString> BaseChart::populateLabels(int numberOfSteps, double graphMin, double stepValue)
{
    QList<QString> res = QList<QString>();
    int numberOfDecimalPlaces;
    double intpart;
    if(modf(stepValue, &intpart)!=0)
        numberOfDecimalPlaces=QString::number(stepValue).split('.')[1].length();
    else
        numberOfDecimalPlaces=0;
    for(int i=0;i<numberOfSteps;++i){
        res.push_back(QString::number(graphMin + stepValue*i, 'f', numberOfDecimalPlaces));
    }
    return res;
}

double BaseChart::calculateOffset(double value, int steps, double stepValue, double graphMin, double scaleHop)
{
    double scalingFactor {(value-graphMin)/(steps*stepValue)};
    if(scalingFactor>1)
        scalingFactor = 1;
    else if(scalingFactor<0)
        scalingFactor = 0;
    return scaleHop*steps*scalingFactor;
}

void BaseChart::emitLegendChanged()
{
    emit legendChanged();
}
