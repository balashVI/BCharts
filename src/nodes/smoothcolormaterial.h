#include <QSGMaterial>
#include <QSGMaterialShader>

//----------------------------------------------------------------------

class QSGSmoothColorMaterial : public QSGMaterial
{
public:
    QSGSmoothColorMaterial();
    int compare(const QSGMaterial *other) const;
protected:
    virtual QSGMaterialType *type() const;
    virtual QSGMaterialShader *createShader() const;
};

//----------------------------------------------------------------------

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
    int m_matrixLoc;
    int m_opacityLoc;
    int m_pixelSizeLoc;
};
