#include "smoothcolormaterial.h"

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

QSGMaterialType *QSGSmoothColorMaterial::type() const
{
    static QSGMaterialType type;
    return &type;
}

QSGMaterialShader *QSGSmoothColorMaterial::createShader() const
{
    return new QSGSmoothColorMaterialShader();
}

//----------------------------------------------------------------------

QSGSmoothColorMaterialShader::QSGSmoothColorMaterialShader()
    : QSGMaterialShader()
{
//    setShaderSourceFile(QOpenGLShader::Vertex, QStringLiteral(":/shaders/smoothcolor.vert"));
//    setShaderSourceFile(QOpenGLShader::Fragment, QStringLiteral(":/shaders/smoothcolor.frag"));
}

void QSGSmoothColorMaterialShader::updateState(const QSGMaterialShader::RenderState &state, QSGMaterial *newEffect, QSGMaterial *oldEffect)
{
    Q_UNUSED(newEffect)

    if (state.isOpacityDirty())
        program()->setUniformValue(m_opacityLoc, state.opacity());

    if (state.isMatrixDirty())
        program()->setUniformValue(m_matrixLoc, state.combinedMatrix());

    if (oldEffect == 0) {
        // The viewport is constant, so set the pixel size uniform only once.
        QRect r = state.viewportRect();
        program()->setUniformValue(m_pixelSizeLoc, 2.0f / r.width(), 2.0f / r.height());
    }
}

const char * const *QSGSmoothColorMaterialShader::attributeNames() const
{
    static char const *const attributes[] = {
        "vertex",
        "vertexColor",
        "vertexOffset",
        0
    };
    return attributes;
}

const char *QSGSmoothColorMaterialShader::vertexShader() const
{
    return "uniform highp vec2 pixelSize;"
            "uniform highp mat4 matrix;"
            "uniform lowp float opacity;"

            "attribute highp vec4 vertex;"
            "attribute lowp vec4 vertexColor;"
            "attribute highp vec2 vertexOffset;"

            "varying lowp vec4 color;"

            "void main()"
            "{"
            "    highp vec4 pos = matrix * vertex;"
            "    gl_Position = pos;"

            "    if (vertexOffset.x != 0.) {"
            "       highp vec4 delta = matrix[0] * vertexOffset.x;"
            "       highp vec2 dir = delta.xy * pos.w - pos.xy * delta.w;"
            "       highp vec2 ndir = .5 * pixelSize * normalize(dir / pixelSize);"
            "       dir -= ndir * delta.w * pos.w;"
            "       highp float numerator = dot(dir, ndir * pos.w * pos.w);"
            "       highp float scale = 0.0;"
            "       if (numerator < 0.0)"
            "           scale = 1.0;"
            "       else"
            "           scale = min(1.0, numerator / dot(dir, dir));"
            "       gl_Position += scale * delta;"
            "   }"

            "   if (vertexOffset.y != 0.) {"
            "       highp vec4 delta = matrix[1] * vertexOffset.y;"
            "       highp vec2 dir = delta.xy * pos.w - pos.xy * delta.w;"
            "       highp vec2 ndir = .5 * pixelSize * normalize(dir / pixelSize);"
            "       dir -= ndir * delta.w * pos.w;"
            "       highp float numerator = dot(dir, ndir * pos.w * pos.w);"
            "       highp float scale = 0.0;"
            "       if (numerator < 0.0)"
            "           scale = 1.0;"
            "       else"
            "           scale = min(1.0, numerator / dot(dir, dir));"
            "       gl_Position += scale * delta;"
            "   }"

            "   color = vertexColor * opacity;"
            "}";
}

const char *QSGSmoothColorMaterialShader::fragmentShader() const
{
    return "varying lowp vec4 color;"
           "void main()"
           "{"
           "    gl_FragColor = color;"
           "}";
}

void QSGSmoothColorMaterialShader::initialize()
{
    m_matrixLoc = program()->uniformLocation("matrix");
    m_opacityLoc = program()->uniformLocation("opacity");
    m_pixelSizeLoc = program()->uniformLocation("pixelSize");
}
