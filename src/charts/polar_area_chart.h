#ifndef POLAR_AREA_CHART_H
#define POLAR_AREA_CHART_H

#include "base_chart.h"

class PolarArea;
class BaseAxis;

///
/// \code
/// ...
/// PolarAreaChart{
///     anchors.fill: parent
///     areas: [
///         PolarArea{
///         },
///         PolarArea{
///         }
///     ]
/// }
/// ...
/// \endcode
///
class PolarAreaChart : public BaseChart
{
    Q_OBJECT

    Q_CLASSINFO("DefaultProperty", "areas")

    Q_PROPERTY(QQmlListProperty<PolarArea> areas READ areas NOTIFY areasChanged())
    Q_PROPERTY(double angleOffset READ angleOffset WRITE setAngleOffset NOTIFY angleOffsetChanged)

public:
    explicit PolarAreaChart(QQuickItem *parent = 0);

    QQmlListProperty<PolarArea> areas();

    double angleOffset() const;
    void setAngleOffset(double value);

    Q_INVOKABLE virtual QVariantList generateLegend() override;

    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

signals:
    void areasChanged();
    void angleOffsetChanged();

protected:
    static void appendArea(QQmlListProperty<PolarArea> *areasList, PolarArea *area);
    static int areasListLength(QQmlListProperty<PolarArea> *areasList);
    static PolarArea *areaAt(QQmlListProperty<PolarArea> *areasList, int index);

protected:
    QList<PolarArea *> mAreasList;
    BaseAxis *pAxis;

private slots:
    void updateAngles();
    void updateDataRange();

private:
    double pAngleOffset;
};

#endif // POLAR_AREA_CHART_H
