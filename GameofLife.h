#include <stdlib.h>

/**** Struct ***/
//Board struct
typedef struct tboard
{
    char *box;
    int width;
    int height;
} board;

board* createBoard(int w, int h)
{
    board *b = (board *)malloc(sizeof(board));
    if(!b)
        return NULL;

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

int checkNeighbors(board *b, int x, int y)
{
    int k,l;
    int count = 0;
    if(x >= b->width || y >= b->height || x < 0 || y < 0)
        return 0;

    for(k=-1; k <= 1; k++)
    for(l=-1; l <= 1; l++)
    {
        if(x+k >= 0 && x+k < b->width && y+l >= 0 && y+l < b->height && !(k == 0 && l == 0))
            if((b->box)[(x+k)+(y+l)*b->width] == 1)
                count++;
    }

    return count;
}

void generation(board* next, board* old)
{
    int i,j;

    int count;
    memcpy(old->box, next->box, (old->width*old->height)*sizeof(char));
//    for(i=0; i < old->width*old->height; i++)
//        (old->box)[i] = (next->box)[i];


    for(i=0; i < old->width; i++)
        for(j=0; j < old->height; j++)
        {
            count = checkNeighbors(old,i,j);
            if((old->box)[i+j*next->width] == 1 && (count < 2))
                (next->box)[i+j*next->width] = 0;
            else if((old->box)[i+j*next->width] == 1 && count > 3)
                (next->box)[i+j*next->width] = 0;
            else if((old->box)[i+j*next->width] == 1 && count <= 3)
                (next->box)[i+j*next->width] = 1;
            else if((old->box)[i+j*next->width] == 0 && count == 3)
                (next->box)[i+j*next->width] = 1;
        }
}
