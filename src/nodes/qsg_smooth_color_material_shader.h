#ifndef QSG_SMOOTH_COLOR_MATERIAL_SHADER_H
#define QSG_SMOOTH_COLOR_MATERIAL_SHADER_H

#include <QSGMaterialShader>

class QSGSmoothColorMaterialShader : public QSGMaterialShader
{
public:
    QSGSmoothColorMaterialShader();
    virtual void updateState(const RenderState &state, QSGMaterial *newEffect, QSGMaterial *oldEffect);
    virtual char const *const *attributeNames() const;

    const char *vertexShader() const override;
    const char *fragmentShader() const override;
private:
    void initialize();
    int mMatrixLoc;
    int mOpacityLoc;
    int mPixelSizeLoc;
};

#endif // QSG_SMOOTH_COLOR_MATERIAL_SHADER_H
