#ifndef BASE_AXIS_H
#define BASE_AXIS_H

#include <QObject>
#include <QColor>

class LabelConfigs;

class BaseAxis : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(double max READ max WRITE setMax NOTIFY maxChanged)
    Q_PROPERTY(QColor gridColor READ gridColor WRITE setGridColor NOTIFY gridColorChanged)
    Q_PROPERTY(LabelConfigs *labels READ labelConfigs)
public:
    explicit BaseAxis(QObject *parent = 0);

    virtual double map(double value) = 0;
    virtual int gridLinesCount() const = 0;
    virtual double gridLinePosition(int i) const = 0;

    double min() const;
    void setMin(double m);

    double max() const;
    void setMax(double m);

    QColor gridColor() const;
    void setGridColor(QColor color);

    LabelConfigs *labelConfigs() const;

protected:
    double mMin;
    double mMax;
    QColor mGridColor;
    LabelConfigs *mLabelConfigs;

signals:
    void minChanged(double min);
    void maxChanged(double max);
    void gridColorChanged(QColor color);

public slots:
};

#endif // BASE_AXIS_H
