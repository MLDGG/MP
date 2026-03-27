/******************************************************************************
 *  Description     : <short description of the project>
 *  Author/s        : <De Guzman, Mavrick>
 *                    <student2 full name (last name, first name)>
 *  Section         : <S13A>
 *  Last Modified   : <23/02/2026>
 *  Acknowledgments : <list of references used in the making of this project>
 ******************************************************************************/

/* ----- preprocessor directives ----- */
#include <stdio.h>

#include "defs.h"
#include "helpers_1.c"
#include "helpers_2.c"


/* ----- definitions (i.e., constants, typedefs, structs) ----- */

/* ----- function implementations ----- */



int main()
{
 
  int nChoice;
  int nPlayers;
  int nScoreOrSteal;
  int nplayerTurn = 0;
  int gameOver = 0;
  int nWinningPoints = 20;
  int newPlayer;
  int settingChoice;
  int seed = 0;
  int winnerIndex;
  int statsChoice;
  struct Player P[6];
  struct Deck deck;
  struct Card drawnCard;
  struct PlayerList playerList;
  struct PlayerList sortedWins;
  struct PlayerList sortedScores;


  initRandom(); // initialize random seed
  getPlayerChoice(&nChoice);

  do{
	
    switch (nChoice)
	{
	case 0:
	  break;
	
	case 1:
    nPlayers = getNumberOfPlayers(); // get number of players
    playerList.nLoadedPlayers = loadPlayers(playerList.players); // load players from players.txt
    initializePlayers(P, nPlayers, playerList); // initialize players with default values and usernames
    // displayPlayers(P, nPlayers); // display players
    // displayPlayerList(playerList, nPlayers); // display player list for user to choose from
    // newPlayer = getPlayerChoiceFromList(nPlayers, playerList); // get user choice for player from list
    // if(newPlayer == 0)
    // {
    //   addNewPlayer(P, &playerList, nPlayers); // add new player to players.txt and player array
    // }
    // else
    // {
    //   isExistingPlayer(P, playerList, nPlayers, newPlayer); // initialize player with existing player username from players.txt
    // }

    for(int i = 0; i < nPlayers; i++)
    {
      int validChoice = 0;
      do
      {
        displayPlayerList(playerList, i); // display player list for user to choose from
        newPlayer = getPlayerChoiceFromList(i, playerList); // get user choice for player from list

        if(newPlayer == 0)
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

    displayPlayers(P, nPlayers);
    // getUsername(&P[nPlayers-1]); // get username of new player
    // printf("Player %d: %s\n", nPlayers, P[nPlayers-1].username); // display new player (for checking only)

    // THIS IS WHERE THE GAME STARTS

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

    displayPlayerCards(P, nPlayers);
    dealTank(P, nPlayers, &deck);

    //   // for checking if dealt cards  correctly
    //   for(int i = 0; i < deck.nCards; i++)
    // {
    //   printf("%c | %s %d\n", deck.cards[i].front, deck.cards[i].back, deck.cards[i].points);
    // }


      printf("\nAfter dealing tank:\n");
      displayPlayerCards(P, nPlayers);


  // GAME START
  while(checkIfWin(P, nPlayers, deck, nWinningPoints) == 0)
  {
    // printf("Remaining cards in deck: %d\n", deck.nCards);
    drawnCard = drawTopCard(&deck);
    displayTopDeck(drawnCard, deck);

    //printf("Top card: %c | %s %d\n", drawnCard.front, drawnCard.back, drawnCard.points);
    nScoreOrSteal = scoreOrSteal(P, drawnCard, nplayerTurn);
    
    if(nScoreOrSteal == 1)
    {
      tryToScore(P, drawnCard, nplayerTurn);
      displayPlayerCards(P, nPlayers);
    }
    else if(nScoreOrSteal == 2)
    {
      tryToSteal(P, drawnCard, nplayerTurn, nPlayers);
      displayPlayerCards(P, nPlayers);
    }

    if(nplayerTurn == nPlayers-1)
    {
      nplayerTurn = 0;
    }
    else
    {
      nplayerTurn++;
    }
  }

  winnerIndex = returnWinnerIndex(P, nPlayers, deck);
  savePlayerStats(P, &playerList, nPlayers, winnerIndex);
  savePlayerFile(playerList);

    getPlayerChoice(&nChoice);
    break;
    
	case 2:
    playerList.nLoadedPlayers = loadPlayers(playerList.players);

    statsChoice = getStatisticsChoice();
    switch(statsChoice)
  {
    case 0:
      break;

    case 1:
      sortPlayerWins(playerList, &sortedWins);
      displayPlayerWins(sortedWins);
      break;

    case 2:
      sortPlayerHighScore(playerList, &sortedScores);
      displayPlayerScores(sortedScores);
      break;

    default:
      break;
  }
    getPlayerChoice(&nChoice);
	  break;
	
	case 3:
    settingChoice = getSettingsChoice();

    switch(settingChoice)
    {
      case 0:
        break;

      case 1:
        setWinningPoints(&nWinningPoints);
        break;

      case 2:
        setShuffleSeed(&seed);
        break;

      default:
        break;
    }
      getPlayerChoice(&nChoice);
      break;
	
	
	default:
	  break;
	}

}while(nChoice != 0);

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
