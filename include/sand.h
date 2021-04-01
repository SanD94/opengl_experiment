#ifndef __SAND_H__
#define __SAND_H__
#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <vector>
#include <array>

#include <functional>
#include <algorithm>
#include <iterator>
#include <numeric>

#ifdef __APPLE__
#   include <OpenGL/OpenGL.h>
#   include <GLUT/glut.h>
#else
#   include <GL/glew.h>
#   include <GL/freeglut.h>
#   include <GL/freeglut_ext.h>
#endif // __APPLE__


#define BUFFER_OFFSET(offset) ((GLvoid*) (offset))


namespace Sand {
    GLuint InitShader(const std::string& vertexShaderFile,
                const std::string& fragmentShaderFile);
    
    const GLfloat DivideByZeroTolerance = GLfloat(1.0e-07);
    
    const GLfloat DegreesToRadians = M_PI / 180.0;
} // namespace Sand


#include "vec.h"
#include "mat.h"

using namespace Sand;

#endif // __SAND_H__