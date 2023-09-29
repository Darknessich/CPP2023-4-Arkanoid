#pragma once
#include <GLFW/glfw3.h>

class Rendered {
public:
  virtual void draw(GLFWwindow* window) const = 0;
  virtual ~Rendered() {};
};