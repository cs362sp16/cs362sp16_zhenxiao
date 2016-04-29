//test getCost function

#include "dominion.h"
#include "dominion_helpers.h"
//#include "rngs.c"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include "dominion.c"
#define DIE_ON_ASSERT 0

int failed = 0;

int myassert(int b, char* msg){
	if (!b) {
     printf("FAILED ASSERTION: %s\n",msg);
	}
	 else if (b){
		 failed++;
	 }
}

void checkasserts() {
   if (failed!=0) {
     printf ("TEST SUCCESSFULLY COMPLETED.\n");
   }
   else{
	   printf("TEST FAILD. \n");
   }
 }
 
 int main() {
    int i;
	printf("tset start... test getCost function...\n");
	int cardcost[27] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};
	for ( i=0; i<27; i++){
		printf("card need cost %d coins, getCost return cost %d coins \n ", cardcost[i], getCost(i));
		if (cardcost[i]==getCost(i)){
			printf ("TEST SUCCESSFULLY COMPLETED.\n");
		}
		else {
			printf("TEST FAILED");
		}
	}
    
   return 0;
 }