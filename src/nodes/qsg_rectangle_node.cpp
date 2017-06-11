#include "qsg_rectangle_node.h"

#include <QSGGeometry>

#include "qsg_smooth_color_material.h"
#include "../tools/calc.h"

QSGRectangleNode::QSGRectangleNode()
    : mGeometry(new QSGGeometry(QSGSmoothColorMaterial::attributeSet(), 0, 0, QSGGeometry::UnsignedIntType)),
      mMaterial(new QSGSmoothColorMaterial)
{
    mGeometry->setDrawingMode(GL_TRIANGLE_STRIP);
    setGeometry(mGeometry);
    setFlag(QSGNode::OwnsGeometry);

    setMaterial(mMaterial);
    setFlag(QSGNode::OwnsMaterial);
}

void QSGRectangleNode::update(QPointF a, QPointF b, QPointF c, QPointF d, QColor color, bool antialiasing)
{
    if (antialiasing)
    {
        mGeometry->allocate(8, 13);
    }
    else
    {
        mGeometry->allocate(4, 4);
    }

    Color4ub fillColor = colorToColor4ub(color);
    Color4ub transparent = {0, 0, 255, 0};

     SmoothVertex *smoothVertices = reinterpret_cast<SmoothVertex *>(mGeometry->vertexData());
     smoothVertices[0].set(a.x(), a.y(), fillColor, 0, 0);
     smoothVertices[1].set(b.x(), b.y(), fillColor, 0, 0);
     smoothVertices[2].set(d.x(), d.y(), fillColor, 0, 0);
     smoothVertices[3].set(c.x(), c.y(), fillColor, 0, 0);

     if (antialiasing)
     {
        auto v1 = Calc::vector(a, b);
        auto v2 = Calc::vector(a, c);
        auto bisec = Calc::vectorBisector(v1, v2);
        smoothVertices[0].dx = bisec.x();
        smoothVertices[0].dy = bisec.y();
        smoothVertices[4].set(a.x(), a.y(), transparent, -bisec.x(), -bisec.y());

        v1 = Calc::vector(b, d);
        v2 = Calc::vector(b, a);
        bisec = Calc::vectorBisector(v1, v2);
        smoothVertices[1].dx = bisec.x();
        smoothVertices[1].dy = bisec.y();
        smoothVertices[5].set(b.x(), b.y(), transparent, -bisec.x(), -bisec.y());

        v1 = Calc::vector(d, c);
        v2 = Calc::vector(d, b);
        bisec = Calc::vectorBisector(v1, v2);
        smoothVertices[2].dx = bisec.x();
        smoothVertices[2].dy = bisec.y();
        smoothVertices[6].set(d.x(), d.y(), transparent, -bisec.x(), -bisec.y());

        v1 = Calc::vector(c, a);
        v2 = Calc::vector(c, d);
        bisec = Calc::vectorBisector(v1, v2);
        smoothVertices[3].dx = bisec.x();
        smoothVertices[3].dy = bisec.y();
        smoothVertices[7].set(c.x(), c.y(), transparent, -bisec.x(), -bisec.y());
     }

     uint *indexes = mGeometry->indexDataAsUInt();
     indexes[0] = 1;
     indexes[1] = 0;
     indexes[2] = 2;
     indexes[3] = 3;
     if (antialiasing)
     {
         indexes[4] = 7;
         indexes[5] = 3;
         indexes[6] = 4;
         indexes[7] = 0;
         indexes[8] = 5;
         indexes[9] = 1;
         indexes[10] = 6;
         indexes[11] = 2;
         indexes[12] = 7;
     }
}
