#ifndef BASE_AXIS_H
#define BASE_AXIS_H

#include <QObject>

class BaseAxis : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(double max READ max WRITE setMax NOTIFY maxChanged)
public:
    explicit BaseAxis(QObject *parent = 0);

    virtual double map(double value) = 0;

    double min() const;
    void setMin(double m);

    double max() const;
    void setMax(double m);

protected:
    double mMin;
    double mMax;

signals:
    void minChanged(double min);
    void maxChanged(double max);

public slots:
};

#endif // BASE_AXIS_H
