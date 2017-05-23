#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent = 0) : QOpenGLWidget(parent), time(0.0f), rotY(1.0f)
{
    vert = "#version 330 core\n"
        "layout(location = 0) in vec3 vertexPosition_modelspace;\n"
        "uniform mat4 MVP;\n"
        "out vec3 position;\n"
        "void main() {\n"
        "position = vertexPosition_modelspace;\n"
        "gl_Position = MVP * vec4(vertexPosition_modelspace, 1);\n}\n";

    frag = "#version 330 core\n"
        "in vec3 position;\n"
        "out vec3 color;\n"
        "uniform float time;\n"
        "void main() {\n"
        ""
        "color = vec3(sin(mix(.5, 1, position.x)*30-time)*sin(mix(.5, 1, position.y)*30+time), "
        "           sin(mix(.5, 1, position.y)*40+time)*sin(mix(.5, 1, position.x)*40+time),"
        "           sin(mix(.5, 1, position.x)*50+time)*sin(mix(.5, 1, position.y)*50-time))"
        "      * (.9-distance(position.xy, vec2(.5)));}\n";

    MVP = new QMatrix4x4();
 //   MVP->perspective(75.0f, width()/(float)height(), 0.0f, 100.0f);
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

    compileShader(vert, frag);
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
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vert_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, verts.size()/3);

    glDisableVertexAttribArray(0);
}

void GLWidget::compileShader(std::string v, std::string f)
{
    GLuint v_shader = glCreateShader(GL_VERTEX_SHADER);
    GLuint f_shader = glCreateShader(GL_FRAGMENT_SHADER);

    const char *v_char = v.c_str();
    const char *f_char = f.c_str();

    std::cout << v_char << '\n' << f_char;
    glShaderSource(v_shader, 1, &v_char, NULL);
    glShaderSource(f_shader, 1, &f_char, NULL);

    glCompileShader(v_shader);
    glCompileShader(f_shader);

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

GLWidget::~GLWidget()
{
    delete MVP;
    //delete &current_shader;
}
