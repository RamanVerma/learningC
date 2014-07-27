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
/*
* This structure is used to convert slot owners
*/
struct convert{
    int points; /*number of slots to be converted*/
    int direction;  /*direction in which to move*/
    int flip_start; /*start position of the conversion*/
    int flip_end;   /*end position of the conversion*/
    char player;   /*convert the ownership to this player*/
};
struct convert max;
/*
* initialize the board by clearing all the slots
* Parameters:
* None
*/
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
* Parameters:
* None
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
* Parameter:
* char player: player in question
*/
char other_player(char player){
    if(player == '+'){
        return 'x';
    }else{
        return '+';
    }
}
/*
* mark an empty slot on the board
* Parameters:
* char player : player for whom to mark the slot
* int index : location of the slot 
* bool force : mark the slot, even hen it is not empty
*/
bool mark_slot(char player, int index, bool force){
    int row, col = 0;
    /*Convert the integer poisiton on the board to matrix co ordinates*/
    row = (index / 6);
    col = (index % 6);
    /*Mark the empty slot*/
    if((!force && board[row][col].c == ' ') || force){
        board[row][col].c = player;
        /*add to the count of corresponding player*/ 
        player == '+' ? plusses++ : crosses++;
        /*Reduce the count on empty slots*/
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
* Parameters:
* int pointA: source index on the board
* int pointB: destination index on the board
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
* Parameters:
* int index: position of the slot
*/
char get_owner(int index){
    int row, col = 0;
    row = (index / 6);
    col = (index % 6);
    return board[row][col].c;
}
/*
* Finds the neighbors to a slot
* Parameters:
* index: the position of the slot
* char c: kind of neighbor/player to be searched
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
* Get the maximum number of points/moves for a player when treading
* from pointA to pointB
* Parameters: 
* int pointA: starting index position
* int pointB: starting index position
* int direction: direction from pointA to pointB
* char player: player in question
*/
int max_moves(int pointA, int pointB, int direction, char player){
    /*
    * Calculate how far can we step in this direction.
    */
    int steps = 1;
    while((pointA + (direction * steps)) < 36 &&
        (pointA + (direction * steps)) >= 0 && 
        get_owner(pointA + (direction * steps)) == other_player(player)){
        steps++;
    }
    return steps - 1;
}
/*
* Best possible move for player
* Argument: 
* char player: player in question
*/
int best_possible_move(char player){
    int row, col, index, direction, n, neighbor, n_row, n_col, steps = 0;
    /*
    * Create a matrix to store the possible points at every slot on the board
    */
    for(row = 0;row < 6;row++){
        for(col =0;col < 6;col++){
            points[row][col] = -1;
        }
    }
    max.flip_start = -1;
    max.flip_end = -1;
    max.direction = 0;
    max.points = -1;
    max.player = player;
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
                    /*
                    * Get direction from pointA to pointB
                    */
                    direction = get_direction(neighbor, index);
                    steps = 0;
                    steps = max_moves(neighbor, index, direction, player);
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
                    /*
                    * Check if the just concluded slot can earn the max possible points
                    */
                    printf("processing neighbor: %d to slot: %d\n", neighbor, index);
                    printf("Before checking for the points at this slot: %d\n", points[n_row][n_col]);
                    if(points[n_row][n_col] > max.points){
                        max.points = points[n_row][n_col];
                        max.direction = direction;
                        max.flip_start = neighbor;
                        max.flip_end = index;
                    }
                    printf("After checking for the points at this slot: %d\n", points[n_row][n_col]);
                }
            }
        }
    }
   printf("points to be gained: %d\n", max.points);
   printf("slot to be marked: %d\n", max.flip_start);
    if(max.flip_start == -1){
        while(1){
            int x = rand() % 36;
            if(get_owner(x) == ' '){
                max.points = 0;
                max.direction = 0;
                max.flip_start = x;
                max.flip_end = x;
                break;
            }
        };
    }
    return max.flip_start;
}
/*
* flips the ownership for a range of slots 
* defined by the variable of type convert
* Parameters:
* struct convert param: structure that defines the range to be converted
*/
void flip(struct convert param){
    /*
    * This is the case when we don't have anything to flip
    */
    if(param.direction == 0)
        return;
    int x = 1;
    for(;x <= param.points; x++){
        mark_slot(param.player, max.flip_start + (max.direction * x), true);
    }
}
/*
* main function
* TODO: flip for human user
* TODO: scoring
* FIXME: the game ended without all slots having been filled
* FIXME: scanf is bad idea to get user input. Some times it gets in infinite loop at 
* when user gives an invalid move
*/
void main(){
    int move, computers_points, computers_move, slots_filled = 0;
    char usersign;
    init_board();
    neighbors = (int *)malloc(sizeof(int) * 8);
    if(neighbors == NULL){
        printf("Short on memory");
        return;
    }
    /*
    * User has to select a sign for himself / herself. Computer will get the opposite sign.
    */
    while(1){
        printf("Select your sign. The only valid values are plus(+) or cross(x)\n");
        scanf("%c", &usersign);
        if(usersign == '+' || usersign == 'x')
            break;
    }
    /*
    * Main loop for the game.
    */
    while(available_slots > 0){
        /*
        * Get the human's next move
        */
        printf("What is your next move. [0..35]\n");
        scanf("%d", &move);
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
            mark_slot(usersign, move, false);
            draw_board();
            /*
            * Last slot has been filled
            */
            if(available_slots == 0)
                continue;
            /*
            * Get the best possible move for computer.
            * Mark the slot and calculate computer's points.
            * Draw the board.
            */
            computers_move = best_possible_move(other_player(usersign));
            printf("Computer will mark slot: %d\n", computers_move);
            mark_slot(other_player(usersign), computers_move, false);
            flip(max);
            computers_points += max.points;
            draw_board();
        }
    }
}
