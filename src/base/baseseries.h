#ifndef BASESERIES_H
#define BASESERIES_H

#include <QObject>
#include <QSGNode>
#include <QColor>

class BaseSeries : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    explicit BaseSeries(QObject *parent = 0);

    virtual QSGNode *updatePaintNode(QSGNode *oldNode, QRectF boundingRect, bool force = false) = 0;

    QColor color() const;
    void setColor(const QColor &value);

    QString name() const;
    void setName(const QString & value);

protected:
    QString pName;
    QColor pColor;

    bool mNeedMaterialUpdate;

signals:
    void nameChanged();
    void colorChanged();
    void needsUpdate();

public slots:

};

#endif // BASESERIES_H
