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

const char* gleeReadFile(const char*);
void gleeUpdateFpsCounter(GLFWwindow*);
bool gleeLogStart();
bool gleeLog(const char*, ...);
bool gleeLogErr(const char*, ...);

