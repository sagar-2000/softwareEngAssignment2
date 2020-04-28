//
// Created by Sagar Mahajan on 03/04/20.
//
#include "moving_stack.h"

struct piece * push(color new, square * s){
    struct piece *curr = s->stack;
    s->stack = malloc(sizeof(piece));
    s->stack->p_color = new;
    s->stack->next = curr;
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
    struct square * push_Stack(struct square *square1, struct square *square2){
    // This function stacks top2 on top of stack top1


    piece *stack1 = square1->stack;
    piece *stack2 = square2->stack;


    //set the new_stackPtr = square1 stack
    piece *new_stackPtr = square1->stack;
    piece *currentPiece = new_stackPtr;
    //loop through and assign the elements of stack1 to the variable new_stackPtr
    while (new_stackPtr->next != NULL){
        new_stackPtr = new_stackPtr->next;
    } //Move till the end of the pointer new_stackPtr

    new_stackPtr->next = stack2; //add the next pointer to point to secondStack

    square2->stack = currentPiece;
    // '' This is needed to add the last piece of the stack to square2
    square2->stack = push(currentPiece->p_color, square2->stack);

    square2->num_pieces = stack_count(square2);

    //Emtpy the moved square, square1
    set_empty(square1);

    return square2;


}
void stacksize(struct square *square2,struct player *currplayer){
    if(square2->stack == NULL){
        perror("Stack is  null");
        return;
    }
    piece *stack = square2->stack;
    printf("current stack count = %d",stack_count(stack));
    if(stack_count(square2->stack) <= 2) {return;}
    printf("MADE IT");
    piece *tempStack = square2->stack;
    piece * final_stack = malloc(sizeof(piece)*STACKLIM);
    piece * new_stack = square2->stack;
    int count = 0;
    while(tempStack != NULL && count<2){
        tempStack = tempStack->next;
        count++;
    }
    for (int i = 0; i < count-1; ++i) {
        new_stack = new_stack->next;
    }
    //square is now with in LIMIT
    new_stack->next = NULL; // set the next pointer of n_square to null
    printStack(square2->stack,"After new_stack ->");
    final_stack = tempStack;
    tempStack = final_stack; // assign temp to allow to iterate over the stack to check pieces

    /* add the fallen pieces to own_pieces and adversary*/
   if(tempStack!=NULL){
       int my_pieces = currplayer->own_pieces;
       int others = currplayer->aquired;
       while (tempStack!=NULL){
           if(tempStack->p_color == currplayer->player_color){ my_pieces +=1;} // if its my own piece
           else{ others += 1;} // not my piece
           tempStack = tempStack->next;
       }
       /*  assign player values    */
    currplayer->own_pieces = my_pieces;
    currplayer->aquired = others;
}
if(final_stack != NULL){
printStack(final_stack, "Fallen Stack ->");
}

    square2->num_pieces = stack_count(square2->stack);


}
struct square * stacksizecheck(struct square *square2,struct player *currplayer, int own1, int throw1){


    //if(stack_count(square2->stack) <= 5) {

        piece *last = NULL;
        piece *current = square2->stack;
        piece *final = malloc(sizeof(piece) * 5);
        piece *remove = NULL;
        piece *temp = square2->stack;
        piece *temp2 = square2->stack;
        color pcol = currplayer->player_color;


        int temp_count = 0;
        while (current != NULL) {
            if(temp_count<5){
                current = current->next;
                temp_count++;
            }
            else{
                last = current;
            }

        }
    if (last != NULL) {
        printStack(last, "last -");
//        current = current->next;
        while (current->next != NULL) {
            printf("boom");
            remove = current;
            printStack(remove, "remove -");
            removedPieces(remove,currplayer);
            current = current->next;
            free(remove);
        }
        last->next = NULL;
        square2->num_pieces = stack_count(temp2);

    }


   // }
    return square2;
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

void removedPieces(struct piece *removed, struct player *cp){

     int own = 0;
     int throw = 0;

    own = cp->own_pieces;
    throw = cp->aquired;

    if(removed->p_color == cp->player_color){
        own += 1;
    } else throw += 1;

    printf("own = %d", own);
    printf("throw = %d", throw);

    cp->own_pieces = own;
    cp->aquired = throw;


}

void printStack(struct piece *stack,char *string){
    printf("%s ",string);
    while(stack != NULL){
        printf("%s",stack->p_color?"B":"R");
        stack = stack->next;
    }      printf("\n");
}
void move(square board [BOARD_SIZE][BOARD_SIZE],struct player players[PLAYERS_NUM]){

    int red_won = 0;
    int green_won = 0;

    while(red_won != 1  || green_won != 1){

        for(int i = 0; i<PLAYERS_NUM; i++){
            int row = 0;
            int col = 0;
            int valid = 1;

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
                    for(int i = 0; i < moves;i++){
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
                    printStack(board[new_row][new_col].stack,"Moved ->");

                    stacksize(&board[new_row][new_col],curr_p);




//            piece *st = board[new_row][new_col].stack;
//
//                    for(int z=0; z<board[new_row][new_col].num_pieces;z++){
//                        printf("\n%d\n",st->p_color);
//                        st = st->next;
//                    }
//
//
                    printf("supply\n%d\n", players[i].own_pieces);

                    print_board(board);


                    winning(board, &players[i], red_won, green_won);

                    green_won = 1;
                    red_won = 1;

            for(int j = 0; j < BOARD_SIZE; j ++) {
                for (int k = 0; k < BOARD_SIZE; k++) {
                    if (board[j][k].type == VALID) {
                        if (board[j][k].stack == NULL)
                            continue;
                        else {
                            if (board[j][k].stack->p_color == GREEN) {
                                red_won = 0;
                                continue;
                            } else {
                                green_won = 0;
                                continue;
                            }
                        }
                    } else
                        continue;
                }
            }

            if(red_won == 1) {
                printf("\n\n!! congratulations %s !! you have won the game. better luck next time %s", players[0].player_name,
                       players[1].player_name);
                break;
            }
            if(green_won == 1) {
                printf("\n\ncongratulations %s you have won the game. better luck next time %s", players[1].player_name,
                       players[0].player_name);
                break;
            }
    }

    }


}
void winning(square board [BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM], int r, int g){




    }




