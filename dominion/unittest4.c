//test fullDeckCount() function

#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "dominion.h"
#include "assert.h"
#include "dominion_helpers.h"

int assert_result(int i, int j){
    if(i==j)
        return 1;
    else
        return 0;
}    

int main(){

struct gameState g;
    int k[10] = {council_room,village,steward,sea_hag,cutpurse,mine,ambassador,
 	       outpost,baron,adventurer};
    int result;   

    printf("tset start... test fullDeckCount function");
    initializeGame(2, k, 5, &g);

	result = fullDeckCount(0, 0, &g);	

	if(assert_result(result, 0))
		printf("test successful\n");
	
	else
		printf("test failed\n");
	return 0;
}