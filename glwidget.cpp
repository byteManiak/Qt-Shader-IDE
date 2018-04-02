#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent), time(0.0f)
{
	setWindowTitle("GL Context");
}

void GLWidget::initializeGL()
{
	makeCurrent();	// make this widget the GL context
	glewExperimental = GL_TRUE;
	glewInit();	// enable glew functions

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
    verts.push_back(0.0f);      // declare square coordinates for 2D shaders

    GLuint vert_array_id;
	glGenVertexArrays(1, &vert_array_id);	// create vertex array for the data that will be declared next
	glBindVertexArray(vert_array_id);	// and bind it

    glGenBuffers(1, &vert_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vert_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*verts.size(), verts.data(), GL_STATIC_DRAW);
    // write square to buffer

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// create vertex array pointer to the square buffer

	glGenTextures(1, &texture);
	// create a texture to be used in the context if needed
}

void GLWidget::loadTexture(QString path)
{
	QImage image = QImage(path);	// load image from path
	image.convertToFormat(QImage::Format_RGBA8888, Qt::AutoColor);	// convert image to RGBA
	image = image.mirrored();	// flip it (needed?)

	glBindTexture(GL_TEXTURE_2D, texture);	// bind the GL texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(),
				 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());	// write image to GL texture

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// set texture filtering - the texture doesn't render without these 2 lines

	glBindTexture(GL_TEXTURE_2D, 0);	// unbind the GL texture
}

void GLWidget::loadModel()
{

}

void GLWidget::paintGL()
{
	glViewport(0, 0, width(), height());	// GL context always has the size of the window
	glClear(GL_COLOR_BUFFER_BIT);	// clear the color buffer

	glUseProgram(current_shader);	// use the current shader code

	time += 0.01f;	// increase time (to do: base on real time)

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	// bind texture to unit 0

    glUniform1f(glGetUniformLocation(current_shader, "time"), time);
    glUniform2f(glGetUniformLocation(current_shader, "resolution"), this->width(), this->height());
	glUniform1i(glGetUniformLocation(current_shader, "tex"), 0);
	// update shader uniforms

    glEnableVertexAttribArray(0);
    // bind current vertex array

    glDrawArrays(GL_TRIANGLE_FAN, 0, verts.size()/3);
	// draw the current array buffer
}

void GLWidget::compileShader(std::string v, std::string f)
{
	std::string vv = "#version 330 core\n" + v;
	std::string ff = "#version 330 core\n" + f;
    // concatenate shader "heads" with code from the IDE

    GLuint v_shader = glCreateShader(GL_VERTEX_SHADER);
    GLuint f_shader = glCreateShader(GL_FRAGMENT_SHADER);
    // declare empty shaders

    const char *v_char = vv.c_str();
    const char *f_char = ff.c_str();
    // convert to C strings for GL functions

    glShaderSource(v_shader, 1, &v_char, NULL);
    glShaderSource(f_shader, 1, &f_char, NULL);
    // send code to GL shaders

    /** compile vertex shader **/

    glCompileShader(v_shader);

    GLint v_shader_status;
    glGetShaderiv(v_shader, GL_COMPILE_STATUS, &v_shader_status);
    // see if shader compiled properly

    if(v_shader_status == GL_FALSE) // if shader didn't compile, output error
    {
		close();
        GLint v_maxLength;
        glGetShaderiv(v_shader, GL_INFO_LOG_LENGTH, &v_maxLength);
        // get length of error text

        std::vector<GLchar> t_str(v_maxLength);
        glGetShaderInfoLog(v_shader, v_maxLength, &v_maxLength, &t_str[0]);
        // get error text

        std::string v_str = "In vertex shader:\n";
        v_str += t_str.data();
        emit shaderError(QString::fromStdString(v_str));
        // send text to textbox
    }

    /** repeat above but for the fragment shader **/

    glCompileShader(f_shader);

    GLint f_shader_status;
    glGetShaderiv(f_shader, GL_COMPILE_STATUS, &f_shader_status);

    if(f_shader_status == GL_FALSE)
	{
		close();
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
    // move vertex and fragment shaders to program

    glDetachShader(shader_program, v_shader);
    glDetachShader(shader_program, f_shader);
    glDeleteShader(v_shader);
    glDeleteShader(f_shader);
    // old shaders are unneeded now so delete them

    current_shader = shader_program;
	// push shader to context
}

void GLWidget::reset() { time = 0; }

GLWidget::~GLWidget()
{

}
