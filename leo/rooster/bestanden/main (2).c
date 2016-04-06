



int i,j;
int counter = 0;
int holding1,holding2;
int startrow, startcollumn;
int endrow, endcollumn;
int currentrow,currentcollumn;
int currentjunctionrow = 0,currentjunctioncollumn = 0;
char first_junction = '0';
char new_matrix[20];
char turn_left = 'L';
char turn_right = 'R';
char up = 'U';
char down = 'D';

int matrix[7][10] ={     {0,1,0,1,0,1,0,1,0},
                                {1,4,1,4,1,5,1,4,1},
                                {0,0,0,1,0,1,0,1,0},
                                {1,4,1,4,1,4,1,4,1},
                                {0,1,0,1,0,1,0,1,0},
                                {1,4,1,4,1,4,1,4,1},
                                {0,2,0,1,0,1,0,1,0}};


int junctions[20][2];

char instructions[20];


void adding_instructions(char first_junction){
    instructions[counter] = first_junction;
    counter++;
}






int steering_sideways(){
    if(currentcollumn < endcollumn){ //++
			if(matrix[currentrow][currentcollumn+1] == 1){
				currentcollumn++;

                adding_instructions('r');
			}else if(matrix[currentrow][currentcollumn+1] == 4){
                currentcollumn++;
                currentjunctionrow = currentrow;
                currentjunctioncollumn = currentcollumn;
                junctions[counter][0] = currentjunctionrow;
                junctions[counter][1] = currentjunctioncollumn;
                if(currentrow == endrow){
				if(matrix[currentrow][currentcollumn+1] == 1){
					currentcollumn++;

                    adding_instructions('r');
                }}else{ //++
                    finding_route();
                    adding_instructions('u');

                }
		}else if(matrix[currentrow][currentcollumn+1] == 5){
            currentcollumn++;

            adding_instructions('\0');
        }
	}else if(currentcollumn > endcollumn){ //--
			if(matrix[currentrow][currentcollumn-1] == 1){
				currentcollumn--;
			}else if(matrix[currentrow][currentcollumn-1] == 4){
                currentcollumn--;

                adding_instructions('l');
                currentjunctionrow = currentrow;
                currentjunctioncollumn = currentcollumn;
                junctions[counter][0] = currentjunctionrow;
                junctions[counter][1] = currentjunctioncollumn;
                if(currentrow == endrow){
				if(matrix[currentrow][currentcollumn-1] == 1){
					currentcollumn--;

                    adding_instructions('l');
                }}else{
                    finding_route();
                    adding_instructions('u');

                }
    }else if(matrix[currentrow][currentcollumn-1] == 5){
            currentcollumn--;

            adding_instructions('/0');
    }
    }

}











void left(){
        turn_left = 'U';
        turn_right = 'D';
        up = 'R';
        down = 'L';
}

void right(){
    turn_right = 'U';
    turn_left = 'D';
    up = 'L';
    down = 'R';
}

void up_settings(){
    turn_right = 'R';
    turn_left = 'L';
    up = 'U';
    down = 'D';
}

int calculate(){
    int i = 0;
    while(instructions[i] != '\0'){
        if(instructions[i] == 'l'){
            new_matrix[i] = turn_left;

            left();
            i++;
            while(1){
            if((instructions[i] != 'u') && (instructions[i] != '\0')){
                if(instructions[i] == 'l'){
                    new_matrix[i] = turn_left;

                }else if(instructions[i] == 'r'){
                    new_matrix[i] = turn_right;

                }else if(instructions[i] == 'd'){
                    new_matrix[i] = down;

                }else if(instructions[i] == '\0'){
                            break;
                        }
                i++;
            }else{
                new_matrix[i] = up;

                i++;
                up_settings();
                break;
            }}
        }else if((instructions[i] == 'r') && (instructions[i] != '\0')){
            new_matrix[i] = turn_right;

            right();
            i++;
            while(1){
                if(instructions[i] != 'u'){
                        if(instructions[i] == 'l'){
                            new_matrix[i] = turn_left;

                        }else if(instructions[i] == 'r'){
                            new_matrix[i] = turn_right;

                        }else if(instructions[i] == 'd'){
                            new_matrix[i] = down;

                        }else if(instructions[i] == '\0'){
                            break;
                        }
                i++;
                }else if(instructions[i] == 'u'){
                    new_matrix[i] = up;

                    i++;
                    up_settings();
                    break;
                }
            }
        }else if((instructions[i] == 'u') && (instructions[i] != '\0')){
            new_matrix[i] = up;

            i++;
        }
    }
}

void finding_place(int place_number){
    for(i = 0;i<7;i++){
        for(j = 0;j<10;j++){
            if(matrix[i][j] == place_number){

            holding1 = i;
            holding2 = j;
            }
    }
}}

void get_places(){

    finding_place(2);
    startrow = holding1;
    startcollumn = holding2;

    finding_place(5);
    endrow = holding1;
    endcollumn = holding2;

    currentrow = startrow;
    currentcollumn = startcollumn;
}

void finding_route(){
	if(currentrow < endrow){ //++
		if(matrix[currentrow + 1][currentcollumn] == 1){
			currentcollumn++;
		}else if(matrix[currentrow+1][currentcollumn] == 4){
			currentrow++;
            currentjunctionrow = currentrow;
            currentjunctioncollumn = currentcollumn;
            junctions[counter][0] = currentjunctionrow;
            junctions[counter][1] = currentjunctioncollumn;
			if(currentrow != endrow){
			if(matrix[currentrow+1][currentcollumn] == 1){
				currentrow++;
                adding_instructions('u');
			}else{
                steering_sideways();
			}}
			else{
                steering_sideways();
				//sideways
			}
		}else if(matrix[currentrow+1][currentcollumn] == 5){
			currentrow++;

            adding_instructions('\0');
		}else if(matrix[currentrow+1][currentcollumn] == 0){
            steering_sideways();
        }
	}else if(currentrow > endrow){ //--
		if(matrix[currentrow - 1][currentcollumn] == 1){
			currentrow--;
		}else if(matrix[currentrow- 1][currentcollumn] == 4){
			currentrow--;
            currentjunctionrow = currentrow;
            currentjunctioncollumn = currentcollumn;
            junctions[counter][0] = currentjunctionrow;
            junctions[counter][1] = currentjunctioncollumn;
			if(currentrow != endrow){
			if(matrix[currentrow -1][currentcollumn] == 1){
				currentrow--;

                adding_instructions('u');
			}else{
                steering_sideways();
			}}
			else{
                steering_sideways();
				//sideways
			}
		}else if(matrix[currentrow-1][currentcollumn] == 5){
			currentrow--;

            adding_instructions('\0');
		}else if(matrix[currentrow-1][currentcollumn] == 0){
            steering_sideways();
        }
	}else if(currentrow == endrow){ //sideways
		steering_sideways();
}
}

int steering_sideways(){
    if(currentcollumn < endcollumn){ //++
			if(matrix[currentrow][currentcollumn+1] == 1){
				currentcollumn++;

                adding_instructions('r');
			}else if(matrix[currentrow][currentcollumn+1] == 4){
                currentcollumn++;
                currentjunctionrow = currentrow;
                currentjunctioncollumn = currentcollumn;
                junctions[counter][0] = currentjunctionrow;
                junctions[counter][1] = currentjunctioncollumn;
                if(currentrow == endrow){
				if(matrix[currentrow][currentcollumn+1] == 1){
					currentcollumn++;

                    adding_instructions('r');
                }}else{ //++
                    finding_route();
                    adding_instructions('u');

                }
		}else if(matrix[currentrow][currentcollumn+1] == 5){
            currentcollumn++;

            adding_instructions('\0');
        }
	}else if(currentcollumn > endcollumn){ //--
			if(matrix[currentrow][currentcollumn-1] == 1){
				currentcollumn--;
			}else if(matrix[currentrow][currentcollumn-1] == 4){
                currentcollumn--;

                adding_instructions('l');
                currentjunctionrow = currentrow;
                currentjunctioncollumn = currentcollumn;
                junctions[counter][0] = currentjunctionrow;
                junctions[counter][1] = currentjunctioncollumn;
                if(currentrow == endrow){
				if(matrix[currentrow][currentcollumn-1] == 1){
					currentcollumn--;

                    adding_instructions('l');
                }}else{
                    finding_route();
                    adding_instructions('u');

                }
    }else if(matrix[currentrow][currentcollumn-1] == 5){
            currentcollumn--;

            adding_instructions('/0');
    }
    }

}

void adding_instructions(first_junction){
    instructions[counter] = first_junction;
    counter++;
}

int main(){
	get_places();
    while(matrix[currentrow][currentcollumn] != matrix[endrow][endcollumn]){
        sleep(2);
        finding_route();
    }
    for(int k=0; k<ARRAY_SIZE;k++){

    }

    calculate();

    for(int h = 0; h<4;h++){
        for(int u = 0; u<2;u++){

        }

    }
    return 0;
}
