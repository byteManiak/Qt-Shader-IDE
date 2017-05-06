#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void GLWidget::initializeGL()
{
    m_vertices.resize( 12 );

    m_vertices[0] = -2.0f;
    m_vertices[1] = -2.0f;
    m_vertices[2] = 0.0f;

    m_vertices[3] = -2.0f;
    m_vertices[4] = 2.0f;
    m_vertices[5] = 0.0f;

    m_vertices[6] = 2.0f;
    m_vertices[7] = 2.0f;
    m_vertices[8] = 0.0f;

    m_vertices[9] = 2.0f;
    m_vertices[10] = -2.0f;
    m_vertices[11] = 0.0f;

    m_colors.resize( 12 );

    m_colors[0] = 0.0f;
    m_colors[1] = 0.0f;
    m_colors[2] = 0.0f;

    m_colors[3] = 0.0f;
    m_colors[4] = 0.0f;
    m_colors[5] = 0.0f;

    m_colors[6] = 0.0f;
    m_colors[7] = 0.0f;
    m_colors[8] = 0.0f;

    m_colors[9] = 0.0f;
    m_colors[10] = 0.0f;
    m_colors[11] = 0.0f;

    glClearColor(0,0,0,0);
    QOpenGLShader v(QOpenGLShader::Vertex);
    v.compileSourceCode("attribute highp vec4 posAttr;\n"
                        "uniform mediump mat4 matrix;\n"
                        "uniform float time;\n"
                        "attribute lowp vec4 colAttr;\n"
                        "varying lowp vec4 col;\n"
                        "void main() {\n"
                        "   col = colAttr;\n"
                        "   gl_Position = matrix * posAttr;\n"
                        "}\n");
    QOpenGLShader f(QOpenGLShader::Fragment);
    f.compileSourceCode(string);
    prog.addShader(&f);
    prog.addShader(&v);
    if(!prog.link()) return;
    m_posAttr = prog.attributeLocation("posAttr");
    m_colAttr = prog.attributeLocation("colAttr");
    m_matrixUniform = prog.uniformLocation("matrix");
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    prog.bind();

    QMatrix4x4 matrix;
    matrix.ortho( -2.0f, 2.0f, -2.0f, 2.0f, 2.0f, -2.0f );
    matrix.translate( 0.0f, 0.0f, -1.0f );

    time+=.02f;
    prog.setAttributeArray( m_posAttr, m_vertices.data(), 3 );
    prog.setAttributeArray( m_colAttr, m_colors.data(), 3 );
    prog.setUniformValue("time", time);
    prog.enableAttributeArray( m_posAttr );
    prog.enableAttributeArray( m_colAttr );

    glDrawArrays( GL_QUADS, 0, 4 );

    prog.disableAttributeArray( m_posAttr );
    prog.disableAttributeArray( m_colAttr );

    prog.setUniformValue(m_matrixUniform, matrix);

    prog.release();

}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}
