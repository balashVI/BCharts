#ifndef QSG_CIRCLE_NODE_H
#define QSG_CIRCLE_NODE_H

#include <QSGGeometryNode>
#include <QColor>

class QSGSmoothColorMaterial;
class QSGGeometry;

class QSGCircleNode : public QSGGeometryNode
{
public:
    QSGCircleNode();

    void update(float radius, int lineWidth, int segmentsCount, QColor color, float scaleFactor, bool antialiasing);

private:
    QSGGeometry *mGeometry;
    QSGSmoothColorMaterial *mMaterial;
};

#endif // QSG_CIRCLE_NODE_H
