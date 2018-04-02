#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <iostream>
#include <QWidget>
#include <QMatrix4x4>
#include <GL/glew.h>
#include <QOpenGLWidget>
#include <QTime>

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
	explicit GLWidget(QWidget *parent = nullptr);
    ~GLWidget();

private:
    std::string vert, frag;

    GLuint current_shader;

    GLfloat time;

    std::vector<GLfloat> verts;
    GLuint vert_buffer;

	GLuint texture;

    void initializeGL();
    void paintGL();

public slots:
    void compileShader(std::string, std::string);
	void reset();
	void loadTexture(QString);
	void loadModel();

signals:
    void shaderError(QString);
};

#endif // GLWIDGET_H
