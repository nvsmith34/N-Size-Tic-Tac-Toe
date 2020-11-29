///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission for CS 354 Fall 2020, Deb Deppeler
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        (n_in_a_row.c)
// This File:        (n_in_a_row.c)
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Fall 2020
//
// Author:           Nathan Smith
// Email:            nvsmith@wisc.edu
// // CS Login:      nathans
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
////////////////////////////////////////////////////////////////////////////////
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
     
char *DELIM = ",";  // commas ',' are a common delimiter character for data strings
     
/* COMPLETED:       
 * Retrieves from the first line of the input file,
 * the size of the board (number of rows and columns).
 * 
 * fp: file pointer for input file
 * size: pointer to size
 */
void get_dimensions(FILE *fp, int *size) {      
    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, fp) == -1) {
        printf("Error in reading the file.\n");
        exit(1);
    }

    char *token = NULL;
    token = strtok(line, DELIM);
    *size = atoi(token);
}       
 
   
  
/* TODO:
 * Returns 1 if and only if the board is in a valid state.
 * Otherwise returns 0.
 * 
 * board: heap allocated 2D board
 * size: number of rows and columns
 */
int n_in_a_row(int **board, int size) {

    //checks if board size is odd
    if(size%2 == 0)
        return 0;

    int countO=0; //used to track number of Os
    int countX = 0; //used to track number of Xs
    //loop through board and count Xs and Os
    for (int i = 0; i<size; i++){
        for(int z = 0; z<size; z++){

            if(*(*(board+i)+z) == 1){
                countX++;
            }
            else if(*(*(board+i)+z) == 2){
                countO++;
            }
        }
    }
    //make sure Xs equal Os or 1 more X than O
    if(countO!=countX && (countO+1)!=countX){
        return 0;
    }


    //checks rows
    int rowWinX = 0; //number of row wins for X
    int rowWinO = 0; //number of row wins for O
    //loops through to count row wins for each
    for(int i=0; i<size; i++){
        int numX = 0; //number of X in each row
        int numO = 0; //number of O in each row
        for (int z=0; z<size; z++){
                //count the Xs in this row
                if(*(*(board+i)+z) == 1){
                    numX++;
                }
                //count the Os in this row
                if(*(*(board+i)+z) == 2){
                    numO++;
                }
        }
        //if the Xs equal the size of the row, then a win for X
        if(numX == size){
            rowWinX++;
        }
        //if the Os equal the size of the row, then win for O
        if(numO == size){
            rowWinO++;
        }

    }
    //cant have parallel X win lines
    if(rowWinX>1){
        return 0;
    }
    //cant have parallel O win lines
    if(rowWinO>1){
        return 0;
    }
    //cant have both X and O win
    if(rowWinX>0 && rowWinO>0){
        return 0;
    }


    //check column wins
    int colWinX = 0; //number of column win lines for X
    int colWinO = 0; //number of column win lines for O
    //loops through to count column wins for each
        for(int i=0; i<size; i++){
            int numX = 0; //number of X in each column
            int numO = 0; //number of O in each column
            for (int z=0; z<size; z++){
                    //count the Xs in this column
                    if(*(*(board+z)+i) == 1){
                        numX++;
                    }
                    //count the Os in this column
                    if(*(*(board+z)+i) == 2){
                        numO++;
                    }
            }
            //if the Xs equal the size of the column, then a win for X
            if(numX == size){
                colWinX++;
            }
            //if the Os equal the size of the column, then a win for X
            if(numO == size){
                colWinO++;
            }
        }
        //cant have parallel X win lines
        if(colWinX>1){
            return 0;
        }
        //cant have parallel O win lines
        if(colWinO>1){
            return 0;
        }
        //cant have both X and O win
        if(colWinX>0 && colWinO>0){
            return 0;
        }


        //check left to right diagonal wins
        int numX = 0; //check number of Xs in left to right diagonal
        int numO = 0; //check number of Os in left to right diagonal
        for(int i=0; i<size; i++){
            //check to see if diagonals equal upper left
            if(*(*(board+i)+i) == **board){
                //if X then count for X
                if(*(*(board+i)+i) == 1){
                     numX++;
                }
                //if O then count for O
                if(*(*(board+i)+i) == 2){
                     numO++;
                }
            }
        }
        int diagWinX = 0; //number of left to right diagonal X wins
        int diagWinO = 0; //nubmer of left to right diagonal O wins
        //if number of X equal size, then win
        if(numX == size){
            diagWinX++;
        }
        //if number of O equal size, then win
        if(numO == size){
            diagWinO++;
        }

        //check right to left diagonal wins
        numX = 0; //reset to 0
        numO = 0; //reset to 0
        for(int i=0; i<size; i++){
            //checks to see if diagonals equal upper right
            if(*(*(board+i) + (size-1)) == *(*board+size)){
                //if X then count for X
                if(*(*(board+i) + (size-i)) == 1){
                     numX++;
                }
                //if O then count O
                if(*(*(board+i) + (size-i))== 2){
                    numO++;
                }
          }
        }
        diagWinX = 0; //reset
        diagWinO = 0; //reset
        //if number of X equals size, then win
        if(numX == size){
            diagWinX++;
        }
        //if number of O equals size then win
        if(numO == size){
            diagWinO++;
        }
        //make sure both X and O cant win
        if(diagWinX>0 && (colWinO>0 || rowWinO>0) ){
            return 0;
        }
        //dual of above
        if(diagWinO>0 && (colWinX>0 || rowWinX>0) ){
            return 0;
        }

        return 1;
}    
  
 
   
/* PARTIALLY COMPLETED:
 * This program prints Valid if the input file contains
 * a game board with either 1 or no winners; and where
 * there is at most 1 more X than O.
 * 
 * argc: CLA count
 * argv: CLA value
 */
int main(int argc, char *argv[]) {              
     
    //TODO: Check if number of command-line arguments is correct.]
    if(argc == 1 || argc>2){
        printf("Usage: ./n_in_a_row <input_filename> \n");
        exit(1);
    }

    //Open the file and check if it opened successfully.
    FILE *fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        printf("Can't open file for reading.\n");
        exit(1);
    }

    //Declare local variables.
    int size;

    //TODO: Call get_dimensions to retrieve the board size.
    get_dimensions(fp, &size);
    //TODO: Dynamically allocate a 2D array of dimensions retrieved above.
    //allocate in 1D then check if succesful
    int **board;
    board = malloc(sizeof(int *) * size);
    if(board == NULL){
        printf("Error while allocating memory.\n");
         exit(1);
    }

    //allocate 2D then check if successful
    for(int i =0; i<size; i++){
        *(board+i) = malloc(sizeof(int) *size);
        if(*(board+i) == NULL){
                printf("Error while allocating memory.\n");
                 exit(1);
            }
    }
    //Read the file line by line.
    //Tokenize each line wrt the delimiter character to store the values in your 2D array.
    char *line = NULL;
    size_t len = 0;
    char *token = NULL;
    for (int i = 0; i < size; i++) {

        if (getline(&line, &len, fp) == -1) {
            printf("Error while reading the file.\n");
            exit(1);
        }

        token = strtok(line, DELIM);
        for (int j = 0; j < size; j++) {
            //TODO: Complete the line of code below
            //to initialize your 2D array.
            *(*(board+i)+j) = atoi(token);
            token = strtok(NULL, DELIM);
        }
    }

    //TODO: Call the function n_in_a_row and print the appropriate
    //output depending on the function's return value.
    if(n_in_a_row(&(*board), size)==1){
        printf("valid \n");
    }
    else{
        printf("invalid \n");
    }
    //TODO: Free all dynamically allocated memory.
    for(int i=0; i<size; i++){
        free(*(board+i));
        *(board+i) = NULL;
    }
    //Close the file.
    if (fclose(fp) != 0) {
        printf("Error while closing the file.\n");
        exit(1);
    } 
     
    return 0;       
}       



                                        // FIN
