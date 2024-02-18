#include <GL/glut.h>
#include <cmath>

// Coordinates of the triangle vertices
GLfloat triangle[3][2] = {{-0.5, -0.5}, {0.5, -0.5}, {0.0, 0.5}};

// Coordinates of the point to rotate around
GLfloat pivot[2] = {0.0, 0.0};

// Angle of rotation
GLfloat angle = 0.0;

// Rotation speed
GLfloat rotationSpeed = 0.5; // Decreased rotational speed

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw triangle
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 1.0); // White color
    for (int i = 0; i < 3; ++i)
    {
        glVertex2fv(triangle[i]);
    }
    glEnd();

    glPushMatrix();

    // Rotate the triangle around the pivot point
    glTranslatef(pivot[0], pivot[1], 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(-pivot[0], -pivot[1], 0.0);

    // Draw the rotated triangle
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0); // Red color
    for (int i = 0; i < 3; ++i)
    {
        glVertex2fv(triangle[i]);
    }
    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void idle()
{
    angle += rotationSpeed; // Increment angle for rotation
    if (angle >= 360.0)
        angle -= 360.0;
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Triangle Rotation");

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
