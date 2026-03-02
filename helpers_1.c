/******************************************************************************
 *  Description     : <short description of the file>
 *  Author/s        : <student1 full name (last name, first name)>
 *                    <student2 full name (last name, first name)>
 *  Section         : <your section>
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

#ifndef HELPERS_1_C // Include this to prevent redefinition error
#define HELPERS_1_C // Include this to prevent redefinition error

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "defs.h"


// PROGRAM FLOW

// // displayMainMenu()
// startNewGame()
// displayTopPlayers()
// displaySettings()
// TerminateProgram()

// loadPlayers()
// loadDeck()
// savePlayers()

// // Game Proper
// // getNumberOfPlayers()
// // getUsername()
// shuffleDeck()
// dealCards()
// trytoScore()
// trytoSteal()
// displayGameResults()
// displayStatistics()

// //settings
// setWinningPoints()
// setShuffleSeed()



void displayMainMenu()
{
  printf("Main Menu\n\t [1] New Game \n\t [2] Top Players \n\t [3] Settings \n\t [0] Exit\n");
  printf("Enter option: ");
}


int getNumberOfPlayers()
{
  int nPlayers;
  do
  {
    printf("How many players?(3-6): ");
    scanf("%d", &nPlayers);
  } while (nPlayers < 3 || nPlayers > 6);
  return nPlayers;
}

void displayPlayers(struct Player P[], int nPlayers)
{
	int i;
	
	for(i = 0; i < nPlayers-1; i++)
	{
		printf("P%d: %s\n", i+1, P[i].username);
	}
	
	printf("P%d: ?\n", i+1);

}

void getUsername(struct Player *pPlayer)
{
  char username[37];
  do
  {
    printf("New player username: ");
    scanf("%s", &username);
  } while (strlen(username) > 36);
  strcpy(pPlayer->username, username);
}

// source: https://www.youtube.com/watch?v=XzRyBwu_h48
int loadDeck(struct Card deck[])
{
  FILE *fptr;
  int i = 0;

  fptr = fopen("mantis.txt", "r");
  if (fptr == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }

  while(fscanf(fptr, " %c | %s %d", &deck[i].front, deck[i].back, &deck[i].points) == 3)
  {
    i++;
  }
  fclose(fptr);

  return i;
}

void shuffleDeck(struct Card deck[])
{
  int seed;

  initRandom();
  seed = randomInt();
  shuffle(deck, 84, sizeof(struct Card), seed);
}

// startNewGame()
// {
//   getNumberOfPlayers();
// }









/******************************************************************************
 * NOTE: These functions are placed here in helpers_1.c to demonstrate code
 * modularization across multiple files. You may move them to different files
 * if it better fits your code organization.
 ******************************************************************************/

/**
 * Displays the array of coordinates
 * @param points The array of coordinates to be displayed
 * @param arrSize The size of the array
 */
void displayCoodinates(Coordinate points[], int arrSize)
{
  // NOTE: This file includes defs.h, which provides access to the
  //       Coordinate structure definition.

  for (int i = 0; i < arrSize; i++)
    printf("(%d, %d)  ", points[i].x, points[i].y);

  printf("\n\n");
}

#endif // HELPERS_1_C; Include this to prevent redefinition error