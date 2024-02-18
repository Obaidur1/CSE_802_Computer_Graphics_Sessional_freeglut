#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>

int x0, y0, x1, y1;

void drawLineBresenham(void)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int twoDy = 2 * dy;
    int twoDyMinusDx = 2 * (dy - dx);
    int p = 2 * dy - dx;

    int x, y;

    if (x0 > x1)
    {
        x = x1;
        y = y1;
        x1 = x0;
    }
    else
    {
        x = x0;
        y = y0;
    }

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();

    while (x < x1)
    {
        x++;
        if (p < 0)
        {
            p += twoDy;
        }
        else
        {
            y++;
            p += twoDyMinusDx;
        }

        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
    }

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
    printf("Enter x0 : ");
    scanf("%d", &x0);
    printf("Enter y0 : ");
    scanf("%d", &y0);
    printf("Enter x1 : ");
    scanf("%d", &x1);
    printf("Enter y1 : ");
    scanf("%d", &y1);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Bresenham's Line Drawing Algorithm");
    myInit();
    glutDisplayFunc(drawLineBresenham);
    glutMainLoop();

    return EXIT_SUCCESS;
}
