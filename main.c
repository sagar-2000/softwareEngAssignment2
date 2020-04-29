//
// Created by Lili on 26/03/2020.
//

#include <stdio.h>

#include "input_output.h"
//#include "moving_stack.h"


void main() {

    // declaration of the players and the board
    player players[PLAYERS_NUM]; // array holding the players information
    square board[BOARD_SIZE][BOARD_SIZE];// the main board

    initialize_players(players);// calling function to initialize players

    initialize_board(board);// calling function to initialize the board
    players[0].own_pieces =1;

    print_board(board);// printing the board

    move(board,players);// calling the function which lets players play their moves

    exit(EXIT_SUCCESS);
}
