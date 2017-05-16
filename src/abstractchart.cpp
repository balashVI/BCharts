#include "abstractchart.h"
#include <QDebug>

AbstractChart::AbstractChart(QQuickPaintedItem *parent) :
    QQuickPaintedItem(parent)
{
    setClip(true);
}

QVariantList AbstractChart::generateLegend()
{

}

void AbstractChart::paint(QPainter *painter)
{

}

double AbstractChart::calculateOrderOfMagnitude(double x)
{
    return qFloor(log(x)/log(10));
}

void AbstractChart::calculateScale(double drawingHeight, double maxSteps, double minSteps, double maxValue, double minValue,
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

QList<QString> AbstractChart::populateLabels(int numberOfSteps, double graphMin, double stepValue)
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

double AbstractChart::calculateOffset(double value, int steps, double stepValue, double graphMin, double scaleHop)
{
    double scalingFactor {(value-graphMin)/(steps*stepValue)};
    if(scalingFactor>1)
        scalingFactor = 1;
    else if(scalingFactor<0)
        scalingFactor = 0;
    return scaleHop*steps*scalingFactor;
}

void AbstractChart::emitLegendChanged()
{
    emit legendChanged();
}
