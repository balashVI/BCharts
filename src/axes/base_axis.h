#ifndef BASE_AXIS_H
#define BASE_AXIS_H

#include <QObject>
#include <QColor>

class LabelConfigs;
class GridConfigs;

class BaseAxis : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(double max READ max WRITE setMax NOTIFY maxChanged)
    Q_PROPERTY(LabelConfigs *labels READ labelConfigs)
    Q_PROPERTY(GridConfigs* grid READ gridConfigs)
public:
    explicit BaseAxis(QObject *parent = 0);

    virtual double map(double value) = 0;
    virtual int gridLinesCount() const = 0;
    virtual double gridLinePosition(int i) const = 0;

    double min() const;
    void setMin(double m);

    double max() const;
    void setMax(double m);

    LabelConfigs *labelConfigs() const;
    GridConfigs *gridConfigs() const;

    void setSize(double size);

protected:
    double mMin;
    double mMax;
    LabelConfigs *mLabelConfigs;
    GridConfigs *mGridConfigs;

    double mSize;

signals:
    void minChanged(double min);
    void maxChanged(double max);
    void gridColorChanged(QColor color);

public slots:
};

#endif // BASE_AXIS_H
