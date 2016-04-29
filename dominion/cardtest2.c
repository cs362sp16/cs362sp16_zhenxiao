//test card village

#include "dominion.h"
#include "dominion_helpers.h"
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
	 if (b){
		 failed+1;
	 }
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
 
 
    int k2[10] = {council_room,village,steward,sea_hag,cutpurse,mine,ambassador,
 	       outpost,baron,adventurer};
 
    int r = initializeGame(2, k2, 5, &g);
    myassert(r == 0, "No duplicates, 2 players, should succeed");
   
    g.hand[0][0] = village;
    int action = g.numActions;
	int cards = numHandCards(&g);
	
	printf("test start... test card village... \n");
	playCard(0, 0, 0, 0, &g);
	myassert (g.numActions == action+2, "action incorrect");
	printf ("before test, the action is %d, after test, the action is %d\n",action, g.numActions );
	myassert (numHandCards(&g) == cards, "draw card incorrect");
	printf("before test, the number of card for currect player is %d\n",cards);
	printf("After test the number of card for currect player is %d\n",numHandCards(&g));
	
    checkasserts();
    return 0;
 }