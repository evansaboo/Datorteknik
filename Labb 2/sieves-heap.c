/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLUMNS 6
int count = 0;

void print_number(int n){
    if(count == COLUMNS){
          printf("\n");
          count = 0;
    }
     printf("%10d ", n);
     count++;   
}

void print_sieves(int n){
    int i;
    int total = n-1; 
    char * pPrime = (char *) malloc(total * sizeof(char));
    
    for(i=0; i < total; i++)        //Alla värden i arrayen är lika med 1
        pPrime[i] = 1;
    
    for(i=2; i <= sqrt(n); i++) // for i = 2, 3, 4, ..., not exceeding ?prime
    {
        if(pPrime[i-2] == 1)       // kollar om prime[i] är true
        { 
            int a = i*i;                               // for j = i2, i2+i, i2+2i, i2+3i, ..., not exceeding prime?:
            while(a <= n){
                pPrime[a-2] = 0;
                a = a + i;
            }
        }  
    }
    int counts = 0;
    int save;
    double totalSave = 0;
    for(i=0; i < total; i++){
        if(pPrime[i] == 1){
        if(i>0){
        totalSave = totalSave + i+2 - save;
        }
        print_number(i+2);
                 counts++;
        save =i+2;
        }
    }
    double a = totalSave/counts;
    printf("%f", (a));
    free(pPrime);
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
      if(argc == 2){
    print_sieves(atoi(argv[1]));
      }
  else
    printf("Please state an interger number.\n");
  return 0;
}