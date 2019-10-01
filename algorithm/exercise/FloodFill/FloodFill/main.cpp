#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

const int COLUMN = 9;
const int ROW = 4;


struct pos {
    int x;
    int y;

};
struct pos mark[4][100];

void insert( struct pos *a,int x,int y)
{
    int i=0;
    while(a[i].x !=-1) {
        i++;
    }
    a[i].x =x;
    a[i].y = y;

}

char bitmap[][COLUMN] = {	{1,1,1,1,1,0,1,2,1},\
    {2,2,1,1,2,2,2,2,2},\
    {1,1,2,2,0,0,0,0,0},\
    {0,0,0,0,0,0,1,2,0}
};

char bit_mark[][COLUMN]= {{0}};


void set_color(int row,int column,char color)
{
    bitmap[row][column] = color;

}

bool flow_help(int row,int column,struct pos *a,char color)
{
    bit_mark[row][column] = 1;
    if( bitmap[row][column] == 0 )
        return false;
    insert(a,row,column);

    if(row-1>=0) {
        if( bit_mark[row-1][column] !=1 && bitmap[row-1][column] !=color) {
            if(flow_help(row-1,column,a,color) == false)
                return false;
        }
    }
    if(row+1<ROW) {
        if(bit_mark[row+1][column] !=1 && bitmap[row+1][column] !=color) {
            if(flow_help(row+1,column,a,color)==false)
                return false;
        }
    }

    if(column-1>=0) {
        if(bit_mark[row][column-1] !=1 && bitmap[row][column-1] !=color) {
            if( flow_help(row,column-1,a,color) == false)
                return false;
        }
    }

    if(column+1<COLUMN) {
        if(bit_mark[row][column+1] !=1 && bitmap[row][column+1] !=color) {
            if( flow_help(row,column+1,a,color) == false)
                return false;
        }
    }
    return true;

}

void flow_fill(int row,int column,char color)
{
    set_color(row,column,color);


    memset(mark,-1,sizeof(mark));
    if(row-1>=0 && bitmap[row-1][column]!=0 && bitmap[row-1][column] !=color) {
        if( flow_help(row-1,column,mark[0],color)) {
            for(int i=0; i<100; i++) {
                if(mark[0][i].x!=-1) {
                    printf("(%d,%d)", mark[0][i].x,mark[0][i].y);
                }
            }


        }
        printf("\n");

    }
    if(row+1<ROW &&bitmap[row+1][column]!=0 && bitmap[row+1][column] !=color) {
        if(flow_help(row+1,column,mark[1],color)) {
            for(int i=0; i<100; i++) {
                if(mark[1][i].x!=-1) {
                    printf("(%d,%d)", mark[1][i].x,mark[1][i].y);
                }
            }
        }
        printf("\n");
    }

    if(column-1>=0  &&bitmap[row][column-1]!=0 && bitmap[row][column-1] !=color) {
        if(flow_help(row,column-1,mark[2],color)) {
            for(int i=0; i<100; i++) {
                if(mark[2][i].x!=-1) {
                    printf("(%d,%d)", mark[2][i].x,mark[2][i].y);
                }
            }

        }
        printf("\n");
    }

    if(column+1<COLUMN &&bitmap[row][column+1]!=0 && bitmap[row][column+1] !=color) {
        if(flow_help(row,column+1,mark[3],color)) {
            for(int i=0; i<100; i++) {
                if(mark[3][i].x!=-1) {
                    printf("(%d,%d)", mark[3][i].x,mark[3][i].y);
                }
            }

        }
        printf("\n");
    }


}

int main()
{
    flow_fill(0,5,2);
    getch();
    return 0;
}