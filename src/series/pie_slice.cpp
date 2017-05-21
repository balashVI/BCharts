#include <QSGFlatColorMaterial>
#include <QSGGeometryNode>
#include <QDebug>
#include <cmath>


#include "pie_slice.h"

PieSlice::PieSlice(QObject *parent) :
    BaseSeries(parent),
    pValue{0},
    pStroke{new Stroke(this)},
    mStartAngle{0},
    mEndAngle{3.14/2},
    mNeedGeometryUpdate{true},
    mScaleAtLastGUpdate{0}
{
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
        emit needsUpdate();
    }
}

void PieSlice::setEndAngle(double angle)
{
    if (angle != mEndAngle) {
        mEndAngle = angle;
        mNeedGeometryUpdate = true;
        emit needsUpdate();
    }
}

Stroke *PieSlice::stroke() const
{
    return pStroke;
}

int PieSlice::vertexCount(QRectF r)
{
    double radius = qMin(r.width(), r.height()) / 2;

    double l = 2*M_PI*radius /  ((mEndAngle - mStartAngle) / 2*M_PI);
    int segmentsCount = ceil(l/5.0); // 1 segment each 5 pixels

    return segmentsCount + 2;
}

QSGNode *PieSlice::updatePaintNode(QSGNode *oldNode, QRectF boundingRect, bool force)
{
    if (force)
    {
        mNeedGeometryUpdate = true;
        mNeedMaterialUpdate = true;
    }

    QSGGeometryNode *node = 0;
    QSGGeometry *geometry = 0;
    QSGGeometryNode *sNode = 0;
    QSGGeometry *sGeometry = 0;

    // init base node
    if (!oldNode) {
        node = new QSGGeometryNode;
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), vertexCount(boundingRect));
        geometry->setLineWidth(1);
        geometry->setDrawingMode(QSGGeometry::DrawTriangleFan);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);

        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
    }
    else
    {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
    }

    // init stroke node
    if (stroke()->enable())
    {
        if (node->childCount())
        {
           sNode = static_cast<QSGGeometryNode*>(node->childAtIndex(0));
           sGeometry = sNode->geometry();
        }
        else
        {
            sNode = new QSGGeometryNode;
            sGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), vertexCount(boundingRect));
            sGeometry->setLineWidth(stroke()->width());
            sGeometry->setDrawingMode(QSGGeometry::DrawLineLoop);
            sNode->setGeometry(sGeometry);
            sNode->setFlag(QSGNode::OwnsGeometry);

            auto *sMaterial = new QSGFlatColorMaterial;
            sNode->setMaterial(sMaterial);
            sNode->setFlag(QSGNode::OwnsMaterial);

            node->appendChildNode(sNode);
        }
    }
    else
    {
        if (node->childCount())
        {
            // delete stroke node if not needed more
            auto sNode = node->childAtIndex(0);
            node->removeChildNode(sNode);
            delete sNode;
        }
    }

    // update material
    if (mNeedMaterialUpdate)
    {
        auto *material = static_cast<QSGFlatColorMaterial*>(node->material());
        material->setColor(pColor);
        node->markDirty(QSGNode::DirtyMaterial);

        // update stroke material
        if (stroke()->enable())
        {
            auto *material = static_cast<QSGFlatColorMaterial*>(sNode->material());
            material->setColor(stroke()->color());
            node->markDirty(QSGNode::DirtyMaterial);
        }
    }

    // check if the neumber of segments needs to be updated
    double scale = qMin(boundingRect.width(), boundingRect.height()) / 2;
    if (scale < 0.75*mScaleAtLastGUpdate || scale > 1.5*mScaleAtLastGUpdate) {

        mScaleAtLastGUpdate = scale;
        mNeedGeometryUpdate = true;
    }

    // update points
    if (mNeedGeometryUpdate)
    {
        mNeedGeometryUpdate = false;

        int vCount = vertexCount(boundingRect);
        geometry->allocate(vCount);
        QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();

        vertices[0].set(0, 0);

        double step = (mEndAngle - mStartAngle) / (vCount - 2);
        for (int i=0; i<vCount-1; ++i)
        {
            double angle = mStartAngle + step*i;
            double x = cos(angle);
            double y = sin(angle);
            vertices[i+1].set(x, y);
        }

        node->markDirty(QSGNode::DirtyGeometry);

        // update stroke node
        if (stroke()->enable())
        {
            sGeometry->setLineWidth(stroke()->width());
            sGeometry->allocate(vCount);
            auto sVertices = sGeometry->vertexDataAsPoint2D();
            for (int i=0; i!=vCount; ++i)
            {
               sVertices[i] = vertices[i];
            }
            sNode->markDirty(QSGNode::DirtyGeometry);
        }
    }

    return node;
}
