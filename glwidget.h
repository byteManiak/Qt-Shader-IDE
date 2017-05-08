#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <iostream>

class GLWidget : public QOpenGLWidget
{    
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget() {}

private:
    void initializeGL();

    QOpenGLShaderProgram prog;
    std::vector<float> m_vertices;
    std::vector<float> m_colors;
    std::vector<float> m_resolution;

    float time;
    int m_posAttr;
    int m_colAttr;
    int m_matrixUniform;

    QOpenGLShader *f;

public slots:
    void paintGL();
    void resizeGL();
    void reset();
    void stop();
    void toggle();
    void compile(QString);
};

#endif // GLWIDGET_H
