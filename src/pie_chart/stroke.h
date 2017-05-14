#ifndef STROKE_H
#define STROKE_H

#include <QObject>
#include <QColor>

class Stroke : public QObject
{
    Q_OBJECT
    
    Q_PROPERTY(bool enable READ enable WRITE setEnable NOTIFY enableChanged)
    Q_PROPERTY(uint width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:
    explicit Stroke(QObject *parent = 0);

    bool enable() const;
    void setEnable(bool e);

    uint width() const;
    void setWidth(uint w);

    QColor color() const;
    void setColor(QColor c);

signals:
    void enableChanged();
    void widthChanged();
    void colorChanged();

protected:
    bool pEnable;
    uint pWidth;
    QColor pColor;
};

#endif // STROKE_H
