#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "Point.h"


int default_velocity = 10;
int fps = 100;
Point point = Point();

void reshape_callback(int , int);
void timer_callback(int);
void keyboard_callback(int, int, int);

void init() {
    glClearColor(0, 0, 0, 1.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    point.Update();
    point.Draw();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("...");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape_callback);
    glutTimerFunc(0, timer_callback, 0);
    glutSpecialFunc(keyboard_callback);
    init();
    glutMainLoop();

    return 0;
}

void reshape_callback(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 500, 0.0, 500, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int) {
    glutPostRedisplay();
    glutTimerFunc(1000/fps, timer_callback, 0);
}

void keyboard_callback(int key, int, int) {
    switch(key) {
        case GLUT_KEY_UP:
            point.velocity = Vector(0, default_velocity);
            break;
        case GLUT_KEY_DOWN:
            point.velocity = Vector(0, -default_velocity);
            break;
        case GLUT_KEY_RIGHT:
            point.velocity = Vector(default_velocity, 0);
            break;
        case GLUT_KEY_LEFT:
            point.velocity = Vector(-default_velocity, 0);
            break;
    }
}
