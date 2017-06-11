#ifndef QSG_RECTANGLE_NODE_H
#define QSG_RECTANGLE_NODE_H

#include <QSGGeometryNode>

class QSGSmoothColorMaterial;
class QSGGeometry;

class QSGRectangleNode : public QSGGeometryNode
{
public:
    explicit QSGRectangleNode();

    void update(QPointF a, QPointF b, QPointF c, QPointF d, QColor color, bool antialiasing);

private:
    QSGGeometry *mGeometry;
    QSGSmoothColorMaterial *mMaterial;
};

#endif // QSG_RECTANGLE_NODE_H
