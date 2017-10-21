#pragma once

#include <GL/glew.h>

enum MODE_RECT
{
	WITH_TEXTURE,
	WITHOUT_TEXTURE
};

class Rect
{
private:
	
	GLuint VAO;

	bool change_vao; //small optimization

	float w, h;

public:
	
	float x, y;

	Rect(float _x, float _y, float w,float h,MODE_RECT mode);
	~Rect();

	void init();
	void init_with_texture();

	void draw();
};