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
	
	printf("--------TESTING Council Room card-------------\n\n");
	//If you play it as your action, you can draw 4 extra cards from your draw pile. 
	//You also get one extra buy.  
	//All other players get one more card from their draw pile to play with once it is their turn.
	//Bug doesn't consistently give other players an extra card
	
	//initialize static values of game
	game.phase = 0;
	
	//START RANDOM LOOPS
	int j;
	for(j = 0; j < 900000; j++){
	
		game.numBuys = 1;
	
		//set up random game
		randomGenerator(&game);
	
		//save original game
		struct gameState gameBefore;
		gameBefore = game;
		
		//call card
		int bonus = 0;
		cardEffect(council_room, 0, 0, 0, &game, 0, &bonus); 
		
		//get opponent 
    	int player;
    	if(game.whoseTurn == 0){
    		player = 1;
    	} else {
    		player = 0;
    	}
		
		//number of card in player's hand
		//see if test passed
		char* testresult;
		if (game.handCount[game.whoseTurn] == gameBefore.handCount[game.whoseTurn] + 3) {
			testresult = "PASSED";
		} else {
			testresult = "FAILED";
		}
	
		printf("Iteration %d: Hand count after calling coucil room = %d, expected = %d, %s\n", count, game.handCount[game.whoseTurn], gameBefore.handCount[game.whoseTurn] + 3, testresult);
	
		//number of buys
		//see if test passed
		if (game.numBuys == gameBefore.numBuys + 1) {
			testresult = "PASSED";
		} else {
			testresult = "FAILED";
		}  
	
		printf("Iteration %d: Number of buys after calling coucil room = %d, expected = %d, %s\n", count, game.numBuys, gameBefore.numBuys + 1, testresult);
	
		//number of card in oppnent's hand
		//see if test passed
		if (game.handCount[player] == gameBefore.handCount[player] + 1) {
			testresult = "PASSED";
		} else {
			testresult = "FAILED";
		}
	
		printf("Iteration %d: Oppnent's hand count after calling coucil room = %d, expected = %d, %s\n", count, game.handCount[player], gameBefore.handCount[player] + 1, testresult);
	
		//increase iteration count
		count++;
		
	}
	
	printf("\n\n--------Testing complete-------------\n");
  
    return 0;
}
 