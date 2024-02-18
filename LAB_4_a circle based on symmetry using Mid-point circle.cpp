#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>

int xc, yc, r;

void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x + xc, y + yc);
    glEnd();
}

void DMC(int x, int y)
{
    drawPixel(x, y);
    drawPixel(y, x);
    drawPixel(-y, x);
    drawPixel(-x, y);
    drawPixel(-x, -y);
    drawPixel(-y, -x);
    drawPixel(y, -x);
    drawPixel(x, -y);
}

void midpointCircle()
{
    int x = 0, y = r;
    int p = 5 / 4 - r;

    DMC(x, y);

    while (x < y)
    {

        if (p < 0)
        {
            x++;
            p += 2 * x + 1;
        }
        else
        {
            x++;
            y--;
            p += 2 * (x - y) + 1;
        }
        DMC(x, y);
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    midpointCircle();

    glFlush();
}

void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

int main(int argc, char **argv)
{
    printf("Enter x coordinate: ");
    scanf("%d", &xc);
    printf("Enter y coordinate: ");
    scanf("%d", &yc);
    printf("Enter radius r: ");
    scanf("%d", &r);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Midpoint Circle Drawing");
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS;
}
