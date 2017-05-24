#ifndef QSG_CIRCLE_NODE_H
#define QSG_CIRCLE_NODE_H

#include <QSGFlatColorMaterial>
#include <QSGGeometryNode>
#include <QSGGeometry>

class QSGCircleNode : public QSGGeometryNode
{
public:
    QSGCircleNode(double radius, int segmentsCount, QColor color);

    void setRadius(double r);
    void setSegmentsCount(int count);
    void setColor(QColor color);

private:
    void updateGeometry();

private:
    QSGGeometry mGeometry;
    QSGFlatColorMaterial mMaterial;
    int mSegmentsCount;
    double mRadius;
};

#endif // QSG_CIRCLE_NODE_H
