#ifndef GRAPHICS_HEADERS_H
#define GRAPHICS_HEADERS_H

#include <iostream>

#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#define GLM_ENABLE_EXPERIMENTAL 

#if defined(__APPLE__) || defined(MACOSX)
  #include <OpenGL/gl3.h>
  #include <OpenGL/GLU.h>
#else //linux as default
  #include <GL/glew.h>
  //#include <GL/glu.h>
#endif

// GLM for matricies
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <Magick++.h>
#include <Physics.h>

#define INVALID_UNIFORM_LOCATION 0x7fffffff

struct Vertex
{
  glm::vec3 vertex;
  glm::vec3 color;
  glm::vec2 uv;
  glm::vec3 normal;
  Vertex(glm::vec3 v, glm::vec3 c, glm::vec2 u, glm::vec3 n) : vertex(v), color(c), uv(u), normal(n) {}
};

struct meshInfo
{
  unsigned int meshSize, meshStartIndex;
  meshInfo(unsigned int a, unsigned int b) : meshSize(a), meshStartIndex(b) {}
};
#endif /* GRAPHICS_HEADERS_H */
