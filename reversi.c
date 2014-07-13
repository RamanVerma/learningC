#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

int crosses = 0;
int plusses = 0;
int available_slots = 36;
struct slot{
    char c;
};
struct slot board[6][6];
int *neighbors;

void init_board(){
    int row, col = 0;
    for(row = 0; row < 6; row++){
        for(col = 0; col < 6; col++){
            board[row][col].c = ' ';
        }
    }
}

void draw_board(){
    int row, col = 0;
    for(row = 0; row < 6; row++){
        for(col = 0; col < 6; col++){
//            printf(" %c |", board[row][col].c);
            printf(" %d |", (row * 6)+ col);
        }
        printf("\n------------------------\n");
    }
}

/*
* mark a slot on the board
* @player : player for whom to mark the slot
* @index : location of the slot 
*/
bool mark_slot(int player, int index){
    int row, col = 0;
    row = (index / 6);
    col = (index % 6);
    if(board[row][col].c == ' '){
        board[row][col].c = (player == 1) ? '+' : 'x';
        player == 1 ? plusses++ : crosses++;
        available_slots--;
        return true;
    }else{
        return false;
    }
}
/*
* Gets the owner of a slot
*/
char get_owner(int index){
    int row, col = 0;
    row = (index / 6);
    col = (index % 6);
    return board[row][col].c;
}
/*
* Finds the neighbors to a slot
*/
void find_neighbors(int * index, char player){
    int row, col, count = 0;
    memset(neighbors, 99, 8);
    row = (*index / 6);
    col = (*index % 6);
    if((row - 1) >= 0 && (col - 1) >= 0 && (get_owner(((row - 1) * 6) + (col - 1)) == ' ')){
        *neighbors++ = ((row - 1) * 6) + (col - 1);
        count++;
    }
    if((row - 1) >= 0 && (get_owner(((row - 1) * 6) + (col)) == ' ')){
        *neighbors++ = ((row - 1) * 6) + (col);
        count++;
    }
    if((row - 1) >= 0 && (col + 1) < 6 && (get_owner(((row - 1) * 6) + (col + 1)) == ' ')){
        *neighbors++ = ((row - 1) * 6) + (col + 1);
        count++;
    }
    if((col - 1) >= 0 && (get_owner(((row) * 6) + (col - 1)) == ' ')){
        *neighbors++ = ((row) * 6) + (col - 1);
        count++;
    }
    if((col + 1) < 6 && (get_owner(((row) * 6) + (col + 1)) == ' ')){
        *neighbors++ = ((row) * 6) + (col + 1);
        count++;
    }
    if((row + 1) < 6 && (col - 1) >= 0 && (get_owner(((row + 1) * 6) + (col - 1)) == ' ')){
        *neighbors++ = ((row + 1) * 6) + (col - 1);
        count++;
    }
    if((row + 1) < 6 && (get_owner(((row + 1) * 6) + (col)) == ' ')){
        *neighbors++ = ((row + 1) * 6) + (col);
        count++;
    }
    if((row + 1) < 6 && (col + 1) < 6 && (get_owner(((row + 1) * 6) + (col + 1)) == ' ')){
        *neighbors++ = ((row + 1) * 6) + (col + 1);
        count++;
    }
    neighbors = neighbors - count;
}
/*
* Best possible move for player(passed on as argument)
*/
int best_possible_move(int player){

}

void main(){
    init_board();
    neighbors = malloc(sizeof(int) * 8);
    draw_board();
    
    int index, row, col = 0;
    for(row = 0; row < 6; row++){
        for(col = 0; col < 6; col++){
            index = (row * 6) + col;
            find_neighbors(&index, '+');
            printf("\n%d : %d, %d, %d, %d, %d, %d, %d, %d", index, *neighbors, *(neighbors+1), *(neighbors+2), *(neighbors+3), *(neighbors+4), *(neighbors+5), *(neighbors+6), *(neighbors+7));
        }
    }
}
