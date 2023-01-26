#include <iostream>
#include <vector>
#include "tinygl-cpp.h"
#include <string>
#include <list>
using namespace tinygl;

struct renderCircle
{
  float x;
  float y;
  int diameter;
  std::string color;
  float opacity;
};

class MyWindow : public Window
{
public:
  MyWindow(int w, int h) : Window(w, h) {}

  float green_x = 30, green_y = 30, purple_x = 80, purple_y = 30, blue_x = 130,
        blue_y = 30, yellow_x = 180, yellow_y = 30, orange_x = 230, orange_y = 30;

  float paletteDiameter = 30;
  float brushDiameter = 15;
  float brushOpacity = 1;
  float paletteRadius = paletteDiameter / 2;
  std::list<renderCircle> strokes;
  std::string selectedColor = "green";

  void setup() override
  {
    std::cout << "Window size: " << width() << ", " << height() << std::endl;
  }

  virtual float getDistance(float p1_x, float p1_y, float p2_x, float p2_y)
  {
    return sqrt((p1_x - p2_x) * (p1_x - p2_x) + (p1_y - p2_y) * (p1_y - p2_y));
  }

  virtual float clamp(float v, float lo, float hi)
  {
    if (v > hi)
      return hi;
    if (v < lo)
      return lo;
    return v;
  }

  virtual void mouseMotion(int x, int y, int dx, int dy)
  {
    if (mouseIsDown(GLFW_MOUSE_BUTTON_LEFT))
    {
      if (y < 70)
      {
        return;
      }

      renderCircle newCircle;
      newCircle.x = x;
      newCircle.y = y;
      newCircle.diameter = brushDiameter;
      newCircle.opacity = brushOpacity;
      newCircle.color = selectedColor;

      strokes.push_back(newCircle);
    }
  }

  virtual void mouseDown(int button, int mods)
  {

    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
      // todo: check if user clicked a color
      float mx = mouseX(); // current mouse pos x
      float my = mouseY(); // current mouse pos y

      float distancegreen = getDistance(green_x, green_y, mx, my);
      float distancepurple = getDistance(purple_x, purple_y, mx, my);
      float distanceblue = getDistance(blue_x, blue_y, mx, my);
      float distanceyellow = getDistance(yellow_x, yellow_y, mx, my);
      float distanceorange = getDistance(orange_x, orange_y, mx, my);

      if (distancegreen < paletteRadius)
      {
        selectedColor = "green";
        std::cout << selectedColor << " was selected." << std::endl;
      }
      else if (distancepurple < paletteRadius)
      {
        selectedColor = "purple";
        std::cout << selectedColor << " was selected." << std::endl;
      }
      else if (distanceblue < paletteRadius)
      {
        selectedColor = "blue";
        std::cout << selectedColor << " was selected." << std::endl;
      }
      else if (distanceyellow < paletteRadius)
      {
        selectedColor = "yellow";
        std::cout << selectedColor << " was selected." << std::endl;
      }
      else if (distanceorange < paletteRadius)
      {
        selectedColor = "orange";
        std::cout << selectedColor << " was selected." << std::endl;
      }
    }
  }

  void keyDown(int key, int mods)
  {
    if (key == GLFW_KEY_UP)
    {
      brushDiameter = clamp(brushDiameter + 3, 5.0, 30.0);
      std::cout << "brush diameter: " << brushDiameter << std::endl;
    }
    else if (key == GLFW_KEY_DOWN)
    {
      brushDiameter = clamp(brushDiameter - 3, 5.0, 30.0);
      std::cout << "brush diameter: " << brushDiameter << std::endl;
    }
    else if (key == GLFW_KEY_LEFT)
    {
      brushOpacity = clamp(brushOpacity - .1, 0.1, 1);
      std::cout << "brush opacity: " << brushOpacity << std::endl;
    }
    else if (key == GLFW_KEY_RIGHT)
    {
      brushOpacity = clamp(brushOpacity + .1, 0.1, 1);
      std::cout << "brush opacity: " << brushOpacity << std::endl;
    }
    else if (key == GLFW_KEY_C)
    {
      strokes.clear();
      std::cout << "cleared screen!" << std::endl;
    }
  }

  void draw() override
  {

    background(0.95f, 0.95f, 0.95f); // parameters: r, g, b

    // color(1.0f, 0.5f, 0.5f);
    // circle(width() * 0.5f, height() * 0.5, 300);

    // todo : draw pallet
    color(0.1f, 0.1f, 0.1f);
    square(width() / 2.0f, 35, width(), 70);

    // green
    color(0.051, 0.455, 0.102);
    circle(green_x, green_y, paletteDiameter);
    // purple
    color(0.227, 0.09, 0.447);
    circle(purple_x, purple_y, paletteDiameter);
    // blue
    color(0.325, 0.596, 0.745);
    circle(blue_x, blue_y, paletteDiameter);
    // yellow
    color(0.949, 0.804, 0.365);
    circle(yellow_x, yellow_y, paletteDiameter);
    // orange
    color(0.871, 0.647, 0.294);
    circle(orange_x, orange_y, paletteDiameter);

    // Create an iterator of std::list
    std::list<renderCircle>::iterator it;
    // Make iterate point to begining and incerement it one by one till it reaches the end of list.
    for (it = strokes.begin(); it != strokes.end(); it++)
    {
      // Access the object through iterator
      float x = it->x;
      float y = it->y;
      float diameter = it->diameter;
      float opacity = it->opacity;
      std::string _color = it->color;

      if (_color == "green")
      {
        color(0.051, 0.455, 0.102, opacity);
      }
      else if (_color == "purple")
      {
        color(0.227, 0.09, 0.447, opacity);
      }
      else if (_color == "blue")
      {
        color(0.325, 0.596, 0.745, opacity);
      }
      else if (_color == "yellow")
      {
        color(0.949, 0.804, 0.365, opacity);
      }
      else if (_color == "orange")
      {
        color(0.871, 0.647, 0.294, opacity);
      }

      circle(x, y, diameter);
    }
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
