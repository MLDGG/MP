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
  struct Player P[6];
  struct Card deck[84];
  	strcpy(P[0].username, "MLDG");
	  strcpy(P[1].username, "yatsfr");
	



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
	nPlayers = getNumberOfPlayers();
	displayPlayers(P, nPlayers);
  getUsername(&P[nPlayers-1]);
  printf("Player %d: %s\n", nPlayers, P[nPlayers-1].username);
  loadDeck(deck);
  for(int i = 0; i < 75; i++)
  {
    printf("%c | %s %d\n", deck[i].front, deck[i].back, deck[i].points);
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
