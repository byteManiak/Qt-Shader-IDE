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

struct vbo
{
	vbo() {}
	~vbo() {}
	vbo(GLfloat x, GLfloat y, GLfloat z, GLfloat uvx, GLfloat uvy, GLfloat nx, GLfloat ny, GLfloat nz)
		: vertex(vec3(x,y,z)), uv(vec2(uvx, uvy)), normal(vec3(nx, ny, nz)) {}
	vec3 vertex;
	vec2 uv;
	vec3 normal;
};

#endif // VEC3_H
