#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <cmath>
#include <iostream>
#include <vector>

#define WIDTH 600
#define HEIGHT 600

#define RADIUS 10   //Radio de la esfera
#define QUALITY 3  //Precisión de la aproximación
#define GRADES 10   //Grados que se rotan utilizando el ratón

/* Variables */
int grades;   //Variable para aumentar o disminuir la rotación
int quality;   //Variable para aumentar o disminuir la calidad

struct point{ //Estructura que guarda las coordenadas de un vértice
    float x;
    float y;
    float z;
};

point **spherePoints; //Matriz de vértices

/*Función que reserva la memoria de la matriz 
(cada vez que se usa F1 o F2 es necesario modificar el tamaño) */
void resizeMatrix(point **matrix){
    spherePoints = new point *[quality + 1];
    for(int i = 0; i< quality+1; i++){
        spherePoints[i] = new point[quality+1];
    }
}

/*Función que crea la esfera*/
void createSphere(int radius, int quality) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3i(1,1,1);

    float divStacks = M_PI / quality;
    float divSectors = 2*M_PI /quality;
    float angleStacks, angleSectors;
    float x, y, z;

    //Primero se guardan los vértices en la matriz
    for(int i = 0; i <= quality; i++){
        angleStacks =  M_PI/2 - i*divStacks;

        for(int j = 0; j <= quality; j++){
            angleSectors = j*divSectors;

            x = radius * cosf(angleStacks) * cos(angleSectors);
            y = radius * cosf(angleStacks) * sinf(angleSectors);
            z = radius * sinf(angleStacks);

            spherePoints[i][j].x = x;
            spherePoints[i][j].y = y;
            spherePoints[i][j].z = z;
        }
    }

    //Con los vértices se realiza la malla de triángulos
    glBegin(GL_TRIANGLE_STRIP);
    for(int i = 0; i < quality; i++){
        for(int j = 0; j <= quality; j++){
            point v1 = spherePoints[i][j];
            glVertex3f(v1.x, v1.y, v1.z);

            point v2 = spherePoints[i+1][j];
            glVertex3f(v2.x, v2.y, v2.z);

        }
    }
    glEnd();
    glFlush();
}

void display(void){
    glClearColor(1.0, 0.9, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);    

    //Enable movement
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3d(0.5, 0.8, 0.5);
    //glScalef(5.0, 5.0, 5.0);
    glRotatef(grades, 1, 1, 1);
    createSphere(RADIUS, quality);

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

void mouseClick(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        grades -= GRADES;
    } 
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        grades += GRADES;
    }
    else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN){
        grades = 0;
    }

    glutPostRedisplay();
}

void keysPressed(int key, int x, int y){
    switch(key){
        case GLUT_KEY_F1:{
            //Aumentar calidad si no supera 100
            if(quality <= 100)
                quality += 1;
                resizeMatrix(spherePoints);
            break;
        }

        case GLUT_KEY_F2:{
            //Disminuir calidad si su valor no es 3 o menos
            if(quality > 3)
                quality -= 1;
                resizeMatrix(spherePoints);
            break;
        }
    }

    glutPostRedisplay();
}

int main(int argc, char **argv){
    grades = 0;
    quality = QUALITY;

    //Reservar memoria
    resizeMatrix(spherePoints);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Sphere");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutSpecialFunc(keysPressed);

    glutMainLoop();
}