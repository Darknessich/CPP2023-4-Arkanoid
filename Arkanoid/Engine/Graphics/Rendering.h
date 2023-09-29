#pragma once
#include <GLFW/glfw3.h>

class Rendering {
public:
  virtual void draw(GLFWwindow* window) const = 0;
  virtual ~Rendering() {};
};