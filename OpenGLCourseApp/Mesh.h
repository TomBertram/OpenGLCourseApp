#pragma once

#include <GL/glew.h>
class Mesh
{
public:
  Mesh();
  
  void CreateMesh(GLfloat *verticies, unsigned int *indices, unsigned int numbOfVerticies, unsigned int numOfIndices);
  void RenderMesh();
  void ClearMesh();  
  
  ~Mesh();

private:
  GLuint VAO, VBO, IBO;
  GLsizei indexCount;

};

