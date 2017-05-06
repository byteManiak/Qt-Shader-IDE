#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

static const char* string = "uniform float time;\n"
                       "const float PI = 3.1415926535897932384626433832795;\n"

        "mat2 rotate2d(float angle){\n"
            "return mat2(cos(angle+time),0.,\n"
            "            sin(angle+time),0.);\n"
        "}\n"

        "float stripes(vec2 st){\n"
        "    st = rotate2d( PI*-0.202 ) * st*5.;\n"
        "    return step(.5,1.0-smoothstep(.3,1.,abs(sin(st.x*PI))));\n"
        "}\n"

        "void main(){\n"
        "    vec2 resolution = vec2(300.0,100.0);\n"
        "   vec2 st = gl_FragCoord.xy/resolution.xy * sin(time/2.)*sin(time/2.);\n"
        "    st.x *= resolution.x/resolution.y;\n"

        "    vec3 color = vec3(stripes(st));\n"
        "    gl_FragColor = vec4(color, 1.0);\n"
        "}\n";

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

    float time;
    int m_posAttr;
    int m_colAttr;
    int m_matrixUniform;

public slots:
    void paintGL();
    void resizeGL(int w, int h);
};

#endif // GLWIDGET_H
