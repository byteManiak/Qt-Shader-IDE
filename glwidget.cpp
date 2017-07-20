#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent = 0) : QOpenGLWidget(parent), time(0.0f), rotY(1.0f)
{
    vert = "#version 330 core\n"
        "layout(location = 0) in vec3 vertexPosition_modelspace;\n"
        "uniform mat4 MVP;\n"
        "out vec3 position;\n";

    frag = "#version 330 core\n"
        "in vec3 position;\n"
        "out vec3 color;\n"
        "uniform float time;\n"
        "uniform vec2 resolution;\n";

    MVP = new QMatrix4x4();
    MVP->rotate(180.0f, QVector3D(0.0f, 1.0f, 0.0f));
    MVP->scale(1.0f);
}

void GLWidget::initializeGL()
{
    makeCurrent();
    glewExperimental = GL_TRUE;
    glewInit();

    verts.push_back(-1.0f);
    verts.push_back(-1.0f);
    verts.push_back(0.0f);
    verts.push_back(1.0f);
    verts.push_back(-1.0f);
    verts.push_back(0.0f);
    verts.push_back(1.0f);
    verts.push_back(1.0f);
    verts.push_back(0.0f);
    verts.push_back(-1.0f);
    verts.push_back(1.0f);
    verts.push_back(0.0f);
    verts.push_back(-1.0f);
    verts.push_back(-1.0f);
    verts.push_back(0.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_CLAMP);
    glDepthRange(0.001f, 200.0f);

    GLuint vert_array_id;
    glGenVertexArrays(1, &vert_array_id);
    glBindVertexArray(vert_array_id);

    glGenBuffers(1, &vert_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vert_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*verts.size(), verts.data(), GL_STATIC_DRAW);
}

void GLWidget::paintGL()
{
    glViewport(0, 0, width(), height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(current_shader);

    time += 0.01f;
    MVP->rotate(rotY, QVector3D(0.0f, 1.0f, 0.0f));

    glUniformMatrix4fv(glGetUniformLocation(current_shader, "MVP"), 1, GL_FALSE, MVP->data());
    glUniform1f(glGetUniformLocation(current_shader, "time"), time);
    glUniform2f(glGetUniformLocation(current_shader, "resolution"), this->width(), this->height());

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vert_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, verts.size()/3);

    glDisableVertexAttribArray(0);
}

void GLWidget::compileShader(std::string v, std::string f)
{
    std::string vv = vert + v;
    std::string ff = frag + f;
    GLuint v_shader = glCreateShader(GL_VERTEX_SHADER);
    GLuint f_shader = glCreateShader(GL_FRAGMENT_SHADER);

    const char *v_char = vv.c_str();
    const char *f_char = ff.c_str();

    glShaderSource(v_shader, 1, &v_char, NULL);
    glShaderSource(f_shader, 1, &f_char, NULL);

    glCompileShader(v_shader);

    GLint v_shader_status;

    glGetShaderiv(v_shader, GL_COMPILE_STATUS, &v_shader_status);

    if(v_shader_status == GL_FALSE)
    {
        GLint v_maxLength;
        glGetShaderiv(v_shader, GL_INFO_LOG_LENGTH, &v_maxLength);

        std::vector<GLchar> t_str(v_maxLength);
        glGetShaderInfoLog(v_shader, v_maxLength, &v_maxLength, &t_str[0]);

        std::string v_str = "In vertex shader:\n";
        v_str += t_str.data();
        emit shaderError(QString::fromStdString(v_str));
    }

    glCompileShader(f_shader);

    GLint f_shader_status;

    glGetShaderiv(f_shader, GL_COMPILE_STATUS, &f_shader_status);

    if(f_shader_status == GL_FALSE)
    {
        GLint f_maxLength;
        glGetShaderiv(f_shader, GL_INFO_LOG_LENGTH, &f_maxLength);

        std::vector<GLchar> t_str(f_maxLength);
        glGetShaderInfoLog(f_shader, f_maxLength, &f_maxLength, &t_str[0]);

        std::string f_str = "In fragment shader:\n";
        f_str += t_str.data();
        emit shaderError(QString::fromStdString(f_str));
    }

    GLuint shader_program = glCreateProgram();

    glAttachShader(shader_program, v_shader);
    glAttachShader(shader_program, f_shader);
    glLinkProgram(shader_program);

    glDetachShader(shader_program, v_shader);
    glDetachShader(shader_program, f_shader);

    glDeleteShader(v_shader);
    glDeleteShader(f_shader);

    current_shader = shader_program;
}

void GLWidget::reset()
{
    time = 0;
}

GLWidget::~GLWidget()
{
    delete MVP;
}
