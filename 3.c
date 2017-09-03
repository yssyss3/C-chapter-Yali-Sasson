#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <conio.h>

#define BOARD_WIDTH 30
#define BOARD_HEIGHT 20

#define EMPTY 32 /*space bar*/
#define FULL 79 /* 'O' */

void printBoard(char board[][BOARD_WIDTH]);
void makeBoard(char board[][BOARD_WIDTH], FILE* input);
void advance(char board[][BOARD_WIDTH]);
int isAlive(int x, int y, char board[][BOARD_WIDTH]);

int main(int argc, char** argv) {
    char board[BOARD_HEIGHT][BOARD_WIDTH] = {};
    FILE* input = NULL;
    char stop = 0;

    input = fopen(argv[1], "r");
    if(input == NULL){
        printf("invalid input file. \nusage: GOL <inputfile>\n");
        return 1;
    }

    makeBoard(board,input);

    while(stop != 's'){
        system("cls");
        printBoard(board);
        printf("\npress any key to advance. \npress s to stop\n");
        advance(board);
        stop = getch();
    }
    return 0;
}

void printBoard(char board[][BOARD_WIDTH]){
    int i, j;
    for(i = 0; i < BOARD_HEIGHT; i++){
        for(j = 0; j < BOARD_WIDTH; j++){
            if(board[i][j] == FULL) printf("%c",219);
            else printf(" ");
        }
        printf("\n");
    }
}

/*The fucntion will read which cells to activate from input file */
void makeBoard(char board[][BOARD_WIDTH], FILE* input){
    memset(board, EMPTY, sizeof(char)*(BOARD_WIDTH*BOARD_HEIGHT));
    char row[6];
    while(fgets(row, 7, input) != NULL) { /*scrolling through all rows in input file */
        char* x;
        char* y;
        row[5] = 0;

        /* getting the X and Y values of each cell in the input file.
         * the value's format in the input file is <x,y> */

        if((x = strtok(row,",")) == NULL){
            printf("Invalid input format!\n");
            exit(1);
        }

        if((y = strtok(NULL, ",")) == NULL){
            printf("Invalid input format!\n");
            exit(1);
        }
        board[atoi(y)][atoi(x)] = FULL;
    }
}

/*The function will check which cells should be alive next turn.
 * afterwards it will apply the changes to the board*/
void advance(char board[][BOARD_WIDTH]){
    char nextBoard[BOARD_HEIGHT][BOARD_WIDTH];
    int i,j;

    for(i = 0; i < BOARD_HEIGHT; i++){
        for(j = 0; j < BOARD_WIDTH; j++){
            if(isAlive(j,i,board)){
                nextBoard[i][j] = FULL;
            }
            else{
                nextBoard[i][j] = EMPTY;
            }
        }
    }
    /*copy nextBoard to board by value */
    for(i = 0; i < BOARD_HEIGHT; i++){
        for(j = 0; j < BOARD_WIDTH; j++){
            board[i][j] = nextBoard[i][j];
        }
    }
}

/*The function will check the number of neighbours for the provided
 * cell and determine if the cell will stay full for the next turn*/
int isAlive(int x, int y, char board[][BOARD_WIDTH]){
    int neighbours = 0;

    /*checking all possible neighbour locations around board[y][x] */
    if(y-1 >= 0 && x-1 >= 0 && board[y-1][x-1] == FULL) neighbours+=1;
    if(y-1 >= 0 && board[y-1][x] == FULL) neighbours+=1;
    if(y-1 >= 0 && x+1 < BOARD_WIDTH && board[y-1][x+1] == FULL) neighbours+=1;

    if(x-1 >= 0 && board[y][x-1] == FULL) neighbours+=1;
    if(x+1 < BOARD_WIDTH && board[y][x+1] == FULL) neighbours+=1;

    if(y+1 < BOARD_HEIGHT && x-1 >= 0 && board[y+1][x-1] == FULL) neighbours+=1;
    if(y+1 < BOARD_HEIGHT && board[y+1][x] == FULL) neighbours+=1;
    if(y+1 < BOARD_HEIGHT && x+1 < BOARD_WIDTH && board[y+1][x+1] == FULL)neighbours+=1;

    /*an empty cell with 3 neighbours will become full */
    if(board[y][x] == EMPTY && neighbours == 3) return 1;

    /*a full cell with two or three neighbours survives */
    if(board[y][x] == FULL && (neighbours == 2 || neighbours == 3)) return 1;

    return 0;
}
