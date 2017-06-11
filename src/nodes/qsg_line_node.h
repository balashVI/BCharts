#ifndef QSG_LINE_NODE_H
#define QSG_LINE_NODE_H

#include "./qsg_rectangle_node.h"
#include <QColor>

class QSGSmoothColorMaterial;
class QSGGeometry;

class QSGLineNode : public QSGRectangleNode
{
public:
    QSGLineNode();

    void update(QPointF a, QPointF b, float width, QColor color, bool antialiasing);
};

#endif // QSG_LINE_NODE_H
