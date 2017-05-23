#include "polar_grid.h"

#include <QSGFlatColorMaterial>
#include <QSGNode>

#include "../tools/label_configs.h"
#include "../axes/base_axis.h"
#include "../tools/calc.h"

PolarGrid::PolarGrid(QObject *parent) : BaseGrid(parent)
{
}

QSGNode *PolarGrid::updatePaintNode(QSGNode *oldNode, QRectF boundingRect, bool force)
{
    QSGNode *node = oldNode ? oldNode : new QSGNode;

    if (node->childCount() >= 1)
    {
        updateGridLines(node->childAtIndex(0), boundingRect, force);
    }
    else
    {
        node->appendChildNode(updateGridLines(nullptr, boundingRect, force));
    }

    return node;
}

QSGNode *PolarGrid::updateGridLines(QSGNode *oldNode, QRectF boundingRect, bool force)
{
    double scaleFactor = std::min(boundingRect.height(), boundingRect.width()) * 0.5;

    QSGNode *node = oldNode ? oldNode : new QSGNode;

    QPointF center{boundingRect.center()};

    int linesCount = mAxis->gridLinesCount();

    // delete redundant line nodes
    int childsCount = node->childCount();
    while (childsCount > linesCount)
    {
        auto child = node->childAtIndex(0);
        node->removeChildNode(child);
        delete child;
        childsCount--;
    }

    for (int i = 0; i != linesCount; ++i)
    {
        double radius = mAxis->gridLinePosition(i);
        int vertexCount = Calc::vertexContInCircleSegment(scaleFactor * radius, 0, M_PI * 2);

        QSGGeometryNode *circleNode = 0;
        QSGGeometry *geometry = 0;

        // init base node
        if (i >= childsCount)
        {
            circleNode = new QSGGeometryNode;
            geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), vertexCount);
            geometry->setLineWidth(1);
            geometry->setDrawingMode(QSGGeometry::DrawLineLoop);
            circleNode->setGeometry(geometry);
            circleNode->setFlag(QSGNode::OwnsGeometry);

            QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
            circleNode->setMaterial(material);
            circleNode->setFlag(QSGNode::OwnsMaterial);
            node->appendChildNode(circleNode);
        }
        else
        {
            circleNode = static_cast<QSGGeometryNode *>(node->childAtIndex(i));
            geometry = circleNode->geometry();
        }

        // update material
        auto *material = static_cast<QSGFlatColorMaterial *>(circleNode->material());
        material->setColor(mAxis->gridColor());
        circleNode->markDirty(QSGNode::DirtyMaterial);

        // check if the number of segments needs to be updated
        //    double scale = qMin(boundingRect.width(), boundingRect.height()) / 2;
        //    if (scale < 0.75 * mScaleAtLastGUpdate || scale > 1.5 * mScaleAtLastGUpdate)
        //    {

        //        mScaleAtLastGUpdate = scale;
        //        mNeedGeometryUpdate = true;
        //    }

        // update points
        //        if (mNeedGeometryUpdate)
        //        {
        //            mNeedGeometryUpdate = false;

        geometry->allocate(vertexCount);
        QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();

        double step = 2 * M_PI / (vertexCount - 1);
        for (int i = 0; i < vertexCount; ++i)
        {
            double angle = step * i;
            double x = radius * cos(angle);
            double y = radius * sin(angle);
            vertices[i].set(x, y);
        }

        circleNode->markDirty(QSGNode::DirtyGeometry);
        //        }
    }

    return node;
}
