#include "qsg_circle_node.h"

#include <QSGGeometry>

#include "qsg_smooth_color_material.h"

QSGCircleNode::QSGCircleNode()
    : mGeometry(new QSGGeometry(QSGSmoothColorMaterial::attributeSet(), 0, 0, QSGGeometry::UnsignedIntType)),
      mMaterial(new QSGSmoothColorMaterial)
{
    mGeometry->setDrawingMode(GL_TRIANGLE_STRIP);
    setGeometry(mGeometry);
    setFlag(QSGNode::OwnsGeometry);

    setMaterial(mMaterial);
    setFlag(QSGNode::OwnsMaterial);
}

void QSGCircleNode::update(float radius, int lineWidth, int segmentsCount, QColor color, float scaleFactor, bool antialiasing)
{
    int verticesCount = 2 * segmentsCount;
    int indexesCount = 2 * segmentsCount + 2;
    if (antialiasing)
    {
        verticesCount *= 2;
        indexesCount *= 3;
    }
    mGeometry->allocate(verticesCount, indexesCount);

    Color4ub fillColor = colorToColor4ub(color);
    Color4ub transparent = {0, 0, 0, 0};
    float lw = scaleFactor * lineWidth;

    float innerRadius = radius - 0.5f * lw;
    float outerRadius = radius + 0.5f * lw;
    float angleStep = 2.0f * M_PI / segmentsCount;

    int verticesShift = antialiasing ? 4 : 2;

    SmoothVertex *smoothVertices = reinterpret_cast<SmoothVertex *>(mGeometry->vertexData());
    for (int i = 0; i < segmentsCount; ++i)
    {
        float angle = angleStep * i;
        float c = cos(angle);
        float s = sin(angle);

        float outerX = outerRadius * c;
        float outerY = outerRadius * s;
        float innerX = innerRadius * c;
        float innerY = innerRadius * s;

        float dx = antialiasing ? (0.3 * lw * outerX / radius) : 0;
        float dy = antialiasing ? (0.3 * lw * outerY / radius) : 0;

        smoothVertices[verticesShift * i + 0].set(outerX, outerY, fillColor, -dx, -dy); // outer point
        smoothVertices[verticesShift * i + 1].set(innerX, innerY, fillColor, dx, dy);   // inner point

        if (antialiasing)
        {
            smoothVertices[verticesShift * i + 2].set(outerX, outerY, transparent, dx, dy);   // outer transparent point
            smoothVertices[verticesShift * i + 3].set(innerX, innerY, transparent, -dx, -dy); // inner transparent point
        }
    }

    uint *indexes = mGeometry->indexDataAsUInt();
    for (int i = 0; i < segmentsCount; ++i)
    {
        // filled triangles
        indexes[2 * i + 0] = verticesShift * i + 0;
        indexes[2 * i + 1] = verticesShift * i + 1;

        if (antialiasing)
        {
            // outer fade triangles
            indexes[2 * segmentsCount + 2 + 2 * i] = verticesShift * i + 2;
            indexes[2 * segmentsCount + 2 + 2 * i + 1] = verticesShift * i + 0;

            // inner fade triangles
            indexes[4 * segmentsCount + 4 + 2 * i] = verticesShift * i + 1;
            indexes[4 * segmentsCount + 4 + 2 * i + 1] = verticesShift * i + 3;
        }
    }

    // close last filled triangles
    indexes[2 * segmentsCount] = 0;
    indexes[2 * segmentsCount + 1] = 1;

    if (antialiasing)
    {
        // close last outer fade trienagles
        indexes[4 * segmentsCount + 2] = 2;
        indexes[4 * segmentsCount + 3] = 0;

        // close last inner fade trienagles
        indexes[6 * segmentsCount + 4] = 1;
        indexes[6 * segmentsCount + 5] = 3;
    }

    markDirty(QSGNode::DirtyGeometry);
}
