#include <string.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include "../GameofLife.h"

/*** Constants ***/
#define WIDTH 400
#define HEIGHT 400
#define CELLSIZE 5
#define DTIME 1.0/10.0

/***Variables globales ***/
board* nuevo;
board* viejo;
clock_t new_t;
clock_t old_t;

/***Funciones***/
void init(void);
void idle(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void ExitAndClean(void);

/*** Main function ***/
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("Juego de la vida");


    init();

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}

void init() {
     int b_width = WIDTH/CELLSIZE;
     int b_height = HEIGHT/CELLSIZE;

    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,WIDTH,HEIGHT,0,-1,1);
    glMatrixMode(GL_MODELVIEW);

    nuevo = createBoard(b_width,b_height);

//    //Blinker
//    (nuevo->box)[10+1*b_width] = 1;
//    (nuevo->box)[10+2*b_width] = 1;
//    (nuevo->box)[10+3*b_width] = 1;

//    (nuevo->box)[10+20*b_width] = 1;
//    (nuevo->box)[11+20*b_width] = 1;
//    (nuevo->box)[12+20*b_width] = 1;

//    //Toad
//    (nuevo->box)[30+30*b_width] = 1;
//    (nuevo->box)[31+30*b_width] = 1;
//    (nuevo->box)[32+30*b_width] = 1;
//    (nuevo->box)[29+31*b_width] = 1;
//    (nuevo->box)[30+31*b_width] = 1;
//    (nuevo->box)[31+31*b_width] = 1;

//    //Block
//    (nuevo->box)[1+1*b_width] = 1;
//    (nuevo->box)[1+2*b_width] = 1;
//    (nuevo->box)[2+1*b_width] = 1;
//    (nuevo->box)[2+2*b_width] = 1;

    //Glider
//    (nuevo->box)[30+20*b_width] = 1;
//    (nuevo->box)[31+20*b_width] = 1;
//    (nuevo->box)[32+20*b_width] = 1;
//    (nuevo->box)[30+21*b_width] = 1;
//    (nuevo->box)[31+22*b_width] = 1;

    //Gosper glider gun
    (nuevo->box)[1+5*b_width] = 1;
    (nuevo->box)[2+5*b_width] = 1;
    (nuevo->box)[1+6*b_width] = 1;
    (nuevo->box)[2+6*b_width] = 1;

    (nuevo->box)[35+3*b_width] = 1;
    (nuevo->box)[36+3*b_width] = 1;
    (nuevo->box)[35+4*b_width] = 1;
    (nuevo->box)[36+4*b_width] = 1;

    (nuevo->box)[13+3*b_width] = 1;
    (nuevo->box)[14+3*b_width] = 1;
    (nuevo->box)[12+4*b_width] = 1;
    (nuevo->box)[16+4*b_width] = 1;
    (nuevo->box)[11+5*b_width] = 1;
    (nuevo->box)[17+5*b_width] = 1;
    (nuevo->box)[11+6*b_width] = 1;
    (nuevo->box)[15+6*b_width] = 1;
    (nuevo->box)[17+6*b_width] = 1;
    (nuevo->box)[18+6*b_width] = 1;
    (nuevo->box)[11+7*b_width] = 1;
    (nuevo->box)[17+7*b_width] = 1;
    (nuevo->box)[12+8*b_width] = 1;
    (nuevo->box)[16+8*b_width] = 1;
    (nuevo->box)[13+9*b_width] = 1;
    (nuevo->box)[14+9*b_width] = 1;

    (nuevo->box)[21+3*b_width] = 1;
    (nuevo->box)[22+3*b_width] = 1;
    (nuevo->box)[21+4*b_width] = 1;
    (nuevo->box)[22+4*b_width] = 1;
    (nuevo->box)[21+5*b_width] = 1;
    (nuevo->box)[22+5*b_width] = 1;
    (nuevo->box)[23+2*b_width] = 1;
    (nuevo->box)[23+6*b_width] = 1;
    (nuevo->box)[25+2*b_width] = 1;
    (nuevo->box)[25+6*b_width] = 1;
    (nuevo->box)[25+1*b_width] = 1;
    (nuevo->box)[25+7*b_width] = 1;

    viejo = createBoard(b_width,b_height);

    old_t = clock();
}

void idle() {
    new_t = clock();

    double elapsed = ((double)(new_t - old_t))/CLOCKS_PER_SEC;

    if(elapsed > DTIME)
    {
        generation(nuevo,viejo);
        old_t = new_t;
    }
}

void display() {
    int i,j;
    int Y,X;


    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    for(i=0; i < nuevo->width; i++)
        for(j=0; j < nuevo->height; j++)
        {
            X = i*CELLSIZE;
            Y = j*CELLSIZE;

            if((nuevo->box)[i+j*nuevo->width] == 1)
            {
                glBegin(GL_QUADS);
                glColor3f(1.0,1.0,1.0);
                glVertex2d(X,Y);
                glVertex2d(X+CELLSIZE,Y);
                glVertex2d(X+CELLSIZE,Y+CELLSIZE);
                glVertex2d(X,Y+CELLSIZE);
                glEnd();
            }
        }

    glutSwapBuffers();
    glFlush();

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
    case 27:
        ExitAndClean();
        break;
    }
}

void ExitAndClean() {
    free(nuevo->box);
    free(viejo->box);

    free(nuevo);
    free(viejo);

    exit(0);
}
