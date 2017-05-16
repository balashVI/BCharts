#ifndef CHARTPOINT_H
#define CHARTPOINT_H

#include <QQuickItem>

/*! \addtogroup <additionalClasses> [Допоміжні класи]
    @{
*/

///
/// \brief Клас ChartPoint
///
/// Цей клас інкапсулює точку в декартовій площині.
///
/// Використовується у класі XYSeries
///
/// \see XYSeries
///
class ChartPoint : public QQuickItem
{
    Q_OBJECT
public:
    /// Конструктор, який ініціалізує властивості стандартними значеннями
    explicit ChartPoint(QQuickItem *parent = 0);
    /// Конструктор, який ініціалізує властивості значеннями, переданими у змінній data
    explicit ChartPoint(const QVariantMap &data, QQuickItem *parent = 0);
    ~ChartPoint();

    /// Містить координату X
    Q_PROPERTY(double x READ x WRITE setX NOTIFY xChanged)
    double x() const;
    void setX(double value);

    /// Містить координату Y
    Q_PROPERTY(double y READ y WRITE setY NOTIFY yChanged)
    double y() const;
    void setY(double value);

protected:
    double pX, pY;

signals:
    /// Сигналізує про зміну координати X
    void xChanged();
    /// Сигналізує про зміну координати Y
    void yChanged();

public slots:
};

/*! @} */

#endif // CHARTPOINT_H
