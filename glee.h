/////////////////////////////////////////////////////////////////////
//
//  GLEE
//  by: eric bischoff
//  
//  glee is a utility library of the most common opengl function.
//
/////////////////////////////////////////////////////////////////////

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>

//General
const char* gleeReadFile(const char*);
void gleeUpdateFpsCounter(GLFWwindow*);

//Log
void gleeLog(const char*);
void gleeLogShader(GLuint);
void gleeLogProgram(GLuint);
void gleeLogLinking(GLuint);

//Utility
const char* gleeGLTypeToString (GLenum);

