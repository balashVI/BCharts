#include "pieslice.h"

#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <cmath>

#include <QDebug>

PieSlice::PieSlice(QQuickItem *parent) :
    BaseSeries(parent),
    pValue{0},
    mStartAngle{0},
    mEndAngle{3.14/2}
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
        qDebug() << "start" << angle;
        mStartAngle = angle;
        update();
    }
}

void PieSlice::setEndAngle(double angle)
{
    if (angle != mEndAngle) {
        qDebug() << "end" << angle;
        mEndAngle = angle;
        update();
    }
}


QSGNode *PieSlice::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGTransformNode *tNode = 0;
    QSGGeometryNode *node = 0;
    QSGGeometry *geometry = 0;

    if (!oldNode) {
        tNode = new QSGTransformNode;
        tNode->setFlag(QSGNode::OwnsGeometry);
        QMatrix4x4 m;
        auto b = boundingRect();

        m.translate(b.width()/2,b.height()/2,1);
        tNode->setMatrix(m);

        node = new QSGGeometryNode;
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 40);
        geometry->setLineWidth(1);
        geometry->setDrawingMode(QSGGeometry::DrawTriangleFan);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);

        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
        material->setColor(pColor);
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);

        //
        QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();

        double r = 1;
        vertices[0].set(0, 0);

        double step = (mEndAngle - mStartAngle) / 38;
        for (int i=0;i<39;i++)
        {
            double angle = mStartAngle + step*i;
            double x = r*cos(angle);
            double y = r*sin(angle);
            vertices[i+1].set(x, y);
        }

//        node->markDirty(QSGNode::DirtyGeometry);

        //
        tNode->appendChildNode(node);
    } else {
        tNode = static_cast<QSGTransformNode *>(oldNode);
    }


    QMatrix4x4 m;
    auto b = boundingRect();

    m.translate(b.width()/2,b.height()/2,1);
    double scale = qMin(b.width(), b.height()) / 2;
    m.scale(scale, scale, 1);
    tNode->setMatrix(m);

    return node;
}
