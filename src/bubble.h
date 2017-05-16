#ifndef BUBBLE_H
#define BUBBLE_H

#include "chartpoint.h"

/*! \addtogroup <additionalClasses> [Допоміжні класи]
    @{
*/

///
/// \brief Клас Bubble
///
/// Клас інкапсуює бульбашку. Вона зображується кругом,
/// і характеризується координатами та власне значенням, від якого залежить її радіус.
///
/// Використовується у класі BubbleSeries
///
/// \see BubbleSeries
///
class Bubble : public ChartPoint
{
    Q_OBJECT
public:
    /// Конструктор, який ініціалізує властивості стандартними значеннями
    explicit Bubble(QQuickItem *parent = 0);
    /// Конструктор, який ініціалізує властивості значеннями, переданими у змінній data
    explicit Bubble(const QVariantMap &data, QQuickItem *parent = 0);
    ~Bubble();

    /// Містить значення бульбашки
    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)
    double value() const;
    void setValue(double value);

protected:
    double pValue;

signals:
    /// Сигналізує про зміну значення бульбашки
    void valueChanged();
};

/*! @} */

#endif // BUBBLE_H

