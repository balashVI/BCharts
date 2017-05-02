#ifndef PIECHART_H
#define PIECHART_H

#include "../base/basechart.h"
#include "pieslice.h"

///
/// \brief Кругова діаграма
///
/// Малює кругову діаграму. Приклад використання:
/// \code
/// ...
/// PieChart{
///     anchors.fill: parent
///     series: [
///         PieSeries{
///         },
///         PieSeries{
///         }
///     ]
/// }
/// ...
/// \endcode
///
class PieChart : public BaseChart
{
    Q_OBJECT
public:
    explicit PieChart(QQuickItem *parent = 0);

    Q_PROPERTY(QQmlListProperty<PieSlice> slices READ slices NOTIFY slicesChanged())
    QQmlListProperty<PieSlice> slices();
    Q_CLASSINFO("DefaultProperty", "slices")

    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;

    Q_PROPERTY(double angleOffset READ angleOffset WRITE setAngleOffset NOTIFY angleOffsetChanged)
    double angleOffset() const;
    void setAngleOffset(double value);


//    Q_INVOKABLE virtual QVariantList generateLegend() override;

protected:
    static void appendSlice(QQmlListProperty<PieSlice> *slicesList, PieSlice *slice);
    static int slicesListLength(QQmlListProperty<PieSlice> *slicesList);
    static PieSlice *sliceAt(QQmlListProperty<PieSlice> *slicesList, int index);
    QList<PieSlice *> slicesList;

private:
    double pAngleOffset;
    double sumSliceValue;

signals:
    void slicesChanged();
    void angleOffsetChanged();

public slots:
    void calculateDataRange();

};

#endif // PIECHART_H
