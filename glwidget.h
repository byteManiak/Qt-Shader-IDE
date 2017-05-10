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
    std::vector<float> m_virt_resolution;

    float time;
    int scale, speed;
    int m_posAttr;
    int m_colAttr;
    int m_matrixUniform;

    QOpenGLShader *v, *f;
    QString v_str, f_str;

public slots:
    void paintGL();
    void resizeGL();
    void speedGL(int);
    void reset();
    void stop();
    void toggle();
    void compile(QString, QString);
};

#endif // GLWIDGET_H
