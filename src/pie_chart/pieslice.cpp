#include "pieslice.h"

#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <cmath>

#include <QDebug>

PieSlice::PieSlice(QQuickItem *parent) :
    BaseSeries(parent),
    pValue{0},
    mStartAngle{0},
    mEndAngle{3.14/2},
    mNeedGeometryUpdate{true},
    mScaleAtLastGUpdate{0}
{
    setFlag(ItemHasContents, true);

    setAntialiasing(true);

    pName = "Slice";
}

double PieSlice::value() const
{
    return pValue;
}

void PieSlice::setValue(double value)
{
    if (value != pValue)
    {
        pValue = value;
        emit valueChanged();
    }
}

void PieSlice::setStartAngle(double angle)
{
    if (angle != mStartAngle) {
        mStartAngle = angle;
        mNeedGeometryUpdate = true;
        update();
    }
}

void PieSlice::setEndAngle(double angle)
{
    if (angle != mEndAngle) {
        mEndAngle = angle;
        mNeedGeometryUpdate = true;
        update();
    }
}

int PieSlice::vertexCount(QRectF r)
{
    double radius = qMin(r.width(), r.height()) / 2;

    double l = 2*M_PI*radius /  ((mEndAngle - mStartAngle) / 2*M_PI);
    int segmentsCount = ceil(l/5.0); // 1 segment each 5 pixels

    return segmentsCount + 2;
}


QSGNode *PieSlice::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    auto b = boundingRect();

    QSGTransformNode *transformNode = 0;
    QSGGeometryNode *node = 0;
    QSGGeometry *geometry = 0;

    if (!oldNode) {
        transformNode = new QSGTransformNode;
        transformNode->setFlag(QSGNode::OwnsGeometry);

        node = new QSGGeometryNode;
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), vertexCount(b));
        geometry->setLineWidth(1);
        geometry->setDrawingMode(QSGGeometry::DrawTriangleFan);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);

        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);

        transformNode->appendChildNode(node);
    }
    else
    {
        transformNode = static_cast<QSGTransformNode *>(oldNode);
        node = static_cast<QSGGeometryNode *>(transformNode->childAtIndex(0));
        geometry = node->geometry();
    }

    // transform
    QMatrix4x4 m;
    m.translate(b.width()/2,b.height()/2,1);
    double scale = qMin(b.width(), b.height()) / 2;
    m.scale(scale, scale, 1);
    transformNode->setMatrix(m);
    transformNode->markDirty(QSGNode::DirtyMatrix);

    if (scale < 0.75*mScaleAtLastGUpdate || scale > 1.5*mScaleAtLastGUpdate) {
        // need to update segments count
        mScaleAtLastGUpdate = scale;
        mNeedGeometryUpdate = true;
    }

    // update material
    if (mNeedMaterialUpdate)
    {
        QSGFlatColorMaterial *material = static_cast<QSGFlatColorMaterial*>(node->material());
        material->setColor(pColor);

        transformNode->markDirty(QSGNode::DirtyMaterial);
    }

    // add points
    if (mNeedGeometryUpdate)
    {
        mNeedGeometryUpdate = false;

        int vCount = vertexCount(b);
        geometry->allocate(vCount);
        QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();

        vertices[0].set(0, 0);

        double step = (mEndAngle - mStartAngle) / (vCount - 2);
        for (int i=0; i<vCount-1; i++)
        {
            double angle = mStartAngle + step*i;
            double x = cos(angle);
            double y = sin(angle);
            vertices[i+1].set(x, y);
        }

        node->markDirty(QSGNode::DirtyGeometry);
    }

    return transformNode;
}
