#include "Rect.h"

Rect::Rect(float _x, float _y, float _w,float _h, MODE_RECT mode) 
{	
	this->x = _x;
	this->y = _y;

	w = _w;
	h = _h;

	VAO = 0;

	change_vao = false;

	if (mode == WITH_TEXTURE)
	{
		init_with_texture();
	}
	else if(mode == WITHOUT_TEXTURE)
	{
		init();
	}
}

Rect::~Rect()
{
	glDeleteVertexArrays(1, &VAO);
}

void Rect::init()
{
	float z = 0.0f;

	float vertices[] =
	{
		this->x,this->y,z,
		this->x,this->y-h,z,
		this->x+w,this->y-h,z,
		this->x+w,this->y,z
	};

	unsigned int indices[] =
	{
		0,1,2,
		0,2,3
	};

	GLuint VBO, IBO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	glBindVertexArray(0);

	change_vao = true;
}

void Rect::init_with_texture()
{	

	float z = 0.0f;

	float vertices[] =
	{
		this->x,this->y,z,					0.0,0.0,
		this->x,this->y + h,z,				0.0,1.0,
		this->x + w,this->y + h,z,			1.0,1.0,
		this->x + w,this->y,z,				1.0,0.0
	};

	unsigned int indices[] =
	{
		0,1,2,
		0,2,3
	};

	GLuint VBO, IBO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),(void*)(3*sizeof(float)));

	glBindVertexArray(0);

	change_vao = true;
}

void Rect::draw()
{	
	if(change_vao)
	glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}