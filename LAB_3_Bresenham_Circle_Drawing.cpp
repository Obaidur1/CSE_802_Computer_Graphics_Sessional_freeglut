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
    glVertex2i(x, y);
    glEnd();
}

void displayBresenhamCircle(int x, int y)
{
    drawPixel(xc + x, yc + y);
    drawPixel(xc - x, yc + y);
    drawPixel(xc + x, yc - y);
    drawPixel(xc - x, yc - y);
    drawPixel(xc + y, yc + x);
    drawPixel(xc - y, yc + x);
    drawPixel(xc + y, yc - x);
    drawPixel(xc - y, yc - x);
}

void bresenhamCircle()
{
    int x = 0, y = r;
    int d = 3 - 2 * r;

    while (x <= y)
    {
        displayBresenhamCircle(x, y);

        x++;

        if (d < 0)
        {
            d = d + 4 * x + 6;
        }
        else
        {
            d = d + 4 * (x - y) + 10;
            y--;
        }

        displayBresenhamCircle(x, y);
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    bresenhamCircle();

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
    printf("Enter x coordinate : ");
    scanf("%d", &xc);
    printf("Enter y coordinate : ");
    scanf("%d", &yc);
    printf("Enter radius r : ");
    scanf("%d", &r);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Bresenham's Circle Drawing Algorithm");
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS;
}
