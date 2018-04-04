#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <QWidget>
#include <QMatrix4x4>
#include <QMessageBox>
#include <GL/glew.h>
#include <QOpenGLWidget>
#include <QTime>
#include "vec.h"

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
	explicit GLWidget(QWidget *parent = nullptr);
    ~GLWidget();

private:
    GLuint current_shader;
    GLfloat time;
	std::vector<vec3> verts;
	std::vector<vec2> uvs;
	std::vector<unsigned> elems;
	GLuint vertexArray;
	GLuint vertexBuffers[3];
	GLuint texture;
	bool hasUVs = false, hasNormals = false;

    void initializeGL();
    void paintGL();
	void normalize();

	// for testing:
	QMatrix4x4 rotation;

public slots:
    void compileShader(std::string, std::string);
	void reset();
	void loadTexture(QString);
	void loadModel(QString);

signals:
    void shaderError(QString);
};

#endif // GLWIDGET_H
