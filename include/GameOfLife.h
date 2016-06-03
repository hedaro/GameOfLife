#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <stdlib.h>
#include <string.h>

/**** Struct ***/
//Board struct
typedef struct board {
    char *box;
    int width;
    int height;
} board;

board* createBoard(int w, int h) {
    if (w <= 0 || h <= 0) {
        return NULL;
    }

    board *b = (board *)malloc(sizeof(board));
    if(!b) {
        return NULL;
    }

    b->box = (char*)calloc(w*h,sizeof(char));

    if(!(b->box))
    {
        free(b);
        return NULL;
    }

    b->width=w;
    b->height=h;

    return b;
}

int checkNeighbors(board *b, int x, int y) {
    int k,l;
    int count = 0;
    if(x >= b->width || y >= b->height || x < 0 || y < 0)
        return 0;

    for(k=-1; k <= 1; k++) {
        for(l=-1; l <= 1; l++) {
            if(x+k >= 0 && x+k < b->width && y+l >= 0 && y+l < b->height && !(k == 0 && l == 0)) {
                if((b->box)[(x+k)+(y+l)*b->width] == 1) {
                    count++;
                }
            }
        }
    }

    return count;
}

void generation(board* current, board* next) {
    int i,j;

    int count;
    memcpy(next->box, current->box, (current->width*current->height)*sizeof(char));
//    for(i=0; i < current->width*current->height; i++)
//        (next->box)[i] = (current->box)[i];


    for(i=0; i < next->width; i++) {
        for(j=0; j < next->height; j++)
        {
            count = checkNeighbors(next,i,j);
            if((next->box)[i+j*next->width] == 1 && count < 2)
                (current->box)[i+j*next->width] = 0;
            else if((next->box)[i+j*next->width] == 1 && count > 3)
                (current->box)[i+j*next->width] = 0;
            else if((next->box)[i+j*next->width] == 1 && count <= 3)
                (current->box)[i+j*next->width] = 1;
            else if((next->box)[i+j*next->width] == 0 && count == 3)
                (current->box)[i+j*next->width] = 1;
            // If cell is alive and neighbors equals 2 or 3 it stays alive
            // If cell is dead and neighbors is not equal to 3 it stays dead
        }
    }
}
#endif /* GAMEOFLIFE_H */