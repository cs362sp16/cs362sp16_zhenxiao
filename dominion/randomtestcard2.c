/*random test for card great hall */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[])
{
	int rcard, n, p, new_game;
	int i = 0;
	int seed;
	struct gameState G, testG;
	int k[20] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall, copper, copper, copper, 
		   copper, silver, silver, silver, gold, gold, gold};
	
	if(argv[1]!=NULL)
        seed = atoi(argv[1]);
    else
        seed = rand()%10 + 1;
	//seed = 42;

	printf("Testing great hall card\n");
	
	for (n = 1; n < 1000; n++) {
		
		p = floor(Random() * 2);
		G.whoseTurn = p;
		G.deckCount[p] = floor(Random() * MAX_HAND);
		G.discardCount[p] = 5;
		G.handCount[p] = floor(Random() * MAX_HAND);
		new_game = initializeGame(p, k, seed, &G);
		for(i = 0; i < G.deckCount[p]; i++){
			rcard = floor(Random() * 19);
			G.deck[p][i] = k[rcard];
		}
		for(i = 0; i < G.handCount[p]; i++){
			rcard = floor(Random() * 19);
			G.hand[p][i] = k[rcard];
		}
		for(i = 0; i < G.discardCount[p]; i++){
			rcard = floor(Random() * 19);
			G.discard[p][i] = k[rcard];
		}
		
		memcpy(&testG, &G, sizeof(struct gameState));
		
		int cards = numHandCards(&G);
		int cards1 = numHandCards(&testG);

	
		cardEffect(great_hall, 0, 0, 0, &testG, 0, 0);
	
		if(cards != cards1){
			printf("Failed draw card, Expected: %d, Result: %d\n", cards , cards1);
		}
		else 
			printf("card draw test pass\n");

		if(G.numActions + 1 != testG.numActions){
			printf("Failed action count, Expected action count: %d, Result: %d\n", G.numActions , testG.numActions);
		}
		else 
			printf("action test pass\n");
	}	
	return 0;
}
