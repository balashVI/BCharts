#ifndef ABSTRACTSERIES_H
#define ABSTRACTSERIES_H

#include <QPainter>
#include <QQuickItem>
#include "chartpen.h"

///
/// \brief Базовий клас усіх серій графіків
///
/// Містить основні властивості та функціонал властиві усім серіям графіків
///
class AbstractSeries : public QQuickItem
{
    Q_OBJECT
public:
    ///Конструктор класу
    explicit AbstractSeries(QQuickItem *parent = 0);

    ///Назва серії
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

    ///Основний колір серії
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

    void setColor(const QColor &value);
    QColor color() const;
    QString name() const;
    void setName(const QString & value);

protected:
    QString pName;
    QColor pColor;

signals:
    ///Сигналізує про зміну назви серії
    void nameChanged();
    ///Сигналізую про зміну основного кольору серії
    void colorChanged();

public slots:

};

#endif // ABSTRACTSERIES_H
