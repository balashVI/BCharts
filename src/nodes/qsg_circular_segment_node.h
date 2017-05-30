#ifndef QSG_CIRCULAR_SEGMENT_NODE_H
#define QSG_CIRCULAR_SEGMENT_NODE_H

#include <QSGGeometryNode>
#include <QColor>

class QSGFlatColorMaterial;
class QSGGeometry;

class QSGCircularSegmentNode : public QSGGeometryNode
{
public:
    QSGCircularSegmentNode();

    void update(QPointF center, float radius, float startAndgle, float endAngle, int lineWidth, QColor color, bool antialiasing);

private:
    QSGGeometry *mGeometry;
    QSGFlatColorMaterial *mMaterial;
};

#endif // QSG_CIRCULAR_SEGMENT_NODE_H
