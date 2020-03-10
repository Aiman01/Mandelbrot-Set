#ifndef _CONTEXT_H
#define _CONTEXT_H

//--------Defines
#define GLFW_INCLUDE_NONE
#define WIDTH 1280.f
#define HEIGHT 720.f
#define KEY(x) GLFW_KEY_##x

//--------Includes
#include <stdio.h>
#include <stdlib.h>
#include "Include/glad/glad.h"
#include "GLFW/glfw3.h"

enum MOUSE_BUTTONS{
		   MOUSE_0,
		   MOUSE_1,
		   MOSUE_2
};


//--------PROTOTYPES
int  initContext(); // Initialize both glfw and glad
int  initGlfw(); // Initialize glfw
int  initGlad(); // Initialize glad
void cleanContext(); // Terminates the context
void updateContext(); // Update the buffers and poll request
int  contextShouldClose(); // See if the windows requested to close
void clearContext(); // Clears the context from previous render
void framebufferSizeCallback(GLFWwindow*, int, int);
void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
int isKeyPress(int key);
float getDelta();

//--------GLOBALS
GLFWwindow *WINDOW;
float CONTEXT_COLOR[4] = {0.f, 0.f, 0.f, 1.f};
float delta;
float lastFrame;
double mouseX;
double mouseY;
float previousTime=0;
float currentTime=0;

//--------FUNCTIONS
int initContext(){
  if(!initGlfw() || !initGlad()) return 0;
  return 1;
}
// Returns 1 if initialzed perfectly 0 otherwise
int initGlfw(){
  if(!glfwInit()){
    fprintf(stderr, "Unable to initialize glfw...\n");
    cleanContext();
    return 0;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  WINDOW = glfwCreateWindow(WIDTH, HEIGHT, "main", NULL, NULL);
  if(!WINDOW){
    fprintf(stderr, "Unable to create a window...\n");
    cleanContext();
    return 0;
  }
  glfwMakeContextCurrent(WINDOW);

  glfwSetFramebufferSizeCallback(WINDOW, framebufferSizeCallback);
  glfwSetCursorPosCallback(WINDOW, cursorPositionCallback);
  return 1;
}

// Returns 1 if initialzed perfectly 0 otherwise
int initGlad(){
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    fprintf(stderr, "Unable to initialize glad...\n");
    cleanContext();
    return 0;
  }
  glViewport(0, 0, WIDTH, HEIGHT);
  glEnable(GL_PROGRAM_POINT_SIZE);
  return 1;
}

void updateContext(){
  float currentFrame = glfwGetTime();
  delta = currentFrame - lastFrame;
  lastFrame = currentFrame;
  if(delta > .001f)delta=.001f;

  if(isKeyPress(GLFW_KEY_ESCAPE))
    glfwSetWindowShouldClose(WINDOW, 1);
  
  glfwSwapBuffers(WINDOW);
  glfwPollEvents();
}

// Cleans opengl
void cleanContext(){
  glfwTerminate();
}

int contextShouldClose(){ return glfwWindowShouldClose(WINDOW); }

void clearContext(){
  glClear(GL_COLOR_BUFFER_BIT);
}

void framebufferSizeCallback(GLFWwindow* win, int width, int height){
  glViewport(0, 0, width, height);
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos){
  mouseX = (float)xpos;
  mouseY = HEIGHT - (float)ypos;
}

int isKeyPress(int key){
  return glfwGetKey(WINDOW, key) == GLFW_PRESS;
}
int isKeyRelease(int key){
  return glfwGetKey(WINDOW, key) == GLFW_RELEASE;
}
int isMousePress(int key){
  return glfwGetMouseButton(WINDOW, key) == GLFW_PRESS;
}

int isMouseRelease(int key){
  return glfwGetMouseButton(WINDOW, key) == GLFW_RELEASE;
}

float getDelta(){ return delta; };
#endif // _CONTEXT_H
