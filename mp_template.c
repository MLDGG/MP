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
  struct Player P[6];
  struct Deck deck;
  struct Card drawnCard;



  displayMainMenu();

  do 
  {
    scanf("%d", &nChoice);
  } while (nChoice < 0 || nChoice > 3);

	switch (nChoice)
	{
	case 0:
	  break;
	
	case 1:
	nPlayers = getNumberOfPlayers(); // get number of players
  initializePlayers(P, nPlayers); // initialize players with default values and usernames
	displayPlayers(P, nPlayers); // display players
  getUsername(&P[nPlayers-1]); // get username of new player
  printf("Player %d: %s\n", nPlayers, P[nPlayers-1].username); // display new player (for checking only)
  deck.nCards = loadDeck(&deck); // load deck from mantis.txt

  // // for checking if deck loaded correctly
  // for(int i = 0; i < deck.nCards; i++)
  // {
  //   printf("%c %s %d\n", deck.cards[i].front, deck.cards[i].back, deck.cards[i].points);
  // }

  shuffleDeck(&deck);

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


    printf("After dealing tank:\n");
    displayPlayerCards(P, nPlayers);

  // printf("Remaining cards in deck: %d\n", deck.nCards);
  drawnCard = drawTopCard(&deck);
  printf("\nTop Deck: %s (%d cards remaining in deck)", drawnCard.back, deck.nCards);
  //printf("Top card: %c | %s %d\n", drawnCard.front, drawnCard.back, drawnCard.points);
  nScoreOrSteal = scoreOrSteal(P, drawnCard, 0);
  if(nScoreOrSteal == 1)
  {
    tryToScore(P, drawnCard, 0);
    displayPlayerCards(P, nPlayers);
  }
  else if(nScoreOrSteal == 2)
  {
    /* code */ 
  }

	break;
	
	case 2:
	  break;
	
	case 3:
	  /* code */ 
	  break;
	
	
	default:
	  break;
	}

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
