#pragma once
#include <iostream>
#include "Vector.h"
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <queue>


class Point
{
  public:
    Vector velocity;

    Point();
    void Draw();
    void Update();

  private:
    Vector position;
    Vector tail_position = position;
    std::queue<Vector> prev_position;
    int default_delay = 20;
    int delay = default_delay;
    float radius = 10;
    Vector drag = Vector(0.5, 0.5);
    bool inside = true;

    void Drag(Vector &v) const;
};

void border_check(Vector &pos);
void DrawCircle(float x, float y, float r);


