#ifndef ABSTRACTAXIS_H
#define ABSTRACTAXIS_H

#include <QQuickItem>
#include <QFontMetrics>
#include "chartpen.h"

/*! \addtogroup <axisClasses> [Класи осей координат]
    @{
*/

///
/// \brief Клас AbstractAxis
///
/// Клас є предком для усіх інших класів осей координат. Він об'єднує в собі
/// усі властивості та методи, властиві всім осям.
///
class AbstractAxis : public QQuickItem
{
    Q_OBJECT
public:
    /// Стандартний конструктор класу
    explicit AbstractAxis(QQuickItem *parent = 0);

    ///Містить користувацькі позначки осі
    Q_PROPERTY(QList<QString> labels READ labels WRITE setLabels NOTIFY labelsChanged)

    ///Містить налаштування лінії осі
    Q_PROPERTY(ChartPen* axisLine READ axisLine WRITE setAxisLine NOTIFY axisLineChanged)

    ///Містить налаштування ліній сітки
    Q_PROPERTY(ChartPen* gridLines READ gridLines WRITE setGridLines NOTIFY gridLinesChanged)

    ///Містить налаштування шрифту міток осі
    Q_PROPERTY(QFont labelsFont READ labelsFont WRITE setLabelsFont NOTIFY labelsFontChanged)

    ///Містить колір міток
    Q_PROPERTY(QColor labelsColor READ labelsColor WRITE setLabelsColor NOTIFY labelsColorChanged)
    void setLabelsColor(const QColor& value);
    const QColor& labelsColor() const;

    ///Вмикає/вимикає відображення підписів осі
    Q_PROPERTY(bool labelsVisible READ labelsVisible WRITE setLabelsVisible NOTIFY labelsVisibleChanged)
    void setLabelsVisible(bool value);
    bool labelsVisible() const;

    void setLabelsFont(QFont &value);
    QFont labelsFont() const;
    void setGridLines(ChartPen* value);
    ChartPen* gridLines() const;
    void setAxisLine(ChartPen* value);
    ChartPen* axisLine() const;
    void setLabels(QList<QString> in);
    const QList<QString> &labels() const;

    double getWidthOfLongestLabel();

protected:
    QList<QString> pLabels;
    ChartPen *pAxisPen, *pGridLines;
    QFont pLabelsFont;
    bool pLabelsVisible;
    QColor pLabelsColor;

    void calculateWidthOfLongestLabel(); //Обчислює довжину найдовшого підпису
    int widthOfLongestLabel;

signals:
    void labelsChanged();
    void axisLineChanged();
    void gridLinesChanged();
    void labelsFontChanged();
    void nameChanged();
    void nameFontChanged();
    void nameVisibleChanged();
    void labelsColorChanged();
    void labelsVisibleChanged();

public slots:

};

/// @}

#endif // ABSTRACTAXIS_H
