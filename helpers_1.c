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

void initializePlayers(struct Player players[], int nPlayers)
{
  char names[][37] = {"MLDG", "yatsfr", "vibe", "winkeuu", "lemon"};
  int i;
  for (i = 0; i < nPlayers; i++)
  {
    strcpy(players[i].username, names[i]);
    players[i].nHand = 0;   // player has 0 hand cards
    players[i].score = 0;   // player has score of 0
    for(int j = 0; j < 7; j++)
    {
      players[i].tank[j] = 0;
    }
  }
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
int loadDeck(struct Deck *deck)
{
  FILE *fptr;
  int i = 0;

  fptr = fopen("mantis.txt", "r");
  if (fptr == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }

  while(fscanf(fptr, " %c | %s %d", &deck->cards[i].front, deck->cards[i].back, &deck->cards[i].points) == 3)
  {
    i++;
  }
  fclose(fptr);

  return i;
}

void shuffleDeck(struct Deck *deck)
{
  int seed;

  initRandom();
  seed = randomInt();
  shuffle(&deck->cards, 84, sizeof(struct Card), seed);
}

displayPlayerCards(struct Player Player[], int nPlayers)
{
  for(int i = 0; i < nPlayers; i++)
  {
    printf("Player %d => [R:%d | O:%d | Y:%d | G:%d | B:%d | I:%d | V:%d ] // %d \n", i+1, Player[i].tank[0], Player[i].tank[1], Player[i].tank[2], Player[i].tank[3], Player[i].tank[4], Player[i].tank[5], Player[i].tank[6], Player[i].score);
  }
}

// Card drawTopCard(Deck *ptrDeck)
// {


//   return; // replace with actual return value
// }


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