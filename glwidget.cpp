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

	verts.push_back(vec3(-1.0f, -1.0f, 0.0f));
	verts.push_back(vec3(1.0f, -1.0f, 0.0f));
	verts.push_back(vec3(1.0f, 1.0f, 0.0f));
	verts.push_back(vec3(-1.0f, 1.0f, 0.0f));
	uvs.push_back(vec2(0.0f, 0.0f));
	uvs.push_back(vec2(1.0f, 0.0f));
	uvs.push_back(vec2(1.0f, 1.0f));
	uvs.push_back(vec2(0.0f, 1.0f));
	// declare square coordinates for default shader

	elems.push_back(0);
	elems.push_back(1);
	elems.push_back(2);
	elems.push_back(0);
	elems.push_back(2);
	elems.push_back(3);

	glGenVertexArrays(1, &vertexArray);	// create vertex array for the data that will be declared next
	glBindVertexArray(vertexArray);	// and bind it

	glGenBuffers(3, vertexBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3)*verts.size(), verts.data(), GL_STATIC_DRAW);
    // write square to buffer

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// create vertex array pointer to the square buffer

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec2)*uvs.size(), uvs.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffers[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned)*elems.size(), elems.data(), GL_STATIC_DRAW);

	glGenTextures(1, &texture);
	// create a texture to be used in the context if needed

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	glDepthRange(0.0001f, 100.0f);
	glDepthFunc(GL_LESS);

	glClearColor(0,0,0,1);
}

void GLWidget::loadTexture(QString path)
{
	if(path == "") return;	// if there is no file loaded, don't do anything
	QImage image = QImage(path);	// load image from path
	image = image.convertToFormat(QImage::Format_RGBA8888, Qt::AutoColor);	// convert image to RGBA
	image = image.mirrored();	// flip it

	show();	// make context visible to be able to load the texture
	glBindTexture(GL_TEXTURE_2D, texture);	// bind the GL texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(),
				 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());	// write image to GL texture

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// set texture filtering - the texture doesn't render without these 2 lines

	glBindTexture(GL_TEXTURE_2D, 0);	// unbind the GL texture
	close();	// close the context as it is no longer needed
}

void GLWidget::loadModel(QString path)
{
	/** CLARIFICATION:
	 * An .obj file contains different vertices, indices and faces on every line in the following way:
	 * - If a line begins with "v", then that is a modelspace vertex coordinate
	 * - If a line begins with "vt", then that is a UV coordinate for texture mapping
	 * - If a line begins with "vn", then that is a vertex normal coordinate for lighting (unused here)
	 * - If a line begins with "f", then that is a face, which is made up of multiple vertices.
	 *	Such a line can have 4 different formats:
	 *	- When there are no "vt" or "vn" lines, the face will only have "v" coordinates
	 *	- When there are "vt" lines, the face can have either "v/vt" or "v/vt/vn" coordinates
	 *	- When there are "vn" lines, the face can have either "v/vt/vn" or "v//vn" coordinates
	**/

	if(path == "") return;	// if there is no file loaded, don't do anything
	std::ifstream file(path.toStdString());	// open file located at "path"

	verts.clear();
	verts.shrink_to_fit();
	elems.clear();
	elems.shrink_to_fit();
	uvs.clear();
	uvs.shrink_to_fit();

	std::string line;	// declare a string that will hold the contents of every line in the file
	while(std::getline(file, line))
	{
		std::stringstream lineStream(line);	// make a stream from the string to tokenize it
		std::string token;
		std::getline(lineStream, token, ' ');	// tokenize to see what the first argument of a line is
		if(token == "v")	// look for vertex coordinates first
		{
			vec3 tempVertex;
			lineStream >> tempVertex.x >> tempVertex.y >> tempVertex.z;
			tempVertex.z -= 0.5f;
			verts.push_back(tempVertex);	// put the coordinates in the buffer
		}
		else if(token == "vt")	// look for UV coordinates
		{
			hasUVs = true;
			// if line has UV coord, then we can apply v/vt or v/vt/vn when we look for "f"
			vec2 tempVertex;
			lineStream >> tempVertex.x >> tempVertex.y;
			uvs.push_back(tempVertex);
		}
		else if(token == "vn") hasNormals = true;	// we don't need normals in the IDE (yet)
		// if line has normal coord, then we can apply v/vt/vn or v//vn when we look for "f"
		else if(token == "f")
		{
			if(!hasUVs && !hasNormals)	// if format of "f" is just "v"
			{
				/** CLARIFICATION:
				 * Because of the way this program works, in order to make a polygon face draw properly,
				 * the following improvisations were used:
				 * - The face is considered to be convex and as if it was drawn using GL_TRIANGLE_FAN
				 * - As such, the face was "parsed" into adjacent triangles that all share the first
				 * coordinate.
				 * I have no idea what the impact of such an overhead poses, but I suspect it to be
				 * within the bounds of O(n) in both memory and speed efficiency.
				 **/

				std::string str = lineStream.str();	// convert stream back into string
				str = str.substr(str.find(' ')+1, str.size());
				// get the rest of the string after the first whitespace
				unsigned v1;
				sscanf(str.c_str(), "%d", &v1);	// this is our first face coordinate
				while(str.find(' ') != 0)
				{
					str = str.substr(str.find(' ')+1, str.size());
					// carry on with "parsing" the other coordinates
					unsigned v2, v3;
					if(sscanf(str.c_str(), "%d %d", &v2, &v3) != 2) break;
					// if 2 coordinates were not read, then the end of the face was reached
					elems.push_back(v1-1);
					elems.push_back(v2-1);
					elems.push_back(v3-1);
					// put triangle in the element array
				}
			}
			else if(!hasNormals)	// if format of "f" is "v/vt"
			{

			}
			else if(!hasUVs)	// if format of "f" is "v//vn"
			{

			}
			else	// if format of "f" is "v/vt/vn"
			{

			}
		}
	}

	normalize();

	/** WHAT IS LEFT TO DO HERE TO GET MODELS WORKING:
	 * - check face lines (the ones starting with "f")
	 * - implement the "f" line formats (though vn is useless in this case)
	 * - rearrange arrays according to face numbers
	 * - draw from element array with face numbers
	**/

	show();

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3)*verts.size(), verts.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec2)*uvs.size(), uvs.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffers[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned)*elems.size(), elems.data(), GL_STATIC_DRAW);
	close();
}

void GLWidget::paintGL()
{
	glViewport(0, 0, width(), height());	// GL context always has the size of the window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// clear the color buffer
	glClearDepth(1);

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
	glEnableVertexAttribArray(1);
    // bind current vertex array

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffers[2]);

	glDrawElements(GL_TRIANGLES, elems.size(), GL_UNSIGNED_INT, 0);
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

void GLWidget::normalize()
{
	float max = 0.0f;
	for(auto i : verts)
	{
		if(i.x > max) max = i.x;
		if(i.y > max) max = i.y;
		if(i.z > max) max = i.z;
	}
	for(auto &&i : verts)
	{
		i.x /= max;
		i.y /= max;
		i.z /= max;
	}
}

GLWidget::~GLWidget()
{

}
