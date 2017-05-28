#ifndef BASE_GRID_H
#define BASE_GRID_H

#include <QObject>

class TextLayout;
class BaseAxis;
class QSGNode;

class BaseGrid : public QObject
{
    Q_OBJECT
public:
    explicit BaseGrid(BaseAxis *axis, TextLayout *textLayer, QObject *parent = 0);

    virtual QSGNode *updatePaintNode(QSGNode *oldNode, QRectF boundingRect, bool force = false) = 0;

    void setAxis(BaseAxis *axis);

protected:
    BaseAxis *mAxis;
    TextLayout *mTextLayer;

};

#endif // BASE_GRID_H
