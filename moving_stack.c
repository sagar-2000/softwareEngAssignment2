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

struct piece * pop(struct piece *top){
    struct piece *curr = top;
    if(curr!=NULL){
        top = curr->next;
        printf("Stack Data: %d\n", curr->p_color);
        free(curr);
    }
    return top;


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
void stacksize(struct square *square2,struct player *currplayer){

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
    print_Stack(square2->stack,"After new_stack ->");//printing the stack after the excess pieces are removed

    stack_end = stack_temp;
    stack_temp = stack_end; // assinging the stack_temp in stack end so that it can be checked

   if(stack_temp!=NULL){// checking the
       int own = currplayer->own_pieces;
       int throw = currplayer->aquired;

       while (stack_temp!=NULL){
           if(stack_temp->p_color == currplayer->player_color){ own +=1;} // if its my own piece
           else{
               throw += 1;
           } // not my piece
           stack_temp = stack_temp->next;
       }
       /*  assign player values    */
    currplayer->own_pieces = own;
    currplayer->aquired = throw;
}
if(stack_end != NULL){
print_Stack(stack_end, "Fallen Stack ->");
}

    square2->num_pieces = stack_count(square2->stack);


}

int stack_count(piece *s){
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


void print_Stack(struct piece *s,char *string){
    printf("%s ",string);
    while(s != NULL){
        printf("%s",s->p_color?"G":"R");
        s = s->next;
    }      printf("\n");
}

void move(square board [BOARD_SIZE][BOARD_SIZE],struct player players[PLAYERS_NUM]){

    int red_won = 0;
    int green_won = 0;

    while(red_won != 1  || green_won != 1){

        for(int i = 0; i<PLAYERS_NUM; i++) {
            int row_fallen = 0;
            int col_fallen = 0;
            int row = 0;
            int col = 0;
            int valid = 1;
            int valid_fallen = 1;
            int fallen_or_stack = 1;

            if (players[i].own_pieces > 0) {

                printf("do you want to place a fallen piece or move a stack: (0 for fallen piece \t 1 for stack)\n");
                scanf("%d", fallen_or_stack);

                if (fallen_or_stack == 0) {

//                    do {
//                        printf("enter the row and column where you want to place the piece");
//                        scanf("%d", &row_fallen);
//                        printf("column: ");
//                        scanf("%d", &col_fallen);
//                        if (board[row_fallen][col_fallen].type == INVALID) {
//                            printf("please enter a valid square\n\n");
//                            valid_fallen = 0;
//                        } else
//                            valid_fallen = 1;
//
//                    } while (valid_fallen == 0);


//                    board[row_fallen][col_fallen].stack = push(players[i].player_color, &board[row_fallen][col_fallen]);
//
//                    players[i].own_pieces -= 1;
//
//                    print_board(board);


                }
            }

            red_won = 0;
            green_won = 0;

            winning(board,&players[i],&red_won,&green_won);
            if( red_won == 1 || green_won == 1){
                break;
            }

                do{
                    printf("player %d select the row and column of the stack you want to move:\nrow: ", i+1);
                    scanf("%d", &row);
                    printf("column: ");
                    scanf("%d", &col);
                    if(board[row][col].type == INVALID || board[row][col].stack == NULL || board[row][col].stack->p_color != players[i].player_color){
                        printf("please enter a valid stack\n\n");
                        valid = 0;
                    } else
                        valid=1;
                }while(valid == 0);

            int new_row = row;
            int new_col = col;




            int moves = stack_count(board[row][col].stack);
            int decition = 0;

            printf("enter where do you want to move the stack\n");
            for(int z = 0; z < moves;z++){
                if( row == 0 && (col == 2 || col == 3||col == 4||col == 5))
                    printf("2 for down");
                else if( row == 7 && (col == 2 || col == 3||col == 4||col == 5))
                    printf("1 for up");
                else if( row == 1 && col == 1)
                    printf("2 for down \t 4 for right");
                else if( row == 1 && col == 6)
                    printf("2 for down \t 3 for left");
                else if( row ==1  && col == 6)
                    printf("2 for down \t 3 for left");
                else if( row ==6  && col == 1)
                    printf("1 for up \t 4 for right");
                else if( row ==6  && col == 6)
                    printf("1 for up \t 3 for left");
                else if( col == 0 && (row == 2 || row == 3||row == 4||row == 5))
                    printf("4 for right");
                else if( col == 7 && (row == 2 || row == 3||row == 4||row == 5))
                    printf("3 for left");
                else
                    printf("1 for up \t 2 for down \t 3 for left \t 4 for right");

                scanf("%d", &decition);

                if(decition == 1)
                    new_row -= 1;
                if(decition == 2)
                    new_row += 1;
                if(decition == 3)
                    new_col -= 1;
                if(decition == 4)
                    new_col += 1;

            }

            struct player *curr_p = &players[i];


            board[new_row][new_col] = *push_Stack(&board[row][col], &board[new_row][new_col]);
            print_Stack(board[new_row][new_col].stack,"Moved ->");

            stacksize(&board[new_row][new_col],curr_p);


            printf(" %s fallen supply\n%d\n", &players[i].player_name, players[i].own_pieces);

            print_board(board);




    }
        if(red_won == 1) {
            printf("\n\n!! congratulations red !! you have won the game. better luck next time ");
            break;

        }
        if(green_won == 1) {
            printf("\n\n!!congratulations green!! you have won the game. better luck next time");
            break;

        }

    }


}
void winning(square board [BOARD_SIZE][BOARD_SIZE],struct player *currp, int *r, int *g){

    *g = 1;
    *r = 1;

    for(int j = 0; j < BOARD_SIZE; j ++) {
        for (int k = 0; k < BOARD_SIZE; k++) {
            if (board[j][k].type == VALID) {
                if (board[j][k].stack == NULL)
                    continue;
                else {
                    if (board[j][k].stack->p_color == GREEN) {
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




