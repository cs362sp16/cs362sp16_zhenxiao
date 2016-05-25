
//#include "rngs.c"
//#include "dominion.c"
#include "dominion.h"
#include "rngs.h"
#include "interface.h"
#include "interface.c"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int checkcard(int k[], int card){
	int i, j;
	
	int check = 0;
	for(i = 0; i < 10; i++){
		card = (rand() % 20) + adventurer;
		for( j = 0; j < i; j++){
			if(card == k[j]){
				check = 1;
				break;
			}
			else
				check = 0;
		}
		if(check == 1)
			i--;
		else
			k[i] = card;
	}
	return k;
}

void createdcard(int *k, char *cardName){
	int i;
	for(i = 0; i < 10; i++){
		cardNumToName(k[i], cardName);
		printf("%s\n", cardName);
	}
}

int winnerplayer(struct gameState *G, int *getWin){
	int i, winner;
	for(i = 0; i < G->numPlayers; i++){
		printf("Player %d has a score of: %d\n", i, scoreFor(i, G));
		if(getWin[i] == 1){
			winner = i ;
		}
	}
	return winner;
}

int randomplayers(){
	int players;
	players = (rand() % 3) + 2;
	return players;
}

void testgame(struct gameState *G, char *cardName, int init, int *k){
	int i, coins, curPlayer;
	int actionCard=0;
	int curCard;
	int card;
	int cardLocation;
	while(!isGameOver(G)){
		curPlayer = G->whoseTurn;
		printf("  Player start to play:  %d \n", curPlayer);
		cardLocation = 0;

		actionCard = 0;
		for(i = 0; i < numHandCards(G); i++){
			if(handCard(i, G) < treasure_map && handCard(i, G) >= adventurer
					&& handCard(i, G) != feast && handCard(i, G) != tribute){
				actionCard = i;
				break;
			}
		}

		printf("Start action stage\n");
		while(G->numActions > 0 && actionCard != 0){
			curCard = handCard(i, G);
			cardNumToName(curCard, cardName);

			init = playCard(actionCard, -1, -1, -1, G);

			if(init == -1){
				discardCard(cardLocation, curPlayer, G, 0);
			}
			else{
				printf("Played card: %s, %d\n", cardName, curCard);
			}

			if(G->numActions <= 0){
				printf("no action, action over\n");
				break;
			}

			for(i = actionCard; i < numHandCards(G); i++){
				if(handCard(i, G) < treasure_map && handCard(i, G) >= adventurer
						&& handCard(i, G) != feast && handCard(i, G) != tribute){
					actionCard = i;
					break;
				}
				else
					actionCard = 0;
			}
		}

		printf("Buy card stage \n");
		coins = 0;
		for(i = 0; i < numHandCards(G); i++){
			if(handCard(i, G) == copper)
				coins++;
			else if(handCard(i, G) == silver)
				coins = coins + 2;
			else if(handCard(i, G) == gold)
				coins = coins + 3;
		}
		while(G->numBuys > 0 && coins > 0){
			do{
				init= rand() % 2;
				cardLocation = rand() % 10;

				if(init)
					card = k[cardLocation];
				else
					card = rand() % treasure_map;
			}while(buyCard(card, G) != 0);

			cardNumToName(card, cardName);
			printf("Buying card: %s\n", cardName);
		}
		printf("Buy over\n");
		printf("End turn\n");
		endTurn(G);
	}
}

int main(int argc, char *argv[]){
	srand(time(NULL));
	int card, players, seed, init ;
	struct gameState *G = newGame();
	int k[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

	int winner;
	char cardName[20];

	int getWin[4];

	if(argv[1] !=NULL){
		seed = atoi(argv[1]);
	}
	else{
		seed = rand()%10 + 1;
	}
	k[10] = checkcard(k, card);

	printf("    Test start  \n");
	printf("randomly created kingdom cards: \n");
	createdcard(k, cardName);

	players = randomplayers();
	G->numPlayers = players;

	init = initializeGame(players, k, seed, G);
	if(init == -1)
		printf("Initialize game failed\n");
	
	testgame(G, cardName, init, k);

	getWinners(getWin, G);
	printf("\n print out scores\n\n");
	
	winner = winnerplayer(G, getWin);

	printf("The winner player is : %d\n", winner);

	printf("Game Over\n\n");
}