//test card council_room


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
	}
	 else if (b){
		 failed++;
	 }
}

void checkasserts() {
   if (failed!=0) {
     printf ("TEST  COMPLETED.\n");
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
   
    g.hand[0][0] = council_room;
    int buy = g.numBuys;
    int cards = numHandCards(&g);
	int otherplayercard = g.handCount[g.whoseTurn+1];
	
    printf("test start... test card council_room... \n");
	playCard(0, 1, 0, 0, &g);
	myassert (g.numBuys == buy+1, "buy incorrect");
	printf ("before test, the buy is %d, after test, the buy is %d\n",buy, g.numBuys );
	myassert (numHandCards(&g) == cards+3, "draw card incorrect");
    printf("before test, the number of card for currect player is %d\n",cards);
	printf("After testm the number of card for currect player is %d\n",numHandCards(&g));
	
	printf("before test, the number of other player's card %d\n", otherplayercard);
	printf("After test, the number of other player's card %d\n", g.handCount[g.whoseTurn+1]);
	
    checkasserts();
    
   return 0;
 }