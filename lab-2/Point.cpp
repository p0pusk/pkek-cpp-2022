#include "Point.h"
#include <cmath>


Point::Point()
    :position(100, 100), velocity(0, 0)
{

}

void Point::Draw() {
    glColor3f(0.5, 0, 0.5);
    std::queue<Vector> history = prev_position;
    float ratio;
    unsigned long size = history.size();
    int i = 1;
    while (!history.empty()) {
        Vector point = history.front();
        history.pop();
        ratio = (float)i / (float)size;
        DrawCircle(point.x, point.y, radius * ratio);
        i++;
    }

    glColor3f(1, 0, 1);
    DrawCircle(position.x, position.y, radius);
}

void Point::Update() {
    position = position + velocity;
    Drag(velocity);
    border_check(position);

    if (tail_position != position) {
        inside = false;
    }
    else {
        inside = true;
        delay = default_delay;
        std::queue<Vector> empty;
        std::swap(prev_position, empty);
    }

    if (!inside) {
        delay--;
        prev_position.push(position);
    }

    if (delay <= 0) {
        if (!prev_position.empty()) {
            tail_position = prev_position.front();
            prev_position.pop();
        }
    }
}

void border_check(Vector &pos) {
    if (pos.x > 500) pos.x = 0;
    if (pos.x < 0) pos.x = 500;
    if (pos.y > 500) pos.y = 0;
    if (pos.y < 0) pos.y = 500;
}

void Point::Drag(Vector &v) const {
    if (v.x > 0) {
        v.x -= drag.x;
        if (v.x < 0) v.x = 0;
    }
    else {
        v.x += drag.x;
        if (v.x > 0) v.x = 0;
    }

    if (v.y > 0) {
        v.y -= drag.y;
        if (v.y < 0) v.y = 0;
    }
    else {
        v.y += drag.y;
        if (v.y > 0) v.y = 0;
    }
}

void DrawCircle(float x, float y, float r) {
    glBegin(GL_POLYGON);
    float theta;
    for (int i = 0; i <= 360; i++) {
        theta = i * M_PI / 180;
        glVertex2f(x + r * cos(theta), y + r * sin(theta));
    }
    glEnd();
}