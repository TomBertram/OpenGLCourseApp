#pragma once

#include <stdio.h>
#include <xstring_insert.h>
#include <iostream>
#include <fstream>
#include <GL/glew.h>


class Shader
{
public:
  Shader();

  void CreateFromString(const char* vertexCode, const char* fragmentCode);
  void CreateFromFiles(const char* vertexLocation, const char* fragmentLocations);

  std::string ReadFile(const char* filelocation);

  GLuint GetProjectionLocation();
  GLuint GetModelLocation();
  GLuint GetViewLocation();

  void UseShader();
  void ClearShader();
  ~Shader();

private:
  GLuint shaderID, uniformProjection, uniformModel, uniformView;

  void CompileShader(const char* vertexCode, const char* fragmentCode);
  void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

