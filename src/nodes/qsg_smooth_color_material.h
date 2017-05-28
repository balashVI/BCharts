#ifndef QSG_SMOOTH_COLOR_MATERIAL_H
#define QSG_SMOOTH_COLOR_MATERIAL_H

#include <QSGMaterial>
#include <QSGGeometry>
#include <QColor>

struct Color4ub
{
    unsigned char r, g, b, a;
};

inline Color4ub colorToColor4ub(const QColor &c)
{
    Color4ub color = {uchar(c.redF() * c.alphaF() * 255),
                      uchar(c.greenF() * c.alphaF() * 255),
                      uchar(c.blueF() * c.alphaF() * 255),
                      uchar(c.alphaF() * 255)};
    return color;
}

struct SmoothVertex
{
    float x, y;
    Color4ub color;
    float dx, dy;
    void set(float nx, float ny, Color4ub ncolor, float ndx, float ndy)
    {
        x = nx;
        y = ny;
        color = ncolor;
        dx = ndx;
        dy = ndy;
    }
};

class QSGSmoothColorMaterial : public QSGMaterial
{
  public:
    QSGSmoothColorMaterial();
    int compare(const QSGMaterial *other) const;

    static const QSGGeometry::AttributeSet &attributeSet();

  protected:
    virtual QSGMaterialType *type() const;
    virtual QSGMaterialShader *createShader() const;
};

#endif // QSG_SMOOTH_COLOR_MATERIAL_H
