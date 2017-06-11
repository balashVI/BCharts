#include "qsg_line_node.h"

#include <QVector2D>

QSGLineNode::QSGLineNode()
    : QSGRectangleNode()
{

}

void QSGLineNode::update(QPointF a, QPointF b, float width, QColor color, bool antialiasing)
{
    QVector2D n = QVector2D(-b.y() + a.y(), b.x() - a.x()).normalized();
    qDebug() << n;
    float halphWidth = 0.5f*width;

    QPointF rA (a.x() + halphWidth * n.x(),
                a.y() + halphWidth * n.y());

    QPointF rB (a.x() - halphWidth * n.x(),
                a.y() - halphWidth * n.y());

    QPointF rC (b.x() + halphWidth * n.x(),
                b.y() + halphWidth * n.y());

    QPointF rD (b.x() - halphWidth * n.x(),
                b.y() - halphWidth * n.y());

    QSGRectangleNode::update(rA, rB, rC, rD, color, antialiasing);
}
