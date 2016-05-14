/* Random test for the card Village*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//set NOISY_TEST to 0 to remove prinftf's from output
#define NOISY_TEST 1
#define MAX_TESTS 1000

 int main(int argc, char* argv[]) {

 	int i, j, new_game, player, hand_count, num_actions;
 	int seed;
 	int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    struct gameState G;

    int isHandCountPass = 1;
    int isNumActionsPass = 1;

    //random number of players
    player = rand() % 2 + 1;
	
	// random number of seed
	if(argv[1]!=NULL)
        seed = atoi(argv[1]);
    else
        seed = rand()%10 + 1;
	//seed = 42;
    //initialize game state
    new_game = initializeGame(player, k, seed, &G);

    //make sure game initialized correctly
    assert(new_game == 0);
    //make sure player has 5 cards
    assert(numHandCards(&G) == 5);
    //make sure player has 1 action
    assert(G.numActions == 1);

    printf("RANDOM TESTING for Village Card\n");
    for(i = 0; i < MAX_TESTS; ++i) {

        //set random values for handCount, deckCount, and discardCount
        G.handCount[player] = rand() % MAX_HAND + 1;
        G.deckCount[player] = rand() % MAX_DECK + 1;
        G.discardCount[player] = rand() % MAX_DECK + 1;

        //fill hand with random cards
        for(j = 0; j < G.handCount[player]; ++j) {
            int randCard = rand() % 10;
            G.hand[player][j] = k[randCard];
        }

        //set random value for numActions
        G.numActions = rand() % MAX_HAND + 1;

        //set values to local variables
        G.whoseTurn = player;
        hand_count = G.handCount[player];
        num_actions = G.numActions;

        //play the villageCard
        //playVillage(&G, 0);
		cardEffect(village, 0, 0, 0, &G, 0, 0);
        //print error messages, if any
        //village card draws a card, then discards one card- difference should be 0
        if(G.handCount[player] != hand_count) {
#if (NOISY_TEST == 1)
            printf("Village Card test (handCount) FAILED for index: %d\n", i);
            printf("hand_count = %d\n", hand_count);
            printf("G.handCount = %d\n", G.handCount[player]);
#endif
            isHandCountPass = 0;
        }
        if(G.numActions != (num_actions+2)) {
#if (NOISY_TEST == 1)
            printf("Village Card test (numActions) FAILED for index: %d\n", i);
            printf("num_actions = %d\n", num_actions);
            printf("G.numActions = %d\n", G.numActions);
#endif
            isNumActionsPass = 0;
        }
    }

    if(isHandCountPass==1) {
        printf("Village Card Test PASSED (handCount)\n");
    }
    else {
        printf("Village Card Test FAILED (handCount)\n");
    }

    if(isNumActionsPass==1) {
        printf("Village Card Test PASSED (numActions)\n");
    }
    else {
        printf("Village Card Test FAILED (numActions)\n");
    }

 	printf("Random Village Card Test Complete!\n");

 	return 0;
 }