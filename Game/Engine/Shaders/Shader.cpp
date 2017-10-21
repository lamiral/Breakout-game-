#include "Shader.h"

Shader::Shader()
{
	vsShader = fsShader = program = 0;
}

Shader::~Shader()
{
	this->deleteProgram();
}

void Shader::loadShaders(const char *vs, const char *fs,int mode)
{
	if (mode == LOAD_FROM_FILE)
	{
		loadShaderFromFile(vs, fs);
	}
	else if(mode == LOAD_FROM_STRING)
	{
		loadShaderFromString(vs, fs);
	}
}

void Shader::loadShaderFromFile(const char *vsPath, const char *fsPath)
{
	std::fstream vsFile, fsFile;

	vsFile.open(vsPath);
	fsFile.open(fsPath);

	if (!vsFile.is_open())
	{
		std::cout << "Error : file vertex shader did not open." << std::endl;
		return;
	}
	else if (!fsFile.is_open())
	{
		std::cout << "Error : file fragment shader did not open." << std::endl;
		return;
	}

	std::stringstream streamVs, streamFs;

	streamVs << vsFile.rdbuf();
	streamFs << fsFile.rdbuf();

	vsFile.close();
	fsFile.close();

	std::string strVs, strFs;

	strVs = streamVs.str();
	strFs = streamFs.str();

	const char *resultVs = strVs.c_str();
	const char *resultFs = strFs.c_str();

	load(resultVs, resultFs);
}

void Shader::loadShaderFromString(const char *vsStr, const char *fsStr)
{
	load(vsStr, fsStr);
}

void Shader::load(const char *vsSouce, const char *fsSource)
{
	vsShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vsShader, 1, &vsSouce, NULL);
	glCompileShader(vsShader);

	fsShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsShader, 1, &fsSource, NULL);
	glCompileShader(fsShader);

	error(vsShader, SHADER);
	error(fsShader, SHADER);

	createProgram();
}

void Shader::createProgram()
{
	program = glCreateProgram();
	glAttachShader(program,vsShader);
	glAttachShader(program,fsShader);
	glLinkProgram(program);

	error(program,PROGRAM);
}

void Shader::error(GLuint object,TYPE type)
{
	if (type == SHADER)
	{
		shaderError(object);
	}
	else
	{
		programError(object);
	}
}

void Shader::programError(GLuint program)
{
	int link_status = 0;
	
	glGetProgramiv(program, GL_LINK_STATUS, &link_status);

	if (!link_status)
	{
		char buffer[512];
		glGetProgramInfoLog(program, 512, NULL, buffer);

		std::cout << buffer << std::endl;
	}
}

void Shader::shaderError(GLuint shader)
{
	int compile_status = 0;

	glGetShaderiv(program, GL_COMPILE_STATUS, &compile_status);

	if (!compile_status)
	{
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);

		std::cout << buffer << std::endl;
	}
}

void Shader::use()
{
	glUseProgram(program);
}

void Shader::stop()
{
	glUseProgram(0);
}

void Shader::deleteShader(TYPE shader_type)
{
	if (shader_type == FRAGMENT_SHADER)
	{
		glDeleteShader(fsShader);
	}
	else
	{
		glDeleteShader(vsShader);
	}
}

void Shader::deleteProgram()
{
	glUseProgram(0);
	this->deleteShader(VERTEX_SHADER);
	this->deleteShader(FRAGMENT_SHADER);
	glDeleteProgram(program);
}

GLuint Shader::getProgram() const
{
	return program;
}

void Shader::SetMatrix4fv(const char *uni_name, glm::mat4x4 &Matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(program, uni_name), 1, GL_FALSE, &Matrix[0][0]);
}