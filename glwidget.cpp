#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent), scale(1), speed(1)
{
    v_str += "uniform mat4 matrix;\n"
    "attribute vec4 posAttr;\n"
    "attribute vec4 colAttr;\n"
    "varying vec4 col;\n";

    f_str += "uniform float time;\n"
    "uniform vec2 resolution;\n";
}

void GLWidget::initializeGL()
{
    m_resolution.resize(2);
    m_resolution[0] = this->width();
    m_resolution[1] = this->height();

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

    glClearColor(0, 0, 0, 1);
    v = new QOpenGLShader(QOpenGLShader::Vertex);
    f = new QOpenGLShader(QOpenGLShader::Fragment);
    if(!prog.link()) return;
    m_posAttr = prog.attributeLocation("posAttr");
    m_colAttr = prog.attributeLocation("colAttr");
    m_matrixUniform = prog.uniformLocation("matrix");
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if(prog.shaders().empty()) return;
    if(!prog.bind()) return;

    QMatrix4x4 matrix;

    time+=.02f * speed;
        prog.setAttributeArray( m_posAttr, m_vertices.data(), 3);
        prog.enableAttributeArray( m_posAttr );
        glDrawArrays( GL_QUADS, 0, 4);
        prog.disableAttributeArray( m_posAttr );

        prog.setAttributeArray( m_colAttr, m_colors.data(), 3);
        prog.enableAttributeArray( m_colAttr );
        glDrawArrays( GL_QUADS, 0, 4);
        prog.disableAttributeArray( m_colAttr );

        prog.setUniformValue("time", time);

        prog.setUniformValueArray("resolution", m_resolution.data(), 1, 2);

        prog.setUniformValue(m_matrixUniform, matrix);

    prog.release();

}

void GLWidget::reset() { time = 0; }

void GLWidget::compile(QString v_src, QString f_src)
{
    QString v_strsrc(v_str);
    v_strsrc += v_src;
    prog.removeShader(v);
    v->compileSourceCode(v_strsrc);
    prog.addShader(v);

    QString f_strsrc(f_str);
    f_strsrc += f_src;
    prog.removeShader(f);
    f->compileSourceCode(f_strsrc);
    prog.addShader(f);
}

void GLWidget::resizeGL()
{
    m_resolution[0] = this->width();
    m_resolution[1] = this->height();
}

void GLWidget::stop() { prog.removeAllShaders(); }

void GLWidget::toggle()
{
    if(isHidden()) show();
    else close();
}

void GLWidget::speedGL(int s) { speed = s; }
