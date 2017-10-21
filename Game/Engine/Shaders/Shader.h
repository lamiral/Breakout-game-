#pragma once

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "glm\mat4x4.hpp"

//Error constants
enum
{	
	ERROR = 0,
	SHADER_ERROR = 1,
	PROGRAM_ERROR = 2,
};

//Shaders constatns
enum TYPE
{	
	SHADER,
	PROGRAM,
	VERTEX_SHADER,
	FRAGMENT_SHADER
};

//Load format constants
enum
{
	LOAD_FROM_FILE = 1,
	LOAD_FROM_STRING = 2,
};

class Shader
{
private:

	GLuint vsShader, fsShader, program;

	void error(GLuint object,TYPE);

	void shaderError(GLuint shader);
	void programError(GLuint program);

	void loadShaderFromString(const char *vsStr, const char *fsStr);
	void loadShaderFromFile(const char *vsPath, const char *fsPath);

	void load(const char *vsSource,const char *fsSource);
	void createProgram();

public:

	Shader();
	~Shader();

	void loadShaders(const char *vs, const char *fs, int load_mode);
	//void loadShader(const char *shader,TYPE);

	void use();
	void stop();

	void deleteProgram();
	void deleteShader(TYPE);

	GLuint getProgram() const;


	//Set uniforms...
	void SetMatrix4fv(const char *uni_name,glm::mat4x4 &Matrix);
};