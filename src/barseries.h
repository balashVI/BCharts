#ifndef BARSERIES_H
#define BARSERIES_H

#include "abstractseries.h"

/**
 * @brief Стовпчикова серія
 *
 * Малює серії стовпчикових графіків
 */
class BarSeries : public AbstractSeries
{
    Q_OBJECT
public:
    ///Конструктор класу
    explicit BarSeries(QQuickItem *parent = 0);

    ///Містить список даних
    Q_PROPERTY(QList<double> data READ data WRITE setData NOTIFY dataChanged)

    ///Містить налаштування лінії обведення
    Q_PROPERTY(ChartPen* strokePen READ strokePen WRITE setStrokePen NOTIFY strokePenChanged)

    ChartPen* strokePen() const;
    void setStrokePen(ChartPen* value);

    const QList<double> &data() const;
    void setData(QList<double> value);

protected:
    QList<double> pData;
    ChartPen *pStrokePen;

signals:
    void dataChanged();
    void strokePenChanged();

public slots:

};

#endif // BARSERIES_H
