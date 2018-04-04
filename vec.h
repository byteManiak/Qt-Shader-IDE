#ifndef VEC3_H
#define VEC3_H

#include <GL/glew.h>

struct vec2
{
	vec2() {}
	~vec2() {}
	vec2(GLfloat x, GLfloat y) : x(x), y(y) {}
	GLfloat x, y;
};

struct vec3
{
	vec3() {}
	~vec3() {}
	vec3(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}
	GLfloat x, y, z;
};

#endif // VEC3_H
