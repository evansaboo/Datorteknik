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
    int prime[n-2];
    for(i=0; i <= n-2; i++)        //Alla värden i arrayen är lika med 1
        prime[i] = 1;
    
    for(i=2; i <= sqrt(n); i++) // for i = 2, 3, 4, ..., not exceeding ?prime
    {
        if(prime[i-2] == 1)       // kollar om prime[i] är true
        { 
            int a = i*i;                               // for j = i2, i2+i, i2+2i, i2+3i, ..., not exceeding prime?:
            while(a < n){
                prime[a-2] = 0;
                a = a + i;
            }
        }  
    }
    for(i=0; i <= n-2; i++){
        if(prime[i] == 1)
        print_number(i+2);
    }   
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