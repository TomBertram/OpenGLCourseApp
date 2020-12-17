#include "Window.h"



Window::Window()
{
  xChange = 0.0f;
  yChange = 0.0f;
  width = 900;
  height = 6000;

  for (size_t i = 0; i < 1024; i++)
  {
    keys[i] = 0;
  }
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
  xChange = 0.0f;
  yChange = 0.0f;
  width = windowWidth;
  height = windowHeight;

  for (size_t i = 0; i < 1024; i++)
  {
    keys[i] = 0;
  }
}

int Window::initialise()
{
  //initialize GLFW
  if (!glfwInit())
  {
    printf("GLEW initialization failed!");
    glfwTerminate();
    return 1;
  }

  //setup GLFW window properties
  //OpenGL version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //Core profile = No Backwards Compatibility
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  //Allow forward compatibility
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
  if (!mainWindow)
  {
    printf("GLFW window creation failed!");
    glfwTerminate();
    return 1;
  }

  //Handle key and mouse input
  createCallbacks();
  //glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  //Get Buffer Size Information
  glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

  //Set context for GLEW to use
  glfwMakeContextCurrent(mainWindow);

  //allow modern extension features
  glewExperimental = GL_TRUE;

  if (glewInit() != GLEW_OK)
  {
    printf("GLEW initialization failed!");
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
    return 1;
  }

  glEnable(GL_DEPTH_TEST);

  //Setup Viewport size
  glViewport(0, 0, bufferWidth, bufferHeight);

  glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
  glfwSetKeyCallback(mainWindow, handleKeys);
  glfwSetCursorPosCallback(mainWindow, handleMouse);
}

GLfloat Window::getXChange()
{
  GLfloat theChange = xChange;
  xChange = 0.0f;
  return theChange;
}

GLfloat Window::getYChange()
{
  GLfloat theChange = yChange;
  yChange = 0.0f;
  return theChange;
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
  Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }

if (key >= 0 && key < 1024)
  {
    if (action == GLFW_PRESS) 
    {
      theWindow->keys[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
      theWindow->keys[key] = false;
    }
  }
}


void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
  Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

  if (theWindow->mousedFirstMoved)
  {
    theWindow->lastX = xPos;
    theWindow->lastY = yPos;
    theWindow->mousedFirstMoved = false;
  }

  theWindow->xChange = xPos - theWindow->lastX;
  //this one is backwards to avoid inverted controls
  theWindow->yChange = theWindow->lastY - yPos;

  theWindow->lastX = xPos;
  theWindow->lastY = yPos;

}

Window::~Window()
{
  glfwDestroyWindow(mainWindow);
  glfwTerminate();
}
