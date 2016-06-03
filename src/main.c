#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/GameOfLife.h"

/*** Constants ***/
#define WIDTH 400
#define HEIGHT 400
#define CELLSIZE 5
#define DTIME 1.0/10.0

/***Global variables ***/
board* next = NULL;
board* current = NULL;
int lastTime = 0;
int newTime = 0;
double deltaTime = 0.0;

//Game Functions
void init();
void shutdown();
void display();

int main(int argc, char** argv) {
    SDL_Window *window;
    SDL_GLContext glcontext;
    SDL_Event e;

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        fprintf(stderr, "\nUnable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        "Conway's Game of life",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_OPENGL
    );

    if (window == NULL) {
        fprintf(stderr, "\nCould not create widnow: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    glcontext = SDL_GL_CreateContext(window);

    init();

    while(e.type != SDL_QUIT) {
        SDL_PollEvent(&e);

        newTime = SDL_GetTicks();
        deltaTime = (double) (newTime - lastTime) / 1000;
        if(deltaTime >= DTIME) {
            generation(current,next);
            lastTime = newTime;
        }

        display();
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glcontext);

    SDL_DestroyWindow(window);

    SDL_Quit();
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

    current = createBoard(b_width,b_height);

    //    //Blinker
    //    (current->box)[10+1*b_width] = 1;
    //    (current->box)[10+2*b_width] = 1;
    //    (current->box)[10+3*b_width] = 1;

    //    (current->box)[10+20*b_width] = 1;
    //    (current->box)[11+20*b_width] = 1;
    //    (current->box)[12+20*b_width] = 1;

    //    //Toad
    //    (current->box)[30+30*b_width] = 1;
    //    (current->box)[31+30*b_width] = 1;
    //    (current->box)[32+30*b_width] = 1;
    //    (current->box)[29+31*b_width] = 1;
    //    (current->box)[30+31*b_width] = 1;
    //    (current->box)[31+31*b_width] = 1;

    //    //Block
    //    (current->box)[1+1*b_width] = 1;
    //    (current->box)[1+2*b_width] = 1;
    //    (current->box)[2+1*b_width] = 1;
    //    (current->box)[2+2*b_width] = 1;

        //Glider
    //    (current->box)[30+20*b_width] = 1;
    //    (current->box)[31+20*b_width] = 1;
    //    (current->box)[32+20*b_width] = 1;
    //    (current->box)[30+21*b_width] = 1;
    //    (current->box)[31+22*b_width] = 1;

    //Gosper glider gun
    (current->box)[1+5*b_width] = 1;
    (current->box)[2+5*b_width] = 1;
    (current->box)[1+6*b_width] = 1;
    (current->box)[2+6*b_width] = 1;

    (current->box)[35+3*b_width] = 1;
    (current->box)[36+3*b_width] = 1;
    (current->box)[35+4*b_width] = 1;
    (current->box)[36+4*b_width] = 1;

    (current->box)[13+3*b_width] = 1;
    (current->box)[14+3*b_width] = 1;
    (current->box)[12+4*b_width] = 1;
    (current->box)[16+4*b_width] = 1;
    (current->box)[11+5*b_width] = 1;
    (current->box)[17+5*b_width] = 1;
    (current->box)[11+6*b_width] = 1;
    (current->box)[15+6*b_width] = 1;
    (current->box)[17+6*b_width] = 1;
    (current->box)[18+6*b_width] = 1;
    (current->box)[11+7*b_width] = 1;
    (current->box)[17+7*b_width] = 1;
    (current->box)[12+8*b_width] = 1;
    (current->box)[16+8*b_width] = 1;
    (current->box)[13+9*b_width] = 1;
    (current->box)[14+9*b_width] = 1;

    (current->box)[21+3*b_width] = 1;
    (current->box)[22+3*b_width] = 1;
    (current->box)[21+4*b_width] = 1;
    (current->box)[22+4*b_width] = 1;
    (current->box)[21+5*b_width] = 1;
    (current->box)[22+5*b_width] = 1;
    (current->box)[23+2*b_width] = 1;
    (current->box)[23+6*b_width] = 1;
    (current->box)[25+2*b_width] = 1;
    (current->box)[25+6*b_width] = 1;
    (current->box)[25+1*b_width] = 1;
    (current->box)[25+7*b_width] = 1;

    next = createBoard(b_width,b_height);
}

void display() {
    int i,j;
    int Y,X;

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    for(i=0; i < current->width; i++) {
        for(j=0; j < current->height; j++)
        {
            X = i*CELLSIZE;
            Y = j*CELLSIZE;

            if((current->box)[i+j*current->width] == 1)
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
    }
}

void shutdown() {
}