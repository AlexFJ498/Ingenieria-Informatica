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


/* Variables */
float holeRadius = 1.75; //Radio de los agujeros

/**
 * Función que crea un círculo haciendo uso del abanico de triángulos.
 * Se usa para crear los agujeros, generar el topo y crear las tres vidas.
 */
void createCircle(float radius, float numTriangulos) {
    glBegin(GL_TRIANGLE_FAN);
        //Primer triángulo
        glVertex2f(0, 0);

        for(int i = 0; i<= numTriangulos; i++){
            glVertex2d(
                radius * cos(i * 2*M_PI / numTriangulos),
                radius * sin(i * 2*M_PI / numTriangulos)
            );
        }
    glEnd();
}

/**
 * Función que crea un agujero en las coordenadas indicadas, 
 * creando primero el borde rojo para luego hacer el círculo negro.
 */
void createHole(float radius, float x, float y, float z){
    glLoadIdentity();
    glTranslatef(x, y, z);

    glColor3d(0.8, 0.0, 0.0);
    createCircle(radius, 8);

    glColor3f(0, 0, 0);
    createCircle(radius - 0.5, 20);
}

/**
 * Función que crea los puntos de vida. El color rojo representa
 * una vida perdida.
 */
void createLives(){
    glLoadIdentity();

    glColor3f(1.0, 0.0, 0.0); //Una vida perdida

    glTranslatef(2, 7, 0);
    createCircle(1, 30);

    glColor3f(0.0, 0.7, 0.0);

    glTranslatef(2.5, 0, 0);
    createCircle(1, 30);

    glTranslatef(2.5, 0, 0);
    createCircle(1, 30);
}

/**
 * Función que crea la barra de puntos
 */
void createPoints(){
    glLoadIdentity();

    glColor3f(1, 1, 1);

    //Rectángulo blanco
    glBegin(GL_QUADS);
        glVertex3f(-9.5, 8, 0);
        glVertex3f(-9.5, 6, 0);
        glVertex3f(-1, 6, 0);
        glVertex3f(-1, 8, 0);
    glEnd();

    glColor3f(0, 0, 0);

    //Puntos
    std::string str = "Points: 0";
    glRasterPos3d(-9, 6.7, 0);
    for(int i=0; i<str.size(); i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    }
}

/**
 * Función que coloca arriba de la pantalla el nivel de juego.
 */
void createLevel(){
    glLoadIdentity();

    glColor3f(0, 0, 0);

    std::string str = "Nivel 1";
    glRasterPos3d(-1, 9, 0);
    for(int i=0; i<str.size(); i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
    }
}

/**
 * Función que crea la barra superior de la pantalla y llama
 * a todas las funciones que colocan los respectivos elementos.
 */
void createBar(){
    glLoadIdentity();
    glColor3f(0.0, 0.3, 0.5);
    glBegin(GL_QUADS);
        glVertex3f(-10, 10, 0);
        glVertex3f(-10, 5, 0);
        glVertex3f(10, 5, 0);
        glVertex3f(10, 10, 0);
    glEnd();

    //Crear las vidas
    createLives();

    //Crear puntuación
    createPoints();

    //Crear nivel
    createLevel();
}

/**
 * Función que genera un topo en las coordenadas indicadas.
 */
void createMole(float radius, float x, float y, float z){
    glLoadIdentity();
    glTranslatef(x, y, z);

    glColor3f(139/255.0, 69/255.0, 19/255.0);
    createCircle(radius - 0.5, 20);

    //Dientes
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
        glVertex3f(-0.3, 0, 0);
        glVertex3f(-0.2, -0.5, 0);
        glVertex3f(0.2, -0.5, 0);
        glVertex3f(0.3, 0, 0);
    glEnd();

    //Cejas y separación de dientes
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, -0.5, 0);

        glVertex3f(-0.5, 0.7, 0);
        glVertex3f(-0.1, 0.5, 0);

        glVertex3f(0.5, 0.7, 0);
        glVertex3f(0.1, 0.5, 0);
    glEnd();

    //Ojos
    glTranslatef(-0.25, 0.3, 0);
    createCircle(0.1, 10);

    glTranslatef(0.5, 0, 0);
    createCircle(0.1, 10);
}

void display(void){
    glClearColor(0.6, 1.0, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);    

    //Enable movement
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Crear agujeros
    createHole(holeRadius, -5.0, 0, 0);
    createHole(holeRadius, 0.0, 0, 0);
    createHole(holeRadius, 5.0, 0, 0);
    createHole(holeRadius, -2.5, -5, 0);
    createHole(holeRadius, 2.5, -5, 0);

    //Posicionar topo
    createMole(holeRadius, 0.0, 0, 0);

    //Crear barra de arriba con todos los elementos
    createBar();

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
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Whac-A-Mole");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    glutMainLoop();
}