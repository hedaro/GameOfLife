#include <string.h>
#include <time.h>
#include <SDL/SDL.h>
#include "../GameofLife.h"

/*** Constants ***/
#define WIDTH 400
#define HEIGHT 400
#define CELLSIZE 5
#define DTIME 1.0/10.0

//Global variables
SDL_Surface* screen = NULL;
int running = 1;
int lastTime = 0;
int newTime = 0;
double deltaTime = 0.0;

board* nuevo = NULL;
board* viejo = NULL;

//Game Functiones
void init();
void shutdown();
void handleInput();
void updateGame();
void draw(SDL_Surface* screen,board* b);


//Main function
int main(int arg, char** argv) {

    init();

    while(running == 1) {
        newTime = SDL_GetTicks();
        deltaTime = (double) (newTime - lastTime) / 1000;
        if(deltaTime >= DTIME)
            {
                generation(nuevo,viejo);
                lastTime = newTime;
            }

        handleInput();

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0,0,0));

        draw(screen,nuevo);

        SDL_Flip(screen);
    }

    shutdown();

    return 0;
}

void init() {
    int b_width = WIDTH/CELLSIZE;
    int b_height = HEIGHT/CELLSIZE;

    SDL_Init(SDL_INIT_VIDEO);

    screen = SDL_SetVideoMode(WIDTH,HEIGHT,0,SDL_HWSURFACE|SDL_DOUBLEBUF);
    if(!screen)
        exit(1);

    SDL_WM_SetCaption("Conway's Game of Life",0);

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

}

void shutdown() {
    if(nuevo) {
        if(nuevo->box)
            free(nuevo->box);
        free(nuevo);
    }
    if(nuevo) {
        if(nuevo->box)
            free(viejo->box);
        free(viejo);
    }

    SDL_Quit();
}

void handleInput() {
    SDL_Event event;
    if(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT)
            running = 0;
        if(event.type == SDL_KEYDOWN)
            if(event.key.keysym.sym == SDLK_ESCAPE)
                running = 0;
    }
}

void draw(SDL_Surface *screen, board *b) {
    int i,j;
    int Y,X;

    for(i=0; i < b->width; i++)
        for(j=0; j < b->height; j++)
        {
            X = i*CELLSIZE;
            Y = j*CELLSIZE;

            if((b->box)[i+j*b->width] == 1)
            {
                SDL_Rect square = {X,Y,CELLSIZE,CELLSIZE};
                SDL_FillRect(screen, &square, SDL_MapRGB(screen->format,255,255,255));
            }
        }
}
