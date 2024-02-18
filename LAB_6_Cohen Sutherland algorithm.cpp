#include <GL/freeglut.h>
#include <iostream>

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

const int x_min = 50;
const int x_max = 250;
const int y_min = 50;
const int y_max = 250;

int computeCode(int x, int y)
{
    int code = INSIDE;

    if (x < x_min)
        code |= LEFT;
    else if (x > x_max)
        code |= RIGHT;

    if (y < y_min)
        code |= BOTTOM;
    else if (y > y_max)
        code |= TOP;

    return code;
}

void CohenSutherlandClip(int x0, int y0, int x1, int y1)
{
    int code0 = computeCode(x0, y0);
    int code1 = computeCode(x1, y1);
    bool accept = false;

    while (true)
    {
        if (!(code0 | code1))
        {
            // Both endpoints inside window, accept the line
            accept = true;
            break;
        }
        else if (code0 & code1)
        {
            // Both endpoints outside window, reject the line
            break;
        }
        else
        {
            // Line needs clipping
            int code_out = code0 ? code0 : code1;
            int x, y;

            // Find intersection point
            if (code_out & TOP)
            {
                x = x0 + (x1 - x0) * (y_max - y0) / (y1 - y0);
                y = y_max;
            }
            else if (code_out & BOTTOM)
            {
                x = x0 + (x1 - x0) * (y_min - y0) / (y1 - y0);
                y = y_min;
            }
            else if (code_out & RIGHT)
            {
                y = y0 + (y1 - y0) * (x_max - x0) / (x1 - x0);
                x = x_max;
            }
            else
            {
                y = y0 + (y1 - y0) * (x_min - x0) / (x1 - x0);
                x = x_min;
            }

            if (code_out == code0)
            {
                x0 = x;
                y0 = y;
                code0 = computeCode(x0, y0);
            }
            else
            {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
        }
    }

    if (accept)
    {
        // Drawing the clipped line
        glColor3f(1.0, 0.0, 0.0); // Red color
        glBegin(GL_LINES);
        glVertex2i(x0, y0);
        glVertex2i(x1, y1);
        glEnd();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); // Black color

    // Drawing the clipping window
    glBegin(GL_LINE_LOOP);
    glVertex2i(x_min, y_min);
    glVertex2i(x_max, y_min);
    glVertex2i(x_max, y_max);
    glVertex2i(x_min, y_max);
    glEnd();

    // Defining the line to be clipped
    int x0 = 30, y0 = 60, x1 = 300, y1 = 200;

    // Drawing the original line
    glColor3f(0.0, 0.0, 1.0); // Blue color
    glBegin(GL_LINES);
    glVertex2i(x0, y0);
    glVertex2i(x1, y1);
    glEnd();

    // Clipping the line using Cohen Sutherland algorithm
    CohenSutherlandClip(x0, y0, x1, y1);

    glFlush();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    gluOrtho2D(0, 400, 0, 300);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 300);
    glutCreateWindow("Cohen Sutherland Line Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
