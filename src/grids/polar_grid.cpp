#include "polar_grid.h"

#include <QSGFlatColorMaterial>
#include <QSGNode>

#include "../nodes/qsg_circle_node.h"
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
    int linesCount = mAxis->gridLinesCount();

    QSGNode *node = oldNode ? oldNode : new QSGNode;

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

        QSGCircleNode *circleNode = 0;

        // init base node
        if (i >= childsCount)
        {
            circleNode = new QSGCircleNode(radius, vertexCount, mAxis->gridColor());
            node->appendChildNode(circleNode);
        }
        else
        {
            circleNode = static_cast<QSGCircleNode *>(node->childAtIndex(i));
            circleNode->setRadius(radius);
            circleNode->setSegmentsCount(vertexCount);
            circleNode->setColor(mAxis->gridColor());
        }

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
    }

    return node;
}
