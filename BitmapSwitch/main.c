#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define ARRAY_SIZE 10

//Al variables needed for this file 
int i,j;
int counter = 0;
int holding1,holding2;
int startrow, startcollumn;
int endrow, endcollumn;
int currentrow,currentcollumn;
int currentjunctionrow = 0,currentjunctioncollumn = 0;
char first_junction = '0';
//The map that is used to find the route 
int matrix[][ARRAY_SIZE] ={     {0,0,0,0,0,0,0,0,0},
                                {0,5,0,1,0,0,1,4,0},
                                {0,4,1,4,0,1,0,1,0},
                                {0,1,0,1,0,1,0,1,0},
                                {0,4,1,4,1,4,1,4,0},
                                {0,1,0,0,0,1,0,1,0},
                                {0,2,0,0,0,1,0,1,0}};

char instructions[ARRAY_SIZE];

void finding_place(int place_number){
    for(i = 0;i<7;i++){
        for(j = 0;j<ARRAY_SIZE;j++){
            if(matrix[i][j] == place_number){
            printf("Gevonden!: matrix[%d][%d]\n",i,j);
            holding1 = i;
            holding2 = j;
            }
    }
}
}
//First junction waarde bewaren want anders weet ik niet welke kant hij op rijdt. 
void junction(){
    currentjunctionrow = currentrow;
    currentjunctioncollumn = currentcollumn;
    if(currentrow < endrow){ //down
        if(matrix[currentrow + 1][currentcollumn] == 1){
            up_down();
            first_junction = 'u';
            adding_instructions(first_junction);
        }else{
            first_junction = sideways();
            adding_instructions(first_junction);
        }
    }if(currentrow > endrow){ //up
        if(matrix[currentrow-1][currentcollumn] == 1){
            up_down();
            first_junction = 'u';
            adding_instructions(first_junction);
        }else{
            first_junction = sideways();
            adding_instructions(first_junction);
        }
    }if(currentrow == endrow){ //sideways 
        first_junction = sideways();
        adding_instructions(first_junction);
    }
}

int sideways(){
    if(currentcollumn > endcollumn){
            //left 
            if(matrix[currentrow][currentcollumn-1] == 1){
            //if there is a 1 to the left the current place moves one to the left 
                printf("[%d][%d]\n", currentrow,currentcollumn);
                currentcollumn--;
                return 'l';
            

            }else if(matrix[currentrow][currentcollumn-1] == 5){
                printf("[%d][%d]\n", currentrow,currentcollumn);
                currentcollumn--;
                printf("Done \n");
                return 'l';
            }else if(matrix[currentrow][currentcollumn-1] == 4){
                printf("[%d][%d]\n", currentrow,currentcollumn);
                currentcollumn--;
                junction();
                
            }
    }else if(currentcollumn < endcollumn){
            //Left 
            if(matrix[currentrow][currentcollumn+1] == 1){
                //if there is a 1 to the left the current place moves one to the left 
                printf("[%d][%d]\n", currentrow,currentcollumn);
                currentcollumn++;
                return 'r';

            }else if(matrix[currentrow][currentcollumn+1] == 5){
                currentcollumn++;
                printf("[%d][%d]\n", currentrow,currentcollumn);
                printf("Done \n");
                return 'r';
            }else if(matrix[currentrow][currentcollumn+1] == 4){
                printf("[%d][%d]\n", currentrow,currentcollumn);
                currentcollumn++;
                junction();
            }
    }
}

int up_down(){
    if(currentrow > endrow){
        printf("[%d][%d]\n First Junction: %c\n", currentrow,currentcollumn,first_junction);
        currentrow--;
    }else if(currentrow < endrow){
        printf("[%d][%d]\n First Junction: %c\n", currentrow,currentcollumn,first_junction);
        currentrow++;
    }else if(currentrow == endrow){
        printf("[%d][%d]\n First Junction: %c\n", currentrow,currentcollumn,first_junction);
        return 1;
    }
}

int finding_route(){
	while(matrix[currentrow][currentcollumn] != matrix[endrow][endcollumn]){//Je kijkt 
            sleep(0,5);
            if(currentrow > endrow){
			if (matrix[currentrow-1][currentcollumn] == 1){ 
				up_down();}
            else{
                if(matrix[currentrow-1][currentcollumn] == 1){
                    up_down();
                }
                else if (matrix[currentrow-1][currentcollumn] == 4){
                junction();
            }
            }}else if(currentrow < endrow){
                    if (matrix[currentrow+1][currentcollumn] == 1){ 
				up_down();}
            else if (matrix[currentrow+1][currentcollumn] == 4){
                junction();
            }
            else{
                if(matrix[currentrow+1][currentcollumn] == 1){
                up_down();}
            }
            }else if(up_down() == 1){
                //The rows are equal so sideways.
                sideways();}
            else if(matrix[currentrow][currentcollumn] == 5){
                printf("Done \n");
            }
    }
}

void adding_instructions(char first_junction){
    instructions[counter] = first_junction;
    counter++;
}

int main(int argc, char **argv){
	printf("Start index\n");
    finding_place(2);
    startrow = holding1;
    startcollumn = holding2;
    printf("Waardes startrow en startcollumn: %d,%d\n", startrow,startcollumn);
    printf("End index\n");
    finding_place(5);
    endrow = holding1;
    endcollumn = holding2;
    printf("Waardes startrow en startcollumn: %d,%d\n", endrow,endcollumn);
    currentrow = startrow;
    currentcollumn = startcollumn;
    finding_route();
    for(int k=0; k<3;k++){
        printf("%c ", instructions[k]);
    }
    return(EXIT_SUCCESS);
}
