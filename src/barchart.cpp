#include "barchart.h"
#include <QFontMetrics>
#include <QPolygon>

BarChart::BarChart(QQuickPaintedItem *parent) :
    AbstractChart(parent), pXAxis{this}, pYAxis{this}
{
}

QQmlListProperty<BarSeries> BarChart::series()
{
    return QQmlListProperty<BarSeries>(this, 0, &BarChart::appendSeries, &BarChart::seriesListLength,
                                       &BarChart::seriesAt, 0);
}

CategoryAxis *BarChart::xAxis()
{
    return &pXAxis;
}

StandartAxis *BarChart::yAxis()
{
    return &pYAxis;
}

QVariantList BarChart::generateLegend()
{
    QVariantList list;
    QVariantMap map;
    for(BarSeries *series: seriesList){
        map.clear();
        map.insert("name", series->name());
        map.insert("color", series->color());
        map.insert("strokeColor", series->strokePen()->color());
        map.insert("strokeWidth", series->strokePen()->width());
        list.append(map);
    }
    return list;
}

void BarChart::appendSeries(QQmlListProperty<BarSeries> *seriesList, BarSeries *series)
{
    BarChart *chart = qobject_cast<BarChart *>(seriesList->object);
    if (chart) {
        series->setParent(chart);
        chart->seriesList.append(series);
        connect(series, &BarSeries::dataChanged, chart, &BarChart::calculateDataRange);
        connect(series, &BarSeries::nameChanged, chart, &BarChart::emitLegendChanged);
        connect(series, &BarSeries::colorChanged, chart, &BarChart::emitLegendChanged);
        chart->emitLegendChanged();
        chart->calculateDataRange();
        emit chart->seriesChanged();
    }
}

int BarChart::seriesListLength(QQmlListProperty<BarSeries> *seriesList)
{
    BarChart *chart = qobject_cast<BarChart *>(seriesList->object);
    if(chart)
        return chart->seriesList.length();
    else return 0;
}

BarSeries *BarChart::seriesAt(QQmlListProperty<BarSeries> *seriesList, int index)
{
    BarChart *chart = qobject_cast<BarChart *>(seriesList->object);
    if(chart)
        return chart->seriesList.at(index);
    return nullptr;
}

void BarChart::paint(QPainter *painter)
{
    painter->setRenderHints(QPainter::Antialiasing, true);
    //Обчислення додаткових параметрів
    double xAxisLabelsHeight = QFontMetrics(pXAxis.labelsFont()).height();
    int labelsWidth{pXAxis.getWidthOfLongestLabel()};
    int maxSize {boundingRect().height()};
    maxSize -= xAxisLabelsHeight;
    maxSize -= 5;
    maxSize -= xAxisLabelsHeight;

    int scaleHeight{maxSize};

    int yAxisLabelsHeight { QFontMetrics(pYAxis.labelsFont()).height() };
    double maxSteps { qFloor(scaleHeight/(yAxisLabelsHeight*0.66)) };
    double minSteps { qFloor(scaleHeight/yAxisLabelsHeight*0.5) };

    int numberOfSteps;
    double stepValue, graphMin;
    calculateScale(scaleHeight, maxSteps, minSteps, upperValue, loverValue, numberOfSteps, stepValue, graphMin);
    pYAxis.setLabels(populateLabels(numberOfSteps+1, graphMin, stepValue));

    double xAxisLength {boundingRect().width()-pYAxis.getWidthOfLongestLabel()-pXAxis.getWidthOfLongestLabel()};
    double valueHop = qFloor(xAxisLength/pXAxis.labels().length());
    double barWidth {(valueHop-pXAxis.axisLine()->width()*2 -
                pXAxis.barValueSpacing()*2 - pXAxis.barDatasetSpacing()*(seriesList.length()-1)) /
                seriesList.length()};
    double yAxisPosX {boundingRect().width()-pXAxis.getWidthOfLongestLabel()/2.0-xAxisLength};
    double xAxisPosY {scaleHeight + xAxisLabelsHeight};
    double scaleHop {qFloor(scaleHeight/numberOfSteps)};

    //--------------------Малювання осей та сітки-------------------------------

    //Малювання осі Х
    painter->setPen(pXAxis.axisLine()->getPen());
    painter->drawLine(boundingRect().width()-pXAxis.getWidthOfLongestLabel()/2+5,xAxisPosY,
                      boundingRect().width()-pXAxis.getWidthOfLongestLabel()/2-xAxisLength-5,
                      xAxisPosY);
    painter->setFont(pXAxis.labelsFont());
    for(int i=0;i<pXAxis.labels().length();i++){
        painter->drawText(yAxisPosX+i*valueHop, xAxisPosY+4, valueHop,
                          xAxisLabelsHeight, Qt::AlignCenter, pXAxis.labels()[i]);
    }
    painter->setPen(pXAxis.gridLines()->getPen());
    for(int i=0;i<pXAxis.labels().length();i++){
        painter->drawLine(yAxisPosX+(1+i)*valueHop, xAxisPosY+3, yAxisPosX+(1+i)*valueHop,5);
    }

    //Малювання осі У
    pYAxis.drawVertical(painter, xAxisPosY, yAxisPosX, xAxisLength, scaleHop);

    //---------------------------------------Малювання графіка------------------------------------

    for(int i=0;i<seriesList.length();++i){
        painter->setPen(seriesList[i]->strokePen()->getPen());
        painter->setBrush(QBrush(seriesList[i]->color()));
        for(int j=0;j<seriesList[i]->data().length();++j){
            if(j>pXAxis.labels().length())
                break;
            double barOffset {yAxisPosX+pXAxis.barValueSpacing()+valueHop*j+barWidth*i+
                        pXAxis.barDatasetSpacing()*i+pXAxis.axisLine()->width()};

            QPolygon poligon;
            poligon << QPoint(barOffset,xAxisPosY);
            double valueOffset {calculateOffset(seriesList[i]->data()[j],
                                                numberOfSteps, stepValue, graphMin, scaleHop)};
            poligon << QPoint(barOffset,xAxisPosY-valueOffset);
            poligon << QPoint(barOffset+barWidth,xAxisPosY-valueOffset);
            poligon << QPoint(barOffset+barWidth,xAxisPosY);
            painter->drawPolyline(poligon);
            painter->drawPolygon(poligon);
        }
    }
}

void BarChart::calculateDataRange()
{
    upperValue = std::numeric_limits<int>::min();
    loverValue = std::numeric_limits<int>::max();

    for(BarSeries *i: seriesList){
        for(double j: i->data()){
            if(j>upperValue)
                upperValue = j;
            if(j<loverValue)
                loverValue = j;
        }
    }
    double offset {(upperValue-loverValue)*0.01};
    upperValue += offset;
    loverValue -= offset;
}

