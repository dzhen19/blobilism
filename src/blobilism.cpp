#include <iostream>
#include <vector>
#include "tinygl-cpp.h"
#include <string>
using namespace tinygl;
// using namespace std;

class MyWindow : public Window
{
public:
  MyWindow(int w, int h) : Window(w, h) {}

  float c1_x = 30, c1_y = 30, c2_x = 80, c2_y = 30, c3_x = 130,
        c3_y = 30, c4_x = 180, c4_y = 30, c5_x = 230, c5_y = 30;
  float diameter = 30;
  float radius = diameter / 2;
  std::string selectedColor = "c1";

  void setup() override
  {
    std::cout << "Window size: " << width() << ", " << height() << std::endl;
  }

  virtual float getDistance(float p1_x, float p1_y, float p2_x, float p2_y)
  {
    return sqrt((p1_x - p2_x) * (p1_x - p2_x) + (p1_y - p2_y) * (p1_y - p2_y));
  }

  virtual void mouseMotion(int x, int y, int dx, int dy)
  {
    if (mouseIsDown(GLFW_MOUSE_BUTTON_LEFT))
    {
      // todo: store a circle with the current color, size, x, y
      // std::cout << "x: " << x << " y: " << y << " dx: " << dx << " dy: " << dy << std::endl;
      color(0.051, 0.455, 0.102);
      circle(x, y, 10);
    }
  }

  virtual void mouseDown(int button, int mods)
  {

    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
      // todo: check if user clicked a color
      float mx = mouseX(); // current mouse pos x
      float my = mouseY(); // current mouse pos y

      float distanceC1 = getDistance(c1_x, c1_y, mx, my);
      float distanceC2 = getDistance(c2_x, c2_y, mx, my);
      float distanceC3 = getDistance(c3_x, c3_y, mx, my);
      float distanceC4 = getDistance(c4_x, c4_y, mx, my);
      float distanceC5 = getDistance(c5_x, c5_y, mx, my);

      if (distanceC1 < radius)
      {
        selectedColor = "c1";
      }
      else if (distanceC2 < radius)
      {
        selectedColor = "c2";
      }
      else if (distanceC3 < radius)
      {
        selectedColor = "c3";
      }
      else if (distanceC4 < radius)
      {
        selectedColor = "c4";
      }
      else if (distanceC5 < radius)
      {
        selectedColor = "c5";
      }
      // std::cout << "distanceC1" << distanceC1 << "distanceC2" << distanceC2 << "distanceC3" << distanceC3 << "distanceC4" << distanceC4 << "distanceC5" << distanceC5 << std::endl;
      std::cout << selectedColor << std::endl;
    }
  }

  void keyDown(int key, int mods)
  {
    if (key == GLFW_KEY_UP)
    {
      // increase size of circle
    }
    else if (key == GLFW_KEY_DOWN)
    {
      // decrease size of circle
    }
    else if (key == GLFW_KEY_LEFT)
    {
      // decrease alpha
    }
    else if (key == GLFW_KEY_RIGHT)
    {
      // increase alpha
    }
    else if (key == GLFW_KEY_C)
    {
      // clear vector of circles
    }
  }

  void draw() override
  {
    background(0.95f, 0.95f, 0.95f); // parameters: r, g, b

    color(1.0f, 0.5f, 0.5f);
    circle(width() * 0.5f, height() * 0.5, 300);

    // todo : draw pallet
    color(0.1f, 0.1f, 0.1f);
    square(width() / 2.0f, 35, width(), 70);

    // c1
    color(0.051, 0.455, 0.102);
    circle(c1_x, c1_y, diameter);
    // c2
    color(0.227, 0.09, 0.447);
    circle(c2_x, c2_y, diameter);
    // c3
    color(0.325, 0.596, 0.745);
    circle(c3_x, c3_y, diameter);
    // c4
    color(0.949, 0.804, 0.365);
    circle(c4_x, c4_y, diameter);
    // c5
    color(0.871, 0.647, 0.294);
    circle(c5_x, c5_y, diameter);
  }

private:
  // todo: create member variables for
  // current circle size
  // current transparency
  // current color
  // list of circles to draw each frame
  // color pallet
};

int main()
{
  MyWindow window(500, 500);
  window.run();
}
