/* Random test for card Adventurer*/

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

 	int i, j, new_game, player, num_coins_pre, num_coins_post,
        hand_count, deck_count, discard_count, player_turn;
 	int seed;
 	int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    struct gameState G;

    //random number of players
    player = rand() % 2 + 1;
	//ramdom seed
	if(argv[1]!=NULL)
        seed = atoi(argv[1]);
    else
        seed = rand()%20 + 1;
    //initialize game state
    new_game = initializeGame(player, k, seed, &G);

    int isNumCoinsPass = 1;
    int isDeckCountPass = 1;
    int isPlayerTurn = 1;

    //make sure game initialized correctly
    assert(new_game == 0);
    //make sure player has 5 cards
    assert(numHandCards(&G) == 5);

    printf("RANDOM TESTING for Adventurer Card\n");
    for(i = 0; i < 20; i++) {
        //initialize game state
        new_game = initializeGame(player, k, seed, &G);

        //set random values for handCount, deckCount, and discardCount
        G.handCount[player] = rand() % MAX_HAND + 1;
        G.deckCount[player] = rand() % MAX_DECK + 1;
        G.discardCount[player] = 0;

        //set values to local variables
        G.whoseTurn = player;
        player_turn = G.whoseTurn;

        //fill hand with random cards
		int card;
        for(j = 0; j < G.handCount[player]; j++) {
            //fill hand with random treasure cards
			//card = rand()%27;
            if(rand() % 10 == 5) {
                G.hand[player][j] = copper;
                G.coins++;
            }
            else {
                int randCard = rand() % 10;
                G.hand[player][j] = k[randCard];
            }
        }

        num_coins_pre = G.coins;

        //play adventurer card
		cardEffect(adventurer, 0, 0, 0, &G, 0, 0);
        //print error messages, if any
        //coins are not correct
        if(G.coins != num_coins_pre+2) {
            printf("---------------------------------\nAdventure Card test (coins) FAILED for index: %d\n", i);
            printf("Coins before = %d\n", num_coins_pre);
            printf("G.coins = %d\n", G.coins);
            isNumCoinsPass = 0;
        }
        //player turn is not correct
        if(G.whoseTurn != player_turn) {
            printf("Adventure Card test (whoseTurn) FAILED for index: %d\n", i);
            printf("player_turn = %d\n", player_turn);
            printf("G.whoseTurn = %d\n", G.whoseTurn);
            isPlayerTurn = 0;
        }
    }

    if(isNumCoinsPass==1) {
        printf("Adventure Card Test PASSED (coins)\n");
    }
    else {
        printf("Adventure Card Test FAILED (coins)\n");
    }

    if(isPlayerTurn==1) {
        printf("Adventure Card Test PASSED (whoseTurn)\n");
    }
    else {
        printf("Adventure Card Test FAILED (whoseTurn)\n");
    }

 	printf("Random Adventure Card Test Complete!\n");

 	return 0;
}
