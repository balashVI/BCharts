#ifndef BASE_GRID_H
#define BASE_GRID_H

#include <QObject>

class BaseAxis;
class QSGNode;

class BaseGrid : public QObject
{
    Q_OBJECT
public:
    explicit BaseGrid(QObject *parent = 0);

    virtual QSGNode *updatePaintNode(QSGNode *oldNode, QRectF boundingRect, bool force = false) = 0;

    void setAxis(BaseAxis *axis);

protected:
    BaseAxis *mAxis;

};

#endif // BASE_GRID_H
