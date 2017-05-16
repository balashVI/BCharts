#ifndef CHARTPEN_H
#define CHARTPEN_H

#include <QPen>
#include <QQuickItem>

/*! \addtogroup <additionalClasses> [Допоміжні класи]
    @{
*/

/**
 * @brief Клас ChartPen
 *
 * Цей клас є реалізацією шаблона проектування під назвою "Адаптер". А саме, він призначений
 * для доступу до властивостей класу QPen з коду QML
 */
class ChartPen : public QQuickItem
{
    Q_OBJECT
public:
    /// Стандартний конструктор
    explicit ChartPen(QQuickItem *parent = 0);

    ///Задає стиль закінчень лінії намальованої пером
    Q_PROPERTY(Qt::PenCapStyle capStyle READ capStyle WRITE setCapStyle NOTIFY capStyleChanged)
    Qt::PenCapStyle capStyle() const;
    void setCapStyle(Qt::PenCapStyle value);

    ///Задає колір пера
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    QColor color() const;
    void setColor(const QColor &newColor);

    /// Задає зміщення штрихів пера
    Q_PROPERTY(double dashOffset READ dashOffset WRITE setDashOffset NOTIFY dashOffsetChanged)
    double dashOffset() const;
    void setDashOffset(double offset);

    /// \brief Задає шаблон штрихів пера
    ///
    /// Приклад:
    /// \code
    /// xAxis.gridLines.dashPattern: [8, 5, 2, 5]
    /// \endcode
    Q_PROPERTY(QList<double> dashPattern READ dashPattern WRITE setDashPattern NOTIFY dashPatternChanged)
    QList<double> dashPattern() const;
    void setDashPattern(const QList<double> &pattern);

    /// Задає стиль переходу між двома лініями
    Q_PROPERTY(Qt::PenJoinStyle joinStyle READ joinStyle WRITE setJoinStyle NOTIFY joinStyleChanged)
    Qt::PenJoinStyle joinStyle() const;
    void setJoinStyle(Qt::PenJoinStyle style);

    /// Задає обмеження видовжень країв об'єднаних ліній
    Q_PROPERTY(double miterLimit READ miterLimit WRITE setMiterLimit NOTIFY miterLimitChanged)
    double miterLimit() const;
    void setMiterLimit(double limit);

    /// Задає стиль пера із списку стандартних стилів
    Q_PROPERTY(Qt::PenStyle style READ style WRITE setStyle NOTIFY styleChanged)
    Qt::PenStyle style() const;
    void setStyle(Qt::PenStyle style);

    /// Задає товщину пера
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    int width() const;
    void setWidth(int newWidth);

    const QPen &getPen() const;

private:
    QPen pen;

signals:
    /// Сигналізує про зміну стилю закінчень лінії намяльованої пером
    void capStyleChanged();

    /// Сигналізує про зміну кольору пера
    void colorChanged();

    /// Сигналізує про зміну зміщення штрихів пера
    void dashOffsetChanged();

    /// Сигналізує про зміну шаблону штрихів пера
    void dashPatternChanged();

    /// Сигналізує про зміну стилю переходу між двома лініями
    void joinStyleChanged();

    /// Сигналізує про зміну обмеження видовжень країв об'єднаних ліній
    void miterLimitChanged();

    /// Сигналізує про зміну стилю пера
    void styleChanged();

    /// Сигналізує про зміну товщини пера
    void widthChanged();
};

/// @}

#endif // CHARTPEN_H
