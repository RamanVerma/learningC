#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

int crosses = 0;
int plusses = 0;
int available_slots = 36;
struct slot{
    char c;
};
struct slot board[6][6];
int points[6][6];
int *neighbors;

void init_board(){
    int row, col = 0;
    for(row = 0; row < 6; row++){
        for(col = 0; col < 6; col++){
            board[row][col].c = ' ';
        }
    }
}
/*
* enumeration variable used to define direction
* of one slot wrt another slot
*/
enum compass{
    northwest = -7,
    north = -6,
    northeast = -5,
    west = -1,
    east = 1,
    southwest = 5,
    south = 6,
    southeast = 7
};
enum compass direction;
/*
* Draws the board in its current form
*/
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
* Convenience function to return the symbol for the 
* opposition player
*/
char other_player(char player){
    if(player == '+'){
        return 'x';
    }else{
        return '+';
    }
}
/*
* mark a slot on the board
* @player : player for whom to mark the slot
* @index : location of the slot 
*/
bool mark_slot(char player, int index){
    int row, col = 0;
    row = (index / 6);
    col = (index % 6);
    if(board[row][col].c == ' '){
        board[row][col].c = (player == '+') ? '+' : 'x';
        player == '+' ? plusses++ : crosses++;
        available_slots--;
        return true;
    }else{
        return false;
    }
}
/*
* Gets the direction from point A to point B
* Direction is relative to poistions of the slots on board
* Direction is an integer defined in an enum variable
* It is assumed that the board is a 6*6 square 
*/
int get_direction(int pointA, int point B){
    direction = (pointA == pointB + 7) ? northwest : (
        (pointA == pointB + 6) ? north : (
            (pointA == pointB + 5) ? northeast : (
                (pointA == pointB + 1) ? west : (
                    (pointA == pointB - 1) ? east : (
                        (pointA == pointB - 5) ? southwest : (
                            (pointA == pointB - 7) ? southeast : 0))))))
    return direction;
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
void find_neighbors(int * index){
    int row, col, count = 0;
    for(row = 0;row < 8; row++){
        *(neighbors + row) = 99;
    }
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
int best_possible_move(char player){
    int row, col, index, n, neighbor = 0;
    for(row = 0;row < 8;row++){
        for(col =0;col < 8;col++){
            points[row][col] = 0;
        }
    }
    for(row = 0;row < 8;row++){
        for(col =0;col < 8;col++){
            index = (row* 6) + col;
            n = 0;
            if(get_owner(index) == other_player(player)){
                find_neighbors(&index);
                while((neighbor = *(neighbors + n)) != 99){
                    
                    n++;
                }
            }
        }
    }
            index = (row * 6) + col;
            find_neighbors(&index);
}

void main(){
    init_board();
    neighbors = (int *)malloc(sizeof(int) * 8);
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
