#include<stdio.h>
#include<stdlib.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void randomGenerator(struct gameState *game) {
	
	//set up random hand for the player whose turn it is
	//rand() % (max_number + 1 - minimum_number) + minimum_number
    game->whoseTurn = rand() % (1 + 1 - 0) + 0;
    //add the card we are testing to the player's hand
    game->hand[game->whoseTurn][0] = 7;
    game->handCount[game->whoseTurn] = rand() % (MAX_HAND + 1 - 1) + 1;
    int i;
    for(i = 1; i < game->handCount[game->whoseTurn]; i++) {
    	game->hand[game->whoseTurn][i] = rand() % (16 + 1 - 0) + 0;
    }
    game->deckCount[game->whoseTurn] = rand() % (MAX_DECK + 1 - 0) + 0;
    for(i = 0; i < game->deckCount[game->whoseTurn]; i++) {
    	game->deck[game->whoseTurn][i] = rand() % (16 + 1 - 0) + 0;
    }
    game->discardCount[game->whoseTurn] = rand() % (MAX_DECK + 1 - 0) + 0;
    for(i = 0; i < game->discardCount[game->whoseTurn]; i++) {
    	game->discard[game->whoseTurn][i] = rand() % (16 + 1 - 0) + 0;
    }
    
    //Set up random hand for opponent 
    int player;
    if(game->whoseTurn == 0){
    	player = 1;
    } else {
    	player = 0;
    }    
    game->handCount[player] = rand() % (MAX_HAND + 1 - 0) + 0;
    for(i = 0; i < game->handCount[player]; i++) {
    	game->hand[player][i] = rand() % (16 + 1 - 0) + 0;
    }
    game->deckCount[player] = rand() % (MAX_DECK + 1 - 0) + 0;
    for(i = 0; i < game->deckCount[player]; i++) {
    	game->deck[player][i] = rand() % (16 + 1 - 0) + 0;
    }
    game->discardCount[player] = rand() % (MAX_DECK + 1 - 0) + 0;
    for(i = 0; i < game->discardCount[player]; i++) {
    	game->discard[player][i] = rand() % (16 + 1 - 0) + 0;
    }
} 
 
int main() { 

	//count for testing iterations
	int count = 1;
	
	//set up variables for games
	srand(time(NULL)); 
	int seed = 1000;
	int numPlayers = 2;
	struct gameState game; 
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &game);
	
	printf("--------TESTING Adventurer card-------------\n\n");
	//If you use this card as your action, you keep drawing from your draw pile until you receive 2 treasure cards (copper, sliver, gold). 
	
	//initialize static values of game
	game.phase = 0;
	game.numBuys = 1;
	
	//START RANDOM LOOPS
	int j;
	for(j = 0; j < 900000; j++){
	
		//set up random game
		randomGenerator(&game);
	
		//save original game
		struct gameState gameBefore;
		gameBefore = game;
	
		//count number of treasure cards before playing card
		int treasureCountBefore = 0;
		int i;
		for (i = 0; i < gameBefore.handCount[game.whoseTurn]; i++) {
			if(gameBefore.hand[0][i] == 4 || gameBefore.hand[0][i] == 5 || gameBefore.hand[0][i] == 6) {
				treasureCountBefore++;
			}
		}
	
		//call card
		int bonus = 0;
		cardEffect(adventurer, 0, 0, 0, &game, 0, &bonus); 
	
		//count number of treasure cards after playing card
		int treasureCountAfter = 0;
		for (i = 0; i < game.handCount[game.whoseTurn]; i++) {
			if(game.hand[0][i] == 4 || game.hand[0][i] == 5 || game.hand[0][i] == 6) {
				treasureCountAfter++;
			}
		}
	
		//see if test passed
		char* testresult;
		if (treasureCountAfter == treasureCountBefore + 2) {
			testresult = "PASSED";
		} else {
			testresult = "FAILED";
		}
	
		printf("Iteration %d: Treasure card count after calling adventurer = %d, expected = %d, %s\n", count, treasureCountAfter, treasureCountBefore + 2, testresult);
	
		//increase iteration count
		count++;
		
	}
	
	printf("\n\n--------Testing complete-------------\n");
  
    return 0;
}
 