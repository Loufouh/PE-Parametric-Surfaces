// -------------------------------------------
// gMini : a minimal OpenGL/GLUT application
// for 3D graphics.
// Copyright (C) 2006-2008 Tamy Boubekeur
// All rights reserved.
// -------------------------------------------

// -------------------------------------------
// Disclaimer: this code is dirty in the
// meaning that there is no attention paid to
// proper class attribute access, memory
// management or optimisation of any kind. It
// is designed for quick-and-dirty testing
// purpose.
// -------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstdlib>

#define _USE_MATH_DEFINES

#include <cmath>

#include <algorithm>
#include <GL/glut.h>
#include <float.h>
#include "src/Vec3.h"
#include "src/Camera.h"


//Basis ( origin, i, j ,k )
struct Basis {
    inline Basis(Vec3 const &i_origin, Vec3 const &i_i, Vec3 const &i_j, Vec3 const &i_k) {
        origin = i_origin;
        i = i_i;
        j = i_j;
        k = i_k;
    }

    inline Basis() {
        origin = Vec3(0., 0., 0.);
        i = Vec3(1., 0., 0.);
        j = Vec3(0., 1., 0.);
        k = Vec3(0., 0., 1.);
    }

    Vec3 operator[](unsigned int ib) {
        if (ib == 0) return i;
        if (ib == 1) return j;
        return k;
    }

    Vec3 origin;
    Vec3 i;
    Vec3 j;
    Vec3 k;
};


// -------------------------------------------
// OpenGL/GLUT application code.
// -------------------------------------------

static GLint window;
static unsigned int SCREENWIDTH = 1600;
static unsigned int SCREENHEIGHT = 900;
static Camera camera;
static bool mouseRotatePressed = false;
static bool mouseMovePressed = false;
static bool mouseZoomPressed = false;
static int lastX = 0, lastY = 0, lastZoom = 0;
static bool fullScreen = false;

// ------------------------------------
// Application initialization
// ------------------------------------
void init() {
    camera.resize(SCREENWIDTH, SCREENHEIGHT);
    glCullFace(GL_BACK);
    glDisable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 1.0f, 1.0f);
    glEnable(GL_COLOR_MATERIAL);
}


#include "parametric_curves/casteljau.h"

std::vector< std::vector<Vec3> > gridControlPoints;
std::vector<Vec3> linePoints;

unsigned int nbControlPointsU = 10;
unsigned int nbControlPointsV = 10;

unsigned int nbU = 50;
unsigned int nbV = 50;

std::vector< std::vector<Vec3> > isoCurves;

void setupGridControlPoints() {
    gridControlPoints.clear();

    for(int i = 0; i < nbControlPointsU; i++) {
        gridControlPoints.push_back({});

        float x = 2.0 * (float) i / (float) nbControlPointsU - 1;

        for(int j = 0; j < nbControlPointsV; j++) {
            float y = 2.0 * (float) j / (float) nbControlPointsV - 1;

            gridControlPoints.back().push_back(
                   Vec3(
                           x,
                           y,
                           x*x + y*y
                   )
            );
        }
    }

}
#include "surface_bernstein/surface_bernstein.h"

void setupIsoCurves() {
    isoCurves = BezierSurfaceByBernstein(
            gridControlPoints,
            gridControlPoints.size(),
            gridControlPoints.front().size(),
            nbU,
            nbV
    );
}

void setup() {
    setupGridControlPoints();

    setupIsoCurves();
}

void update() {

}

// ------------------------------------
// Rendering.
// ------------------------------------

void drawCurveFromPoints(const std::vector<Vec3> &points) {
    glBegin(GL_LINES);

    for (int i = 0; i < points.size() - 1; i++) {
        Vec3 p1 = points[i];
        Vec3 p2 = points[i + 1];

        glVertex3f(
                p1[0],
                p1[1],
                p1[2]
        );
        glVertex3f(
                p2[0],
                p2[1],
                p2[2]
        );
    }

    glEnd();
}

void drawCircle(const Vec3 &center, float radius) {
    glBegin(GL_POLYGON);

    for (int i = 0; i < 10; i++) {
        float angle = 2 * M_PI * (float) i / (float) 10;

        glVertex3f(
                center[0] + radius * cos(angle),
                center[1] + radius * sin(angle),
                center[2]
        );
    }

    glEnd();
}

void drawControlPoints() {
    glColor3f(1, .2, .2);

    for (std::vector<Vec3> &row: gridControlPoints) {
        for(Vec3 &point : row) {
            drawCircle(point, .01);
        }
    }
}

void drawSurface() {
    glLineWidth(1);
    glColor3f(0, 0, 0);

    for(std::vector<Vec3> &curve : isoCurves) {
        drawCurveFromPoints(curve);
    }
}

//Draw function
void draw() {
    glLineWidth(3);

    drawControlPoints();

    drawSurface();
}

void display() {
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera.apply();
    update();
    draw();
    glFlush();
    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

// ------------------------------------
// User inputs
// ------------------------------------
//Keyboard event
void key(unsigned char keyPressed, int x, int y) {
    switch (keyPressed) {
        case 'f':
            if (fullScreen) {
                glutReshapeWindow(SCREENWIDTH, SCREENHEIGHT);
                fullScreen = false;
            } else {
                glutFullScreen();
                fullScreen = true;
            }
            break;

        default:
            break;
    }
    idle();
}

//Mouse events
void mouse(int button, int state, int x, int y) {
    if (state == GLUT_UP) {
        mouseMovePressed = false;
        mouseRotatePressed = false;
        mouseZoomPressed = false;
    } else {
        if (button == GLUT_LEFT_BUTTON) {
            camera.beginRotate(x, y);
            mouseMovePressed = false;
            mouseRotatePressed = true;
            mouseZoomPressed = false;
        } else if (button == GLUT_RIGHT_BUTTON) {
            lastX = x;
            lastY = y;
            mouseMovePressed = true;
            mouseRotatePressed = false;
            mouseZoomPressed = false;
        } else if (button == GLUT_MIDDLE_BUTTON) {
            if (mouseZoomPressed == false) {
                lastZoom = y;
                mouseMovePressed = false;
                mouseRotatePressed = false;
                mouseZoomPressed = true;
            }
        }
    }

    idle();
}

//Mouse motion, update camera
void motion(int x, int y) {
    if (mouseRotatePressed == true) {
        camera.rotate(x, y);
    } else if (mouseMovePressed == true) {
        camera.move((x - lastX) / static_cast<float>(SCREENWIDTH), (lastY - y) / static_cast<float>(SCREENHEIGHT),
                    0.0);
        lastX = x;
        lastY = y;
    } else if (mouseZoomPressed == true) {
        camera.zoom(float(y - lastZoom) / SCREENHEIGHT);
        lastZoom = y;
    }
}


void reshape(int w, int h) {
    camera.resize(w, h);
}

// ------------------------------------
// Start of graphical application
// ------------------------------------
int main(int argc, char **argv) {
    if (argc > 2) {
        exit(EXIT_FAILURE);
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT);
    window = glutCreateWindow("TP | Surfaces paramétriques");

    init();
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutReshapeFunc(reshape);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    key('?', 0, 0);

    setup();

    glutMainLoop();
    return EXIT_SUCCESS;
}

