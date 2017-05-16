#ifndef BARCHART_H
#define BARCHART_H

#include "abstractchart.h"
#include "barseries.h"
#include "categoryaxis.h"
#include "standartaxis.h"

///
/// \brief Стовпчикова діаграма
///
/// Малює стовпчикову діаграму. Приклад використання:
/// \code
/// ...
/// BarChart{
///     anchors.fill: parent
///     series: [
///         BarSeries{
///         },
///         BarSeries{
///         }
///     ]
/// }
/// ...
/// \endcode
///
class BarChart : public AbstractChart
{
    Q_OBJECT
public:
    ///Конструктор класу
    explicit BarChart(QQuickPaintedItem *parent = 0);

    /// Зберігає список серій графіка
    ///
    /// Приклад ініціалізації:
    /// \code
    /// ...
    /// series: [
    ///     BarSeries{...},
    ///     BarSeries{...},
    ///     BarSeries{...}
    /// ]
    /// ...
    /// \endcode
    /// Отримати кількість елементів можна наступним чином:
    /// \code
    /// series.length
    /// \endcode
    /// Отримати доступ до i-тої серії в списку можна наступним чином:
    /// \code
    /// series[i]
    /// \endcode
    ///
    /// \see BarSeries
    Q_PROPERTY(QQmlListProperty<BarSeries> series READ series NOTIFY seriesChanged())
    QQmlListProperty<BarSeries> series();

    ///Мітистить вісь категорій х
    Q_PROPERTY(CategoryAxis* xAxis READ xAxis NOTIFY xAxisChanged)
    CategoryAxis* xAxis();

    ///Містить вісь у
    Q_PROPERTY(StandartAxis* yAxis READ yAxis NOTIFY yAxisChanged)
    StandartAxis* yAxis();

    Q_INVOKABLE virtual QVariantList generateLegend();

protected:
    static void appendSeries(QQmlListProperty<BarSeries> *seriesList, BarSeries *series);
    static int seriesListLength(QQmlListProperty<BarSeries> *seriesList);
    static BarSeries *seriesAt(QQmlListProperty<BarSeries> *seriesList, int index);
    QList<BarSeries *> seriesList;
    CategoryAxis pXAxis;
    StandartAxis pYAxis;
    void virtual paint(QPainter *painter) override;
    void drawRotatedText(QPainter *painter, float degrees, int x, int y, const QString &text); //Малює текст з нахилом
    double upperValue, loverValue;

signals:
    /// Сигналізує про зміну серій
    /// \see BarSeries
    void seriesChanged();
    void xAxisChanged();
    void yAxisChanged();
protected slots:
    void calculateDataRange();
};

#endif // BARCHART_H
