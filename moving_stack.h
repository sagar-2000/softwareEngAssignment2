//
// Created by Sagar Mahajan on 03/04/20.
//

#ifndef FOCUS_MOVING_STACK_H
#define FOCUS_MOVING_STACK_H

#endif //FOCUS_MOVING_STACK_H


#include <stdio.h>
#include <stdlib.h>

#include "game_init.h"
#include "stdbool.h"
#define STACKLIM 5


void move(square board [BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM]);
void print_board(square board[BOARD_SIZE][BOARD_SIZE]);
int stack_count(piece *n_stack);
void printStack(struct piece *stack,char *string);
struct square * stacksizecheck(struct square *square2, player *currplayer, int own, int throw);
void stacksize(struct square *square2,struct player *currplayer);
void winning(square board [BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM], int r, int g);
void removedPieces(struct piece *removed, struct player *cp );
set_empty(square * s);