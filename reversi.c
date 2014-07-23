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
int max_slot;
int max_points;

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

/*
* Draws the board in its current form
*/
void draw_board(){
    int row, col = 0;
    for(row = 0; row < 6; row++){
        for(col = 0; col < 6; col++){
            printf(" %c |", board[row][col].c);
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
int get_direction(int pointA, int pointB){
    enum compass direction;
    direction = (pointA == pointB + 7) ? northwest : (
        (pointA == pointB + 6) ? north : (
            (pointA == pointB + 5) ? northeast : (
                (pointA == pointB + 1) ? west : (
                    (pointA == pointB - 1) ? east : (
                        (pointA == pointB - 5) ? southwest : (
                            (pointA == pointB - 6) ? south : (
                                (pointA == pointB - 7) ? southeast : 0)))))));
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
* index: the position of the slot
* c: kind of neighbor to be searched
*/
void find_neighbors(int * index, char c){
    int row, col, count = 0;
    /*
    * Initialize the neigbors array to a big value
    */
    for(row = 0;row < 8; row++){
        *(neighbors + row) = 99;
    }
    /*
    * Get the board coordinates corresponding to the position
    */
    row = (*index / 6);
    col = (*index % 6);
    /*check north west*/
    if((row - 1) >= 0 && (col - 1) >= 0 && (get_owner(((row - 1) * 6) + (col - 1)) == c)){
        *neighbors++ = ((row - 1) * 6) + (col - 1);
        count++;
    }
    /*check north*/
    if((row - 1) >= 0 && (get_owner(((row - 1) * 6) + (col)) == c)){
        *neighbors++ = ((row - 1) * 6) + (col);
        count++;
    }
    /*check north east*/
    if((row - 1) >= 0 && (col + 1) < 6 && (get_owner(((row - 1) * 6) + (col + 1)) == c)){
        *neighbors++ = ((row - 1) * 6) + (col + 1);
        count++;
    }
    /*check west*/
    if((col - 1) >= 0 && (get_owner(((row) * 6) + (col - 1)) == c)){
        *neighbors++ = ((row) * 6) + (col - 1);
        count++;
    }
    /*check east*/
    if((col + 1) < 6 && (get_owner(((row) * 6) + (col + 1)) == c)){
        *neighbors++ = ((row) * 6) + (col + 1);
        count++;
    }
    /*check south west*/
    if((row + 1) < 6 && (col - 1) >= 0 && (get_owner(((row + 1) * 6) + (col - 1)) == c)){
        *neighbors++ = ((row + 1) * 6) + (col - 1);
        count++;
    }
    /*check south*/
    if((row + 1) < 6 && (get_owner(((row + 1) * 6) + (col)) == c)){
        *neighbors++ = ((row + 1) * 6) + (col);
        count++;
    }
    /*check south east*/
    if((row + 1) < 6 && (col + 1) < 6 && (get_owner(((row + 1) * 6) + (col + 1)) == c)){
        *neighbors++ = ((row + 1) * 6) + (col + 1);
        count++;
    }
    /*bring neighbors pointer to the first element of the dynamically allocated array*/
    neighbors = neighbors - count;
}
/*
*
*/

/*
* Best possible move for player(passed on as argument)
*/
int best_possible_move(char player){
    int row, col, index, n, neighbori, n_row, n_col = 0;
    /*
    * Create a matrix to store the possible points at every slot on the board
    */
    for(row = 0;row < 6;row++){
        for(col =0;col < 6;col++){
            points[row][col] = -1;
        }
    }
    max_slot = 0;
    max_points = 0;
    /*
    * Iterate through every slot on the board
    */
    for(row = 0;row < 6;row++){
        for(col = 0;col < 6;col++){
            /*
            * If the owner of any slot is the opposite player, get all his vacant
            * neighboring slots.
            */
            index = (row * 6) + col;
            if(get_owner(index) == other_player(player)){
                /*
                * Find the vacant neighboring slots
                */
                find_neighbors(&index, ' ');
                /*
                * Calculate the possible points to be won if a vacant neighboring
                * slot is occupied.
                */
                for(n = 0;(neighbor = *(neighbors + n)) != 99;n++){

//Refactor the code from here
//int points(int pointA, int pointB, char player)
                    /*
                    * Get direction from this neighbor to the index
                    */
                    int direction = 0;
                    direction = get_direction(neighbor, index);
                    /*
                    * Calculate how far can we step in this direction.
                    */
                    int steps = 1;
                    while((neighbor + (direction * steps)) < 36 &&
                        (neighbor + (direction * steps)) >= 0 && 
                        get_owner(neighbor + (direction * steps)) == other_player(player)){
                        steps++;
                    }
                    /*
                    * There should be a valid slot adjacent to the last step, and it must be
                    * occupied by the player(passed as argument)
                    */
                    n_row = neighbor / 6;
                    n_col = neighbor % 6;
                    if((neighbor + (direction * (steps + 1))) < 36 &&
                        (neighbor + (direction * (steps + 1))) >= 0 &&
                        get_owner(neighbor + (direction * (steps + 1))) == player){
                        points[n_row][n_col] = (points[n_row][n_col] < steps) ? steps : points[n_row][n_col];
                    }

//Take this much code in another function

                    /*
                    * Check if the just concluded slot can earn the max possible points
                    */
                    if(points[n_row][n_col] > max_points){
                        max_points = points[n_row][n_col];
                        max_slot = neighbor;
                    }
                }
            }
        }
    }
    return max_slot;
}

void main(){
    int move, computers_points = 0;
    char usersign;
    init_board();
    neighbors = (int *)malloc(sizeof(int) * 8);
    if(neighbors == NULL){
        printf("Short on memory");
        return;
    }
    draw_board();
    /*
    * User has to select a sign for himself / herself. Computer will get the opposite sign.
    */
    while(1){
        scanf("Select your sign. The only valid values are plus(+) or cross(x)", &usersign);
        if(usersign == '+' || usersign == 'x')
            break;
    }
    /*
    * Main loop for the game.
    */
    while(){
        /*
        * Get the human's next move
        */
        scanf("What is your next move. [0..35]", &move);
        if(move < 0 || move > 35 || get_owner(move) != ' '){
            /*
            * Invalid move. Input again
            */
            printf("Wrong move. Provide a valid value on the board.");
            continue;
        }else{
            /*
            * Valid move. 
            * Mark the slot for human user and caclculate his points.
            * Draw the board.
            */
            mark_slot(usersign, move);
            draw_board();
            /*
            * Get the best possible move for computer.
            * Mark the slot and calculate computer's points.
            * Draw the board.
            */
            computers_move = best_possible_move(other_player(usersign));
            mark_slot(other_player(usersign), computers_move);
            computers_points += max_points;
            draw_board();
        }
    }
}
