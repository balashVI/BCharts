#include "polar_grid.h"

#include <QSGFlatColorMaterial>
#include <QSGNode>
#include <cmath>

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

    if (node->childCount() != 0)
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
    float scaleFactor = std::min(boundingRect.height(), boundingRect.width()) * 0.5;
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

    QPointF center = boundingRect.center();
    for (int i = 0; i < linesCount; ++i)
    {
        double radius = mAxis->gridLinePosition(i) * scaleFactor;
        int vertexCount = Calc::vertexContInCircleSegment(radius, 0, M_PI * 2);

        QSGCircleNode *circleNode = 0;

        if (i < childsCount)
        {
            circleNode = static_cast<QSGCircleNode *>(node->childAtIndex(i));
        }
        else
        {
            circleNode = new QSGCircleNode();
            node->appendChildNode(circleNode);
        }

        circleNode->update(center, radius, 2, vertexCount, mAxis->gridColor(), true);
    }
    return node;
}
