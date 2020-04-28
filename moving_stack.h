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
int stack_count(piece *s);
void print_Stack(struct piece *stack,char *string);
void stacksize(struct square *square2,struct player *currplayer);
void winning(square board [BOARD_SIZE][BOARD_SIZE],struct player *currp, int *r, int *g);
set_empty(square * s);