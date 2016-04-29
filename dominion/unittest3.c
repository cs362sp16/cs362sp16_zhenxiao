

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
 void assert_updatacoins(struct gameState *g){
	int p, bouns;
	p = g->whoseTurn;
	bouns = 1;
	g->hand[p][0] = copper;
	g->hand[p][1] = copper;
	g->hand[p][2] = copper;
	g->hand[p][3] = silver;
	g->hand[p][4] = gold;

	updateCoins(p, g, bouns);
	printf("bouns is 1, get copper, silver and gold\n");
	if (g->coins == 9){
		printf("test sucessful\n");
		printf("coin value is %d\n", g->coins);
	}
	else {
		printf("test failed\n");
		printf("coin value is %d\n", g->coins);
	}
 }
 int main() {
    struct gameState *g;
	g = newGame();
	printf("test start... test updateCoins function\n");
    int k[10] = {council_room,village,steward,sea_hag,cutpurse,mine,ambassador,
 	       outpost,baron,adventurer};
 
    int r = initializeGame(2, k, 1, g);
    myassert(r == 0, "No duplicates, 2 players, should succeed");
    myassert (numHandCards(g) == 5, "draw card incorrect");
    
	assert_updatacoins(g);
    
   return 0;
 }