using namespace std;

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>

#include "data.h"

const int NUM=50;
GLuint circle;
GLuint square;
GLuint triangle;
circles c[100];
squares s[100];
triangles t[100];

GLvoid BuildList(){
    circle = glGenLists(3);
    square = circle + 1;
    triangle = circle + 2;

    glNewList(circle,GL_COMPILE);
        glColor3f(1.0, 0.0, 0.0);
        glutSolidSphere(0.05,10,10);
    glEndList();

    glNewList(square,GL_COMPILE);
        glColor3f(0.0, 0.0, 1.0);
        glRectf(0.05,0.05,-0.05,-0.05);
    glEndList();

    glNewList(triangle,GL_COMPILE);
        glColor3f(1.0, 1.0, 1.5);
        glBegin(GL_TRIANGLES);
            glVertex3f(0.05f, -0.05f, 0.0f);
            glVertex3f(0.0f, 0.05f, 0.0f);
            glVertex3f(-0.05f, -0.05f, 0.0f);
        glEnd();
    glEndList();
}

static void reshapeScene(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}


static void animate()
{
    glutPostRedisplay();
}

static void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.0, 1.0, 0.0);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
        glVertex3d(-0.8,0.8,0);
        glVertex3d(0.8,0.8,0);
        glVertex3d(0.8,-0.8,0);
        glVertex3d(-0.8,-0.8,0);
    glEnd();

    glMatrixMode(GL_MODELVIEW);

    for(int i=0;i<NUM;++i){
        if (s[i].f==1){
            glLoadIdentity();
            glTranslated(s[i].x,s[i].y,0);
            glCallList(square);
            s[i].x+=s[i].Vx;
            s[i].y-=s[i].Vy;
            if (s[i].x*s[i].x>=0.6) s[i].Vx*=-1;
            if (s[i].y<=-0.7){
                s[i].y = 3;
                s[i].Vy = 0;
                s[i].Vx = 0;
            }
        }
    }

    for(int i=0;i<NUM;++i){
        if (c[i].f==1){
            glLoadIdentity();
            glTranslated(c[i].x,c[i].y,0);
            glCallList(circle);
            c[i].x+=c[i].Vx;
            c[i].y-=c[i].Vy;
            if (c[i].x*c[i].x>=0.6) c[i].Vx*=-1;
            if (c[i].y<=-0.7){
                c[i].y = 3;
                c[i].Vy = 0;
                c[i].Vx = 0;
            }
        }
    }

    for(int i=0;i<NUM;++i){
        if (t[i].f==1){
            glLoadIdentity();
            glTranslated(t[i].x,t[i].y,0);
            glCallList(triangle);
            t[i].x+=t[i].Vx;
            t[i].y-=t[i].Vy;
            if (t[i].x*t[i].x>=0.6) t[i].Vx*=-1;
            if (t[i].y<=-0.7){
                t[i].y = 3;
                t[i].Vy = 0;
                t[i].Vx = 0;
            }
        }
    }

    Sleep(100);
    glutSwapBuffers();
}



int main(int argc, char **argv) {
    for(int i=0;i<NUM;++i){
        c[i].f = 1;
        s[i].f = 1;
        t[i].f = 1;
        c[i].x = 1.2*float(rand())/RAND_MAX-0.6;
        s[i].x = 1.2*float(rand())/RAND_MAX-0.6;
        t[i].x = 1.2*float(rand())/RAND_MAX-0.6;
        c[i].y = 0.7;
        s[i].y = 0.7;
        t[i].y = 0.7;
        c[i].Vx = (float(rand())/RAND_MAX-1)/16;
        c[i].Vy = (float(rand())/RAND_MAX)/16;
        s[i].Vx = (float(rand())/RAND_MAX-1)/16;
        s[i].Vy = (float(rand())/RAND_MAX)/16;
        t[i].Vx = (float(rand())/RAND_MAX-1)/16;
        t[i].Vy = (float(rand())/RAND_MAX)/16;
    }


	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Figures rain");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshapeScene);
    glutIdleFunc(animate);
    BuildList();
	glutMainLoop();
	return 0;
}
