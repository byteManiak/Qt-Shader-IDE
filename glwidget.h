#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <iostream>
#include <sstream>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{    
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

signals:
    void outputError(QString);
    void noError();

private:
    void initializeGL();

    int speed;
    float time;
    int m_posAttr;
    int m_colAttr;
    int m_matrixUniform;

    QOpenGLShaderProgram *prog;
    std::vector<float> m_vertices;
    std::vector<float> m_colors;
    std::vector<float> m_resolution;

    QOpenGLShader *v, *f;
    QString v_str, f_str;
    QPoint mousePos;

    std::string prev_error;

public slots:
    void paintGL();
    void resizeGL();
    void speedGL(int);
    void reset();
    void stop();
    void toggle();
    void compile(QString, QString);
    void mouseMoveEvent(QMouseEvent*);
};

#endif // GLWIDGET_H
