#include "../tools/stroke.h"

#include <QSGFlatColorMaterial>
#include <QSGNode>
#include <cmath>

#include "../axes/base_axis.h"
#include "polar_area.h"

PolarArea::PolarArea(QObject *parent)
    : BaseSeries(parent),
      pValue{0},
      pStroke{new Stroke(this)},
      mStartAngle{0},
      mEndAngle{3.14 / 2}
{
}

QSGNode *PolarArea::updatePaintNode(QSGNode *oldNode, QRectF boundingRect)
{
    auto center = boundingRect.center();
    float scaleFactor = std::min(boundingRect.height(), boundingRect.width()) * 0.5f;

    QSGGeometryNode *node = 0;
    QSGGeometry *geometry = 0;
    QSGGeometryNode *sNode = 0;
    QSGGeometry *sGeometry = 0;

    // init base node
    if (!oldNode)
    {
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
            sNode = static_cast<QSGGeometryNode *>(node->childAtIndex(0));
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
    auto *material = static_cast<QSGFlatColorMaterial *>(node->material());
    material->setColor(pColor);
    node->markDirty(QSGNode::DirtyMaterial);

    // update stroke material
    if (stroke()->enable())
    {
        auto *material = static_cast<QSGFlatColorMaterial *>(sNode->material());
        material->setColor(stroke()->color());
        node->markDirty(QSGNode::DirtyMaterial);
    }

    // update points
    int vCount = vertexCount(boundingRect);
    geometry->allocate(vCount);
    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();

    vertices[0].set(center.x(), center.y());

    double step = (mEndAngle - mStartAngle) / (vCount - 2);
    for (int i = 0; i < vCount - 1; ++i)
    {
        double angle = mStartAngle + step * i;
        Q_ASSERT(mAxis);
        double r = std::max(0.0, mAxis->map(value()) * scaleFactor);
        double x = center.x() + r * cos(angle);
        double y = center.y() + r * sin(angle);
        vertices[i + 1].set(x, y);
    }

    node->markDirty(QSGNode::DirtyGeometry);

    // update stroke node
    if (stroke()->enable())
    {
        sGeometry->setLineWidth(stroke()->width());
        sGeometry->allocate(vCount);
        auto sVertices = sGeometry->vertexDataAsPoint2D();
        for (int i = 0; i != vCount; ++i)
        {
            sVertices[i] = vertices[i];
        }
        sNode->markDirty(QSGNode::DirtyGeometry);
    }

    return node;
}

double PolarArea::value() const
{
    return pValue;
}

void PolarArea::setValue(double value)
{
    if (value != pValue)
    {
        pValue = value;
        emit valueChanged();
    }
}

void PolarArea::setStartAngle(double angle)
{
    if (angle != mStartAngle)
    {
        mStartAngle = angle;
        emit needsUpdate();
    }
}

void PolarArea::setEndAngle(double angle)
{
    if (angle != mEndAngle)
    {
        mEndAngle = angle;
        emit needsUpdate();
    }
}

Stroke *PolarArea::stroke() const
{
    return pStroke;
}

void PolarArea::setAxis(BaseAxis *axis)
{
    if (axis != mAxis)
    {
        mAxis = axis;
    }
}

int PolarArea::vertexCount(QRectF r)
{
    double radius = qMin(r.width(), r.height()) / 2;

    double l = 2 * M_PI * radius / ((mEndAngle - mStartAngle) / 2 * M_PI);
    int segmentsCount = ceil(l / 5.0); // 1 segment each 5 pixels

    return segmentsCount + 2;
}
