#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <cmath>

#define XMIN -10
#define XMAX 10
#define Z -1
#define SPEED 0.1
#define TAM 10

/* Variables */
float x;
float y;
float z;

float xMin;
float xMax;

float speed;
float tam;

/**
 * Method to control movement
 */
void moveObject(void){

    //Calculate new coordinates for next time instant
        if(x < xMax ){
            x = x + speed;
            y = pow(x, z);
        } else{
            x = xMin;
            y = pow(x, z);
        }

    //Redisplay objects
	glutPostRedisplay();
};

void display(void){
    glClearColor(0.2, 0.3, 0.7, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);    

    //Enable movement
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    //Crear ejes
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex3i(-20, 0, 0);
    glVertex3i(20, 0, 0);
    glVertex3i(0, -20, 0);
    glVertex3i(0, 20, 0);
    glEnd();

    //Crear círculo
    glPointSize(tam);
    glColor3ub(1, 1, 1);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();

	//Swap buffers
	glutSwapBuffers();
}

static void reshape(int w, int h){
	glViewport(0, 0, w, h);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    //Tamaño de 10x10
    glOrtho(-10, 10, -10, 10, -10.0, 10.0);

    glFlush();
}


int main(int argc, char **argv){
    //Inicializar valores del rango y el valor de z
	xMin = XMIN;
    xMax = XMAX;
    z = Z;

    //Inicializar posición de la esfera
    x = xMin;
    y = pow(x, abs(z));

    //Inicializar velocidad y tamaño del punto
    speed = SPEED;
    tam = TAM;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("Practica 7");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(moveObject);

    glutMainLoop();
}