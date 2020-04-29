//
// Created by Sagar Mahajan on 03/04/20.
//
#include "moving_stack.h"

struct piece * push(color new, square * s){// function which pushes a piece on to a stack
    struct piece *curr = s->stack;// pointer to the top of stack
    s->stack = malloc(sizeof(piece));// creating space for the new piece
    s->stack->p_color = new;//putting in the piece
    s->stack->next = curr;//incrimenting the pointer
    return s->stack;
}

    struct square * push_Stack(struct square *square1, struct square *square2){ //the function which places one stack on top of another

    piece *stack1 = square1->stack;// pointers to the top of the stacks
    piece *stack2 = square2->stack;


    piece *newStack = square1->stack;//
    piece *currentPiece = newStack;
    //loop through and assign the elements of stack1 to the variable new_stackPtr
    while (newStack->next != NULL){
        newStack = newStack->next;
    } //Move till the end of the pointer new_stackPtr

    newStack->next = stack2; //add the next pointer to point to secondStack
    square2->stack = currentPiece;
    square2->stack = push(currentPiece->p_color, square2->stack);

    square2->num_pieces = stack_count(square2);

    //Emtpy the moved square, square1
    set_empty(square1);

    return square2;


}
void stacksize(struct square *square2,struct player *currplayer){// this function

    if(square2->stack == NULL){//checking the stack is null
        perror("Stack is  null");
        return;
    }
    piece *stack = square2->stack;//pointer to the top of the stack

    if(stack_count(square2->stack) <= STACKLIM) {//this if statement checks whether the size of the stack is greater than 5 and only then continues with the function
        return;
    }

    piece * stack_temp = square2->stack;// pointer to the top of stack
    piece * stack_end = malloc(sizeof(piece)*STACKLIM);// this is the pointer made to store the pieces that excede 5 and therefore can be checked
    piece * new_stack = square2->stack;// pointer to the top of stack

    int count = 0;

    while(stack_temp != NULL && count<STACKLIM){//iterating stack_temp to the last piece
        stack_temp = stack_temp->next;
        count++;
    }
    for (int i = 0; i < count-1; ++i) {
        new_stack = new_stack->next;
    }

    new_stack->next = NULL; // set the next pointer of square to null
    print_Stack(square2->stack,"After removing excess pieces ->");//printing the stack after the excess pieces are removed

    stack_end = stack_temp;
    stack_temp = stack_end; // assinging the stack_temp in stack end so that it can be checked

   if(stack_temp!=NULL){// checking the pieces removed and storing them in players own_pieces if its its the same color
       int own = currplayer->own_pieces;
       int throw = currplayer->aquired;

       while (stack_temp!=NULL){
           if(stack_temp->p_color == currplayer->player_color){ own +=1;}
           else{
               throw += 1;
           }
           stack_temp = stack_temp->next;
       }
       /*  assign player values    */
    currplayer->own_pieces = own;
    currplayer->aquired = throw;
}
if(stack_end != NULL){// printint out the extra pieces removed from the stack
print_Stack(stack_end, "the removed pieces ->");
}

    square2->num_pieces = stack_count(square2->stack);


}

int stack_count(piece *s){// counts the number of pieces in the stack
    int count = 0;
    while(s != NULL){
        count++;
        s = s->next;
    }
    if(s!=NULL && s->next == NULL){
        count++;
    }
    return count;
}


void print_Stack(struct piece *s,char *string){// prints the stack
    printf("%s ",string);
    while(s != NULL){
        printf("%s",s->p_color?"G":"R");// prints the color of the pieces
        s = s->next;
    }      printf("\n");
}

void move(square board [BOARD_SIZE][BOARD_SIZE],struct player players[PLAYERS_NUM]){// this function executes the moves of the players

    int red_won = 0;// integers to check who won the game
    int green_won = 0;

    while(red_won != 1  || green_won != 1){// main loop which end when a player wins

        for(int i = 0; i<PLAYERS_NUM; i++) {// loop which helps switch chances between the players


            int row = 0;// integer for the row selected by user when moving stack
            int col = 0;// integer for the column selected by user when moving stack
            int row_fallen = 0;// integer for the row selected by user when placing own piece
            int col_fallen = 0;// integer for the row selected by user when placing own piece
            int valid = 1;// integer to check if the row and col entered by the user is valid
            int valid_fallen = 1;// integer to check if the row and col entered to place a own piece is valid
            int fallen_or_stack = 1;

            if (players[i].own_pieces > 0) {// only asks the user for the option of placing own piece if he/she has one to place

                printf("\ndo you want to place a fallen piece or move a stack (press '0' for fallen piece  or  '1' for stack):\n");
                scanf("%d", &fallen_or_stack);

                if (fallen_or_stack == 0) { // if the player wants to place a own_piece

                    do { // asks the row and col until its a valis square
                        printf("enter the row and column where you want to place the piece:\n");
                        printf("row: ");
                        scanf("%d", &row_fallen);
                        printf("column: ");
                        scanf("%d", &col_fallen);
                        if (board[row_fallen][col_fallen].type == INVALID) {
                            printf("please enter a valid square\n\n");
                            valid_fallen = 0;
                        } else
                            valid_fallen = 1;

                    } while (valid_fallen == 0);


                    board[row_fallen][col_fallen].stack = push(players[i].player_color, &board[row_fallen][col_fallen]); // pushes the piece on top of the stack


                    players[i].own_pieces -= 1;// reduces the players own_piece by 1

                    print_board(board);// prints the board
                    continue;

                }
            }

            red_won = 0;// setting the winning integers to 0 which change to 1 if a player wins
            green_won = 0;

            winning(board,&red_won,&green_won);// calling the winning function
            if( red_won == 1 || green_won == 1){//exits the loop if a player has won
                break;
            }

                do{ // loop so that the player is asked the row and col again if they are not valid
                    printf("\nplayer %d select the row and column of the stack you want to move:\nrow: ", i+1);
                    scanf("%d", &row);
                    printf("column: ");
                    scanf("%d", &col);
                    if(board[row][col].type == INVALID || board[row][col].stack == NULL || board[row][col].stack->p_color != players[i].player_color){//conditions for them to be valid
                        printf("please enter a valid stack\n\n");
                        valid = 0;
                    } else
                        valid=1;
                }while(valid == 0);

            int new_row = row;// new row and col is for the final square the user wants the stack to land
            int new_col = col;




            int moves = stack_count(board[row][col].stack);// setting the number of moves using the number of pieces in the stack
            int decition = 0;

            printf("enter where do you want to move the stack\n");
            for(int z = 0; z < moves;z++){ //loop for the user to enter the moves. this only prints the valid move that the user can choose

                if( row == 0 && (col == 2 || col == 3||col == 4||col == 5))
                    printf("2 for down\n");
                else if( row == 7 && (col == 2 || col == 3||col == 4||col == 5))
                    printf("1 for up\n");
                else if( row == 1 && col == 1)
                    printf("2 for down \t 4 for right\n");
                else if( row == 1 && col == 6)
                    printf("2 for down \t 3 for left\n");
                else if( row ==1  && col == 6)
                    printf("2 for down \t 3 for left\n");
                else if( row ==6  && col == 1)
                    printf("1 for up \t 4 for right\n");
                else if( row ==6  && col == 6)
                    printf("1 for up \t 3 for left\n");
                else if( col == 0 && (row == 2 || row == 3||row == 4||row == 5))
                    printf("4 for right\n");
                else if( col == 7 && (row == 2 || row == 3||row == 4||row == 5))
                    printf("3 for left\n");
                else
                    printf("1 for up \t 2 for down \t 3 for left \t 4 for right\n");

                scanf("%d", &decition); // asking user for the moves

                if(decition == 1) // changing the new ro and col according to the move made
                    new_row -= 1;
                if(decition == 2)
                    new_row += 1;
                if(decition == 3)
                    new_col -= 1;
                if(decition == 4)
                    new_col += 1;

            }

            struct player *curr_p = &players[i];// pointer to the current player


            board[new_row][new_col] = *push_Stack(&board[row][col], &board[new_row][new_col]);// calling the function to move the stack
            print_Stack(board[new_row][new_col].stack,"\nafter Moving ->");//

            stacksize(&board[new_row][new_col],curr_p);


            printf(" %s's fallen supply -> %d\n", &players[i].player_name, players[i].own_pieces);

            print_board(board);// printing out the board




    }
        if(red_won == 1) {  // prints the final lines when someone wins
            printf("\n\n!! congratulations red !! you have won the game. better luck next time ");
            break;

        }
        if(green_won == 1) {
            printf("\n\n!!congratulations green!! you have won the game. better luck next time");
            break;

        }

    }


}
void winning(square board [BOARD_SIZE][BOARD_SIZE], int *r, int *g){ // this function checks if one of the players have won the game

    *g = 1;
    *r = 1;

    for(int j = 0; j < BOARD_SIZE; j ++) { // this loop checks each valid square in the board if all the colours are the same
        for (int k = 0; k < BOARD_SIZE; k++) {
            if (board[j][k].type == VALID) {
                if (board[j][k].stack == NULL)
                    continue;
                else {
                    if (board[j][k].stack->p_color == GREEN) { // if the loop finds a green piece, that means red has not won and vice versa
                        *r = 0;

                    } else {
                        *g = 0;

                    }
                }
            } else
                continue;
        }
    }

    }




