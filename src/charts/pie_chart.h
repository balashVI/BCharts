#ifndef PIE_CHART_H
#define PIE_CHART_H

#include "base_chart.h"

class PieSlice;

///
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

    Q_CLASSINFO("DefaultProperty", "slices")

    Q_PROPERTY(QQmlListProperty<PieSlice> slices READ slices NOTIFY slicesChanged())
    Q_PROPERTY(double angleOffset READ angleOffset WRITE setAngleOffset NOTIFY angleOffsetChanged)

public:
    explicit PieChart(QQuickItem *parent = 0);


    QQmlListProperty<PieSlice> slices();

    double angleOffset() const;
    void setAngleOffset(double value);

    Q_INVOKABLE virtual QVariantList generateLegend() override;

    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

signals:
    void slicesChanged();
    void angleOffsetChanged();

protected:
    static void appendSlice(QQmlListProperty<PieSlice> *slicesList, PieSlice *slice);
    static int slicesListLength(QQmlListProperty<PieSlice> *slicesList);
    static PieSlice *sliceAt(QQmlListProperty<PieSlice> *slicesList, int index);

protected:
    QList<PieSlice *> slicesList;

private:
    double pAngleOffset;
    double sumSliceValue;

public slots:
    void calculateDataRange();

};

#endif // PIE_CHART_H
