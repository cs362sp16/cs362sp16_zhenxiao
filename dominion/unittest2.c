//test card drawcard


#include "dominion.h"
#include "dominion_helpers.h"
//#include "rngs.c"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include "dominion.c"

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
    struct gameState g;
 
 
    int k[10] = {council_room,village,steward,sea_hag,cutpurse,mine,ambassador,
 	       outpost,baron,adventurer};
 
    int r = initializeGame(2, k, 5, &g);
    myassert(r == 0, "No duplicates, 2 players, should succeed");
    myassert (numHandCards(&g) == 5, "draw card incorrect");
    
	printf("after initiallzation, the number of card is %d\n", numHandCards(&g));
	drawCard(0,&g);
	myassert (numHandCards(&g) == 6, "draw card incorrect");
	printf("after drawCard test, the number of card is %d\n", numHandCards(&g));
    checkasserts();
    
   return 0;
 }