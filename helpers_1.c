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
    players[i].playerNum = i+1; // player number (1-6)
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
    scanf("%s", username);
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

void displayPlayerCards(struct Player Player[], int nPlayers)
{
  for(int i = 0; i < nPlayers; i++)
  {
    printf("Player %d => [R:%d | O:%d | Y:%d | G:%d | B:%d | I:%d | V:%d ] // %d \n", i+1, Player[i].tank[0], Player[i].tank[1], Player[i].tank[2], Player[i].tank[3], Player[i].tank[4], Player[i].tank[5], Player[i].tank[6], Player[i].score);
  }
}

struct Card drawTopCard(struct Deck *ptrDeck)
{
  struct Card topCard = ptrDeck->cards[ptrDeck->nCards - 1]; // Get the top card
  ptrDeck->nCards--; // Decrease the number of cards in the deck
  return topCard; // Return the drawn card
}


struct Player addCardToHand(struct Player player, struct Card drawnCard)
{
  switch(drawnCard.front)
  {
    case 'R':
      player.tank[0]++;
      break;
    case 'O':
      player.tank[1]++;
      break;
    case 'Y':
      player.tank[2]++;
      break;
    case 'G':
      player.tank[3]++;
      break;
    case 'B':
      player.tank[4]++;
      break;
    case 'I':
      player.tank[5]++;
      break;
    case 'V':
      player.tank[6]++;
      break;
  }
  return player;
}

void dealTank(struct Player players[], int nPlayers, struct Deck *ptrDeck)
{
  int i;
  int j;
  struct Card drawnCard;

  for(i = 0; i < nPlayers; i++)
  {
    for( j = 0; j < 4; j++)
    {
      drawnCard = drawTopCard(ptrDeck);
      players[i] = addCardToHand(players[i], drawnCard);
    }
  }
}

int colorToIndex(char frontCard)
{
    int idx;

    switch(frontCard)
    {
        case 'R': idx = 0; break;
        case 'O': idx = 1; break;
        case 'Y': idx = 2; break;
        case 'G': idx = 3; break;
        case 'B': idx = 4; break;
        case 'I': idx = 5; break;
        case 'V': idx = 6; break;
        default:  idx = 0; break;
    }
    return idx;
}

int checkIfColorExist(struct Player player[], struct Card drawnCard, int playerIndex)
{
  int bool = 0;
  int colorIndex = colorToIndex(drawnCard.front);
  if(player[playerIndex].tank[colorIndex] > 0)
  {
    bool = 1;
  }
  return bool;
}
void displayTopDeck(struct Card drawnCard, struct Deck deck)
{
  printf("\nTop Deck: %s (%d cards remaining in deck)", drawnCard.back, deck.nCards);
}

int scoreOrSteal(struct Player player[], struct Card drawnCard, int playerIndex)
{
  int choice;
  do
  {
    printf("Player %d, what would you like to do?\n", playerIndex+1);
    printf("\t[1] Score\n \t[2] Steal\n");
    printf("Enter option: ");
    scanf("%d", &choice);
  } while (choice < 1 || choice > 2);
  return choice;
}

void tryToScore(struct Player player[], struct Card drawnCard, int playerIndex)
{
  int colorIndex;

  colorIndex = colorToIndex(drawnCard.front);

  if(checkIfColorExist(player, drawnCard, playerIndex) == 1)
  {
    printf("Resolving turn for Player %d...\n", playerIndex+1);
    printf("- Drawn card revealed: %c (%d pt/s)!\n", drawnCard.front, drawnCard.points);
    printf("- Player %d has (%d) %c card/s worth a total of  (%d) points!\n", playerIndex+1, player[playerIndex].tank[colorIndex], drawnCard.front, drawnCard.points * player[playerIndex].tank[colorIndex]);
    player[playerIndex].tank[colorIndex]++;
    player[playerIndex].score += drawnCard.points * player[playerIndex].tank[colorIndex];
    printf("- +%d points to Player %d's Score Pile!\n", drawnCard.points * player[playerIndex].tank[colorIndex], playerIndex+1);
    player[playerIndex].tank[colorIndex] = 0;
  }
  else
  {
    printf("Resolving turn for Player %d...\n", playerIndex+1);
    printf("- Drawn card revealed: %c (%d pt/s)!\n", drawnCard.front, drawnCard.points);
    printf("- Player %d has no %c cards...\n", playerIndex+1, drawnCard.front);
    printf("- Adding drawn card to Player %d's tank\n", playerIndex+1);
    player[playerIndex] = addCardToHand(player[playerIndex], drawnCard);
  }
}

// IMPROVE THIS FUNCTION 
int getPlayerToSteal(struct Player player[], int playerIndex, int nPlayers)
{
  int i;
  int j = 1;
  int nChoice;
  int index[nPlayers-1]; // store player number to steal from


  printf("\nWho would you like to steal from?\n");
  for(i = 0; i < nPlayers; i++)
  {
    if(i != playerIndex)
    {
      printf("\t[%d] Player %d\n", j, i+1);
      index[j-1] = i+1; 
      j++;
    }
  }

  // // FOR CHECKING IF INDEXED CORRECTLY
  // for(i = 0; i < nPlayers-1; i++)
  // {
  //   printf("[%d] Player %d\n", i, index[i]);
  // }

  do
  {
    printf("Enter option: ");
    scanf("%d", &nChoice);
  } while (nChoice < 1 || nChoice > nPlayers-1);

  printf("player %d was chosen to be stolen from\n", index[nChoice-1]);

  return index[nChoice-1]; // player number to steal from (minus 1 to match array index)
}

void tryToSteal(struct Player player[], struct Card drawnCard, int playerIndex, int nPlayers)
{
  int colorIndex;
  int nPlayerToStealFrom;

  nPlayerToStealFrom = getPlayerToSteal(player, playerIndex, nPlayers); // get index of player to steal from
  colorIndex = colorToIndex(drawnCard.front);

  if(checkIfColorExist(player, drawnCard, nPlayerToStealFrom-1) == 1)
  {
    printf("Resolving turn for Player %d...\n", playerIndex+1);
    printf("- Drawn card revealed: %c (%d pt/s)!\n", drawnCard.front, drawnCard.points);
    printf("- Player %d has (%d) %c card/s\n", nPlayerToStealFrom, player[nPlayerToStealFrom-1].tank[colorIndex], drawnCard.front);
    player[nPlayerToStealFrom-1].tank[colorIndex]++;
    printf("- +%d points to Player %d's Score Pile!\n", drawnCard.points * player[playerIndex].tank[colorIndex], playerIndex+1);
    player[playerIndex].tank[colorIndex] += player[nPlayerToStealFrom-1].tank[colorIndex];
    player[nPlayerToStealFrom-1].tank[colorIndex] = 0;
  }
  else
  {
    printf("Resolving turn for Player %d...\n", playerIndex+1);
    printf("- Drawn card revealed: %c (%d pt/s)!\n", drawnCard.front, drawnCard.points);
    printf("- Player %d has no %c cards...\n", nPlayerToStealFrom, drawnCard.front);
    printf("- Adding drawn card to Player %d's tank\n", nPlayerToStealFrom);
    player[nPlayerToStealFrom-1] = addCardToHand(player[nPlayerToStealFrom-1], drawnCard);
  }

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