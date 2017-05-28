#include "qsg_smooth_color_material.h"

#include "qsg_smooth_color_material_shader.h"

QSGSmoothColorMaterial::QSGSmoothColorMaterial()
{
    setFlag(RequiresFullMatrixExceptTranslate, true);
    setFlag(Blending, true);
}

int QSGSmoothColorMaterial::compare(const QSGMaterial *other) const
{
    Q_UNUSED(other)
    return 0;
}

const QSGGeometry::AttributeSet &QSGSmoothColorMaterial::attributeSet()
{
    static QSGGeometry::Attribute data[] = {
        QSGGeometry::Attribute::create(0, 2, GL_FLOAT, true),
        QSGGeometry::Attribute::create(1, 4, GL_UNSIGNED_BYTE, false),
        QSGGeometry::Attribute::create(2, 2, GL_FLOAT, false)};
    static QSGGeometry::AttributeSet attrs = {3, sizeof(SmoothVertex), data};
    return attrs;
}

QSGMaterialType *QSGSmoothColorMaterial::type() const
{
    static QSGMaterialType type;
    return &type;
}

QSGMaterialShader *QSGSmoothColorMaterial::createShader() const
{
    return new QSGSmoothColorMaterialShader();
}
