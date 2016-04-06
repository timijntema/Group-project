#include "roosterfuncties.c"
int matrix[7][10] ={     {0,1,0,1,0,1,0,1,0},
                                {1,4,1,4,1,5,1,4,1},
                                {0,0,0,1,0,1,0,1,0},
                                {1,4,1,4,1,4,1,4,1},
                                {0,1,0,1,0,1,0,1,0},
                                {1,4,1,4,1,4,1,4,1},
                                {0,2,0,1,0,1,0,1,0}};

task main()
{
	get_places();
    while(matrix[currentrow][currentcollumn] != matrix[endrow][endcollumn]){
        sleep(2);
        finding_route();
    }


    calculate();

}
