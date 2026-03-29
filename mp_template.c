/******************************************************************************
 *  Description     : This program is a C-based implementation of the Mantis 
 						card game where 3–6 players compete by drawing cards 
						from a shuffled deck loaded from mantis.txt and choosing
						whether to score points or steal cards from opponents. 
						Player information such as usernames, number of wins, and 
						high scores are stored and updated using players.txt . 
						The project demonstrates the use of structures, arrays, 
						file handling, and modular programming while allowing users 
						to configure settings like the winning score and shuffle seed.
 *  Author/s        : <De Guzman, Mavrick>
 *                    <Morin, Eliana>
 *  Section         : <S13A>
 *  Last Modified   : <29/03/2026>
 *  Acknowledgments : <list of references used in the making of this project>
 ******************************************************************************/

/* ----- preprocessor directives ----- */
#include <stdio.h>

#include "defs.h"
#include "helpers_2.c"
#include "helpers_1.c"


/* ----- definitions (i.e., constants, typedefs, structs) ----- */

/* ----- function implementations ----- */



int main()
{
 
  int menuChoice; // user input for main menu
  int numPlayers; // number of players
  int validChoice; // checks if user inputs is valid (for player username)
  int turnChoice; // user input if player wants to score or steal
  int playerTurn = 0; // variable to see who's turn is it
  int winningPoints = 20; // variable for minimum minimum points
  int newPlayer; // user input if new player (add a username) or existing player
  int settingChoice; // user input for setting
  int seed = 0; // for shuffling deck
  int winnerIndex; // index of the winner
  int statsChoice; // user input for statistics
  int i;
	
  struct Player P[6]; // player array
  struct Deck deck; // deck
  struct Card drawnCard; // drawn card
  struct PlayerList playerList; // loaded players from players.txt
  struct PlayerList sortedWins; // sorted player wins (from higest to lowest)
  struct PlayerList sortedScores; // sorted player high scores (from highest to lowest)
	
  initRandom(); // initialize random seed

  /* ----- main manu ----- */
  getPlayerChoice(&menuChoice);
  do{
	
    switch (menuChoice)
	{
  	/* terminate program */
	case 0:
	  break;

	/* start new game */
	case 1:
  
	    numPlayers = getNumberOfPlayers(); // get number of players
	    playerList.nLoadedPlayers = loadPlayers(playerList.players); // load players from players.txt
	    initializePlayers(P, numPlayers, playerList); // initialize players with default values and usernames
	    
	    /* get username for each player */
	    for(i = 0; i < numPlayers; i++)
	    {
	      validChoice = 0; // to check if user picks valid choice
	      do
	      {
	        displayPlayerList(playerList, i); // display player list for user to choose from
	        newPlayer = getPlayerChoiceFromList(i, playerList); // get user choice for player from list
	
	        if(newPlayer == 0) // if user picks 0, then add a new username to the list
	        {
	          addNewPlayer(P, &playerList, i); // add new player to players.txt and player array
	          validChoice = 1;
	        }
	        else
	        {
	          if (checkTakenUsername(P, i, playerList.players[newPlayer - 1].username))
	          {
	            printf("That username is already assigned to another current player. Pick a different player or add a new one.\n");
	          }
	          else
	          {
	            isExistingPlayer(P, playerList, i, newPlayer); // initialize player with existing player username from players.txt
	            validChoice = 1;
	          }
	        }
	      } while (!validChoice);
	    }
	    displayPlayers(P, numPlayers); // displays all the players
	
	
	
	
	    /********************************
	    * THIS IS WHERE THE GAME STARTS *
	    *********************************/
	
	    deck.nCards = loadDeck(&deck); // load deck from mantis.txt
	
	    // // for checking if deck loaded correctly
	    // for(int i = 0; i < deck.nCards; i++)
	    // {
	    //   printf("%c %s %d\n", deck.cards[i].front, deck.cards[i].back, deck.cards[i].points);
	    // }
	
	    shuffleDeck(&deck, seed);
	
	    //   // for checking if deck shuffled correctly
	    //     printf("shuffled deck:\n");
	
	    //   for(int i = 0; i < deck.nCards; i++)
	    // {
	    //   printf("%c | %s %d\n", deck.cards[i].front, deck.cards[i].back, deck.cards[i].points);
	    // }
	
	    displayPlayerCards(P, numPlayers);
	    dealTank(P, numPlayers, &deck);
	
	    //   // for checking if dealt cards  correctly
	    //   for(int i = 0; i < deck.nCards; i++)
	    // {
	    //   printf("%c | %s %d\n", deck.cards[i].front, deck.cards[i].back, deck.cards[i].points);
	    // }
	
	
	      printf("\nAfter dealing tank:\n");
	      displayPlayerCards(P, numPlayers);
	
	
	    /* GAME LOOP */
	  	while(checkIfWin(P, numPlayers, deck, winningPoints) == 0)
	  	{
		    // printf("Remaining cards in deck: %d\n", deck.nCards);
		    drawnCard = drawTopCard(&deck); // draw card
		    displayTopDeck(drawnCard, deck); // display drawn card
		
		    //printf("Top card: %c | %s %d\n", drawnCard.front, drawnCard.back, drawnCard.points);
		    turnChoice = scoreOrSteal(P, drawnCard, playerTurn); // get user choice if score or steam
		    
		    if(turnChoice == 1) // if score
		    {
		      tryToScore(P, drawnCard, playerTurn);
		      displayPlayerCards(P, numPlayers);
		    }
		    else if(turnChoice == 2) // if steal
		    {
		      tryToSteal(P, drawnCard, playerTurn, numPlayers);
		      displayPlayerCards(P, numPlayers);
		    }
		
		    if(playerTurn == numPlayers-1) // if all players has played a turn, reset to player 1 next turn
		    {
		      playerTurn = 0;
		    }
		    else
		    {
		      playerTurn++; // next player's turn
	    	}
	 	 }
	
	  
	 	 winnerIndex = returnWinnerIndex(P, numPlayers, deck); // returns and displays the player index of the winner
		 savePlayerStats(P, &playerList, numPlayers, winnerIndex); // save the stats in playerlist variable
	 	 savePlayerFile(playerList); // save the playerlist variable in the file
	
	  	 getPlayerChoice(&menuChoice); // asks the user for main menu input
	     break;
  
  /* display statistics */
	case 2:
	    playerList.nLoadedPlayers = loadPlayers(playerList.players); // load players
	
	    statsChoice = getStatisticsChoice(); // asks user what statistics to display
	    switch(statsChoice)
		  {
		    case 0:
		      break;
		
		    // displayer player wins 
		    case 1:
		      sortPlayerWins(playerList, &sortedWins); 
		      displayPlayerWins(sortedWins);
		      break;
		
		    // display player high scores
		    case 2:
		      sortPlayerHighScore(playerList, &sortedScores);
		      displayPlayerScores(sortedScores);
		      break;
		
		    default:
		      break;
		  }
	    getPlayerChoice(&menuChoice);
		break;
	
  /* display settings */
	case 3:
    settingChoice = getSettingsChoice();

    switch(settingChoice)
    {
      case 0:
        break;
      
	  // set minimum winning points
      case 1: 
        setWinningPoints(&winningPoints);
        break;
    
      // set shuffle seed
      case 2:
        setShuffleSeed(&seed);
        break;

      default:
        break;
    }
      getPlayerChoice(&menuChoice);
      break;
	
	
	default:
	  break;
	}

}while(menuChoice != 0);

  return 0;
}


/**
 * This is to certify that this project is my/our own work, based on my/our personal
 * efforts in studying and applying the concepts learned. I/We have constructed the
 * functions and their respective algorithms and corresponding code by myself/ourselves.
 * The program was run, tested, and debugged by my/our own efforts. I/We further certify
 * that I/we have not copied in part or whole or otherwise plagiarized the work of other
 * students and/or persons, nor did I employ the use of AI in any part of the deliverable.
 *
 * <student1 full name (De Guzman, Mavrick)> (DLSU ID# 12541907)
 * <student2 full name (last name, first name)> (DLSU ID# <number>)
 */
