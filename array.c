#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h>
#define ARRAY_SIZE 8

int array(int s[]){

int n;
int i;
int m;
// keuz uit random patroon of zelf invoeren
printf("wilt u zelf in vullen[1] of random[2]:   ");
scanf("%d",&n);
// het zelf invoeren van patroon 
    if(n==1)
        {
        printf("voer in array van 1 en 0\n");
            for(i=0;i<8;i++)
                {
                    scanf("%d",&s[i]);
                    
                }
        }
        //het random genereren van een patroon
        else if( n==2)
        {  
            srand (time(NULL));
            for(i=0;i<5;i++)
                    {
                        m = rand() % 7  ;
                                s[m]=1;
                     }
        }       
return 0;
}



int main(){
int s[ARRAY_SIZE] = { 0,0,0,0,0,0,0,0};
int i;
array(s);
for(i=0;i<8;i++)
                {
                    printf("%d",s[i]);
                }
return 0;
}   