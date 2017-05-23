#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <iostream>
#include <QWidget>
#include <QMatrix4x4>
#include <GL/glew.h>
#include <QOpenGLWidget>

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget*);
    ~GLWidget();

private:
    std::string vert, frag;

    GLuint current_shader;

    GLfloat time;

    std::vector<GLfloat> verts;
    GLuint vert_buffer;

   // std::vector< std::vector<QVector3D*> >lines;

    QMatrix4x4 *MVP;
    GLfloat rotY;

    void initializeGL();
    void paintGL();
    void compileShader(std::string, std::string);
};

#endif // GLWIDGET_H
