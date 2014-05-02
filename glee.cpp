#include "glee.h"

const char* gleeReadFile(const char* filename) {
  FILE *f = fopen(filename, "rb");
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);
  char* string = new char[fsize + 1];
  fread(string, fsize, 1, f);
  fclose(f);
  string[fsize] = 0;
  return string;
}

void gleeUpdateFpsCounter(GLFWwindow* window) {
  static double previous_seconds = glfwGetTime();
  static int frame_count;
  double current_seconds = glfwGetTime();
  double elapsed_seconds = current_seconds - previous_seconds;
  if (elapsed_seconds > 0.25) {
    previous_seconds = current_seconds;
    double fps = (double)frame_count / elapsed_seconds;
    char tmp[128];
    sprintf(tmp, "OpenGL @ fps: %.2f", fps);
    glfwSetWindowTitle(window, tmp);
    frame_count = 0;
  }
  frame_count++;
}

void gleeLog(const char* message) {
  printf("--------------------\n");
  printf("%s", message);
}


void gleeLogShader(GLuint shader) {
  int params = -1;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
  if (GL_TRUE != params) {
    printf("--------------------\n");
    fprintf(stderr, "ERROR: GL shader index %i did not compile\n", shader);
    int max_length = 2048;
    int actual_length = 0;
    char log[2048];
    glGetShaderInfoLog(shader, max_length, &actual_length, log);
    printf("shader info log for GL index %u:\n%s\n", shader, log);
  } else {
    printf("--------------------\n");
    printf("SHADER AT INDEX %i COMPILED SUCCESSFULLY\n", shader);
  }
}

void gleeLogProgram(GLuint program) {
  printf("--------------------\nSHADER PROGRAM %i INFO:\n", program);

  int params = -1;
  glGetProgramiv(program, GL_LINK_STATUS, &params);
  printf("GL_LINK_STATUS = %i\n", params);
  
  glGetProgramiv(program, GL_ATTACHED_SHADERS, &params);
  printf("GL_ATTACHED_SHADERS = %i\n", params);
  
  glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &params);
  printf("GL_ACTIVE_ATTRIBUTES = %i\n", params);
  for (int i = 0; i < params; i++) {
    char name[64];
    int max_length = 64;
    int actual_length = 0;
    int size = 0;
    GLenum type;
    glGetActiveAttrib(program,i,max_length,&actual_length,&size,&type,name);
    if (size > 1) {
      for(int j = 0; j < size; j++) {
        char long_name[64];
        sprintf(long_name, "%s[%i]", name, j);
        int location = glGetAttribLocation(program, long_name);
        printf("  %i.)  type:%s  name:%s  location:%i\n",
          i, gleeGLTypeToString(type), long_name, location);
      }
    } else {
      int location = glGetAttribLocation(program, name);
      printf("  %i) type:%s name:%s location:%i\n",
        i, gleeGLTypeToString(type), name, location);
    }
  }
  
  glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &params);
  printf("GL_ACTIVE_UNIFORMS = %i\n", params);
  for(int i = 0; i < params; i++) {
    char name[64];
    int max_length = 64;
    int actual_length = 0;
    int size = 0;
    GLenum type;
    glGetActiveUniform(
      program,
      i,
      max_length,
      &actual_length,
      &size,
      &type,
      name
    );
    if (size > 1) {
      for(int j = 0; j < size; j++) {
        char long_name[64];
        sprintf(long_name, "%s[%i]", name, j);
        int location = glGetUniformLocation(program, long_name);
        printf("    %i.)  type:%s  name:%s  location:%i\n",
          i, gleeGLTypeToString(type), long_name, location);
      }
    } else {
      int location = glGetUniformLocation(program, name);
      printf("    %i.)  type:%s  name:%s  location:%i\n",
        i, gleeGLTypeToString(type), name, location);
    }
  }
}

void gleeLogLinking(GLuint program) {
  // check if link was successful
  printf("--------------------\n");
  int params = -1;
  glGetProgramiv(program, GL_LINK_STATUS, &params);
  if (GL_TRUE != params) {
    fprintf(
	     stderr,
	     "ERROR: could not link shader program GL index %u\n",
	     program
	     );
    int max_length = 2048;
    int actual_length = 0;
    char log[2048];
    glGetProgramInfoLog(program, max_length, &actual_length, log);
    printf("program info log for GL index %u:\n%s", program, log);
  } else {
    printf("PROGRAM %i LINKED SUCCESSFULLY\n",program);
  }
}

const char* gleeGLTypeToString(GLenum type) {
  switch (type) {
    case GL_BOOL: return "bool";
    case GL_INT: return "int";
    case GL_FLOAT: return "float";
    case GL_FLOAT_VEC2: return "vec2";
    case GL_FLOAT_VEC3: return "vec3";
    case GL_FLOAT_VEC4: return "vec4";
    case GL_FLOAT_MAT2: return "mat2";
    case GL_FLOAT_MAT3: return "mat3";
    case GL_FLOAT_MAT4: return "mat4";
    case GL_SAMPLER_2D: return "sampler2D";
    case GL_SAMPLER_3D: return "sampler3D";
    case GL_SAMPLER_CUBE: return "samplerCube";
    case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
    default: break;
  }
  return "other";
}



