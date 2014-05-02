#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glee.h" //Custom C Library

int main() {
  if (!glfwInit()) {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  } 

  // uncomment these lines if on Apple OS X
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 4);

  //GLFWmonitor* mon = glfwGetPrimaryMonitor();
  //const GLFWvidmode* vmode = glfwGetVideoMode(mon);
  //GLFWwindow* window = glfwCreateWindow(vmode->width, vmode->height, "Hello Triangle", mon, NULL);
  GLFWwindow* window = glfwCreateWindow(1080, 720, "Hello Triangle", NULL, NULL);
  if (!window) {
    fprintf(stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);
                                  
  //start GLEW
  glewExperimental = GL_TRUE;
  glewInit();

  //get version info
  const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
  const GLubyte* version = glGetString(GL_VERSION); // version as a string
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

  //tell GL to only draw onto a pixel if the shape is closer to the viewer
  glEnable(GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

  GLfloat points[] = {
    -0.9f,  0.9f,  0.0f,
     0.0f, -0.9f,  0.0f,
    -0.9f, -0.9f,  0.0f,
     0.9f,  0.9f,  0.0f,
     0.9f, -0.9f,  0.0f,
     0.0f,  0.9f,  0.0f
  };

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  const char*  vertex_shader = gleeReadFile("./shader.vert.glsl");
  const char* fragment_shader = gleeReadFile("./shader.frag.glsl");

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);
  gleeLogShader(vs);
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);
  gleeLogShader(fs);

  GLuint program = glCreateProgram();
  glAttachShader(program, fs);
  glAttachShader(program, vs);
  glLinkProgram(program);
  gleeLogLinking(program);

  //Log Shader Compilation
  gleeLogProgram(program);

  while (!glfwWindowShouldClose(window)) {
    gleeUpdateFpsCounter(window);
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glfwPollEvents();
    glfwSwapBuffers(window);
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
      glfwSetWindowShouldClose(window, 1);
    }
  }
  // close GL context and any other GLFW resources
  glfwTerminate();
  return 0;
}

