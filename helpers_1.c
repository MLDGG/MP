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
#include "interface.c"


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

/**
 * changes color to index for use in isetcolor function
 * @param color the color of the card
 * @return the index of the color for use in isetcolor function
 */
int colorInterface(char color)
{
    int idx;

    switch(color)
    {
        case 'R': idx = 1; break;
        case 'O': idx = 0; break;
        case 'Y': idx = 4; break;
        case 'G': idx = 3; break;
        case 'B': idx = 2; break;
        case 'I': idx = 5; break;
        case 'V': idx = 6; break;
        default:  idx = 0; break;
    }
    return idx;
}

/**
 * Displays the main menu options
 */
void displayMainMenu()
{
  printf("Main Menu\n\t [1] New Game \n\t [2] Top Players \n\t [3] Settings \n\t [0] Exit\n");
  printf("Enter option: ");
}

/**
 * Displays the main menu options and prompts the user to enter a choice
 * @param nChoice pointer to store the user's choice
 */
void getPlayerChoice(int *nChoice)
{
  displayMainMenu();
  do 
  {
    scanf("%d", nChoice);
  } while (*nChoice < 0 || *nChoice > 3);
}

/**
 * Determines the number of players (between 3 and 6)
 * @return The number of players
 */
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

/**
 * Initializes the list of players, wherein each player has 0 hand cards, 0 tank cards, and 0 score, and their player number
 * @param players The player array
 * @param nPlayers The number of players
 */
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


/**
* Displays the players username and player number, with the last player as "?"
* @param P the player array
* @param nPlayers the number of players
 */
void displayPlayers(struct Player P[], int nPlayers)
{
	int i;
	
	for(i = 0; i < nPlayers-1; i++)
	{
		printf("P%d: %s\n", i+1, P[i].username);
	}
	
	printf("P%d: ?\n", i+1);

}

/**
 * gets the username of the new player and updates the player struct with the username
 * @param pPlayers The player array
 */
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
/**
 * loads the deck from mantis.txt 
 * @param deck contains the deck of cards
 * @returns the number of cards in the deck
 */
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

/**
 * shuffles the deck of cards
 * @param deck is a pointer to the deck
 */
void shuffleDeck(struct Deck *deck)
{
  int seed;

  initRandom();
  seed = randomInt();
  shuffle(&deck->cards, 84, sizeof(struct Card), seed);
}

/**
 * displays the player's cards (tank) and score
 * @param Player the player array
 * @param nPlayers the number of players
 */
void displayPlayerCards(struct Player Player[], int nPlayers)
{
  for(int i = 0; i < nPlayers; i++)
  {
    printf("---------------------------------------------------------------------\n");
    iSetColor(I_COLOR_WHITE);
    printf("player %d => [",i+1);
    iSetColor(I_COLOR_RED);
    printf("R:%d | ", Player[i].tank[0]);
    iSetColor(I_COLOR_WHITE);
    printf("O:%d | ", Player[i].tank[1]);
    iSetColor(I_COLOR_YELLOW);
    printf("Y:%d | ", Player[i].tank[2]);
    iSetColor(I_COLOR_GREEN);
    printf("G:%d | ", Player[i].tank[3]);
    iSetColor(I_COLOR_BLUE);
    printf("B:%d | ", Player[i].tank[4]);
    iSetColor(I_COLOR_CYAN);
    printf("I:%d | ", Player[i].tank[5]);
    iSetColor(I_COLOR_PURPLE);
    printf("V:%d ] ", Player[i].tank[6]);
    iSetColor(I_COLOR_WHITE);
    printf("// %d \n", Player[i].score);
    printf("---------------------------------------------------------------------\n");
  }
}

/**
 * draw the top card of the deck(the last card in the array) and decrease the number of cards in the deck by 1
 * @param ptrDeck is a pointer to the deck
 * @returns the drawn card
 */
struct Card drawTopCard(struct Deck *ptrDeck)
{
  struct Card topCard = ptrDeck->cards[ptrDeck->nCards - 1]; // Get the top card
  ptrDeck->nCards--; // Decrease the number of cards in the deck
  return topCard; // Return the drawn card
}

/**
 * adds the drawn card to the player's hand 
 * @param player is the player struct 
 * @param drawnCard is the card drawn from the deck
 * @returns the updated player struct with the drawn card added to the player's hand
 */
struct Player addCardToHand(struct Player player, struct Card drawnCard) // TRY TO MAKE POINTER TO PLAYER STRUCT PARA HINDI NA NEED IRETURN VALUE?
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

/**
 * deals 4 cards to each player (to start game)
 * @param players is the player array
 * @param nPlayers is the number of players
 * @param ptrDeck is a pointer to the deck
 */
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
/**
 * converts the color of the front card to index
 * @param frontCard the front card color
 * @returns the index of the color
 */
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

/**
 * checks if the player has the same color card as the drawn card
 * @param player is the player array
 * @param drawnCard is the card drawn from the deck
 * @param playerIndex is the index of the player in the player array
 * @returns 1 if the player has a card of the same color as the drawn card, 0 otherwise
 */
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

/**
 * displays the drawn card (the top card of the deck) and the number of cards remaining in the deck
 * @param drawnCard is the card drawn from the deck
 * @param deck is the deck of cards
 */
void displayTopDeck(struct Card drawnCard, struct Deck deck)
{
  char color[3];
  int i;
  
  for(i = 0; i < 3; i++)
  {
    color[i] = colorInterface(drawnCard.back[i]);
  }

  printf("\nTop Deck: ");
  iSetColor(color[0]);
  printf("%c", drawnCard.back[0]);
  iSetColor(color[1]);
  printf("%c", drawnCard.back[1]);
  iSetColor(color[2]);
  printf("%c", drawnCard.back[2]);
  iSetColor(I_COLOR_WHITE);
  printf(" (%d cards remaining in deck)\n\n", deck.nCards);

  // printf("\nTop Deck: %s (%d cards remaining in deck)\n\n", drawnCard.back, deck.nCards);
}

/**
 * prompts the player to choose whether to score or steal
 * @param player is the player array
 * @param drawnCard is the card drawn from the deck
 * @param playerIndex is the index of the player in the player array
 * @returns 1 if the player chooses to score, 2 if the player chooses to steal
 */
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

  printf("\n");

  return choice;
}

/**
 * reveals the card's front color and point value, checks if the player has the same color card as the drawn card,
 * if player has the same color card, all those color card are added to score pile. score is updated based on the 
 * number of points of the drawn card and the number of same color cards in the player's hand. 
 * 
 * if player does not have the same color card, the drawn card is added to the player's hand (tank)
 * 
 * @param player is the player array
 * @param drawnCard is the card drawn from the deck
 * @param playerIndex is the index of the player in the player array
 */
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
    printf("- +%d points to Player %d's Score Pile!\n\n", drawnCard.points * player[playerIndex].tank[colorIndex], playerIndex+1);
    player[playerIndex].tank[colorIndex] = 0;
  }
  else
  {
    printf("Resolving turn for Player %d...\n", playerIndex+1);
    printf("- Drawn card revealed: %c (%d pt/s)!\n", drawnCard.front, drawnCard.points);
    printf("- Player %d has no %c cards...\n", playerIndex+1, drawnCard.front);
    printf("- Adding drawn card to Player %d's tank\n\n", playerIndex+1);
    player[playerIndex] = addCardToHand(player[playerIndex], drawnCard);
  }
}

/**
 * prompts the player to choose which player to steal from
 * @param player is the player array
 * @param playerIndex is the index of the player in the player array
 * @param nPlayers is the number of players
 * @returns the player number to steal from (example: returns 5 if player 5 is chosen to be stolen from)
 * (to get the index of the player to steal from, subtract 1 from the returned value)
 */
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


/**
 * gets user input for which player to steal from, checks if the chosen player has the same color card as the drawn card,
 * if the chosen player has the same color card, all those color card are added to the stealing player's tank.
 * if the chosen player does not have the same color card, the drawn card is added to the chosen player's hand (tank)
 * @param player is the player array
 * @param drawnCard is the card drawn from the deck
 * @param playerIndex is the index of the player's turn in the player array
 * @param nPlayers is the number of players
 */
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
    printf("- +%d cards to Player %d's tank!\n\n", player[nPlayerToStealFrom-1].tank[colorIndex], playerIndex+1);
    player[playerIndex].tank[colorIndex] += player[nPlayerToStealFrom-1].tank[colorIndex];
    player[nPlayerToStealFrom-1].tank[colorIndex] = 0;
  }
  else
  {
    printf("Resolving turn for Player %d...\n", playerIndex+1);
    printf("- Drawn card revealed: %c (%d pt/s)!\n", drawnCard.front, drawnCard.points);
    printf("- Player %d has no %c cards...\n", nPlayerToStealFrom, drawnCard.front);
    printf("- Adding drawn card to Player %d's tank\n\n", nPlayerToStealFrom);
    player[nPlayerToStealFrom-1] = addCardToHand(player[nPlayerToStealFrom-1], drawnCard);
  }

}

/**
 * check if a player has a score of 20 or more, or if deck is empty
 * @param player is the player array
 * @param nPlayers is the number of players
 * @param deck is the deck of cards
 * @returns 1 if a player has a score of 20 or more, or if deck is empty, 0 otherwise
 */
int checkIfWin(struct Player player[], int nPlayers, struct Deck Deck, int nWinningPoints)
{
  int i;
  int bool = 0;
  for(i = 0; i < nPlayers; i++)
  {
    if(player[i].score >= nWinningPoints || Deck.nCards == 0)
    {
      bool = 1;
    }
  }
  return bool;
}

/**
 * determines the winner of the game by checking which player has the highest score
 * @param player is the player array
 * @param nPlayers is the number of players
 * @param deck is the deck of cards
 * @returns the index of the winning player in the player array
 */
int returnWinnerIndex(struct Player player[], int nPlayers, struct Deck deck)
{
  int i;
  int winnerIndex = 0;
  for(i = 0; i < nPlayers; i++)
  {
    if(player[i].score > player[winnerIndex].score)
    {
      winnerIndex = i;
    }
  }

  printf("Player %d wins with a score of %d points!\n\n", winnerIndex+1, player[winnerIndex].score);

  return winnerIndex;
}

/**
 * prompts user to set minimum number of points required to win the game
 * @param nWinningPoints pointer to store the minimum number of points required to win the game
 */
void setWinningPoints(int *nWinningPoints)
{
  printf("Set minimum number of points required to win the game: ");
  scanf("%d", nWinningPoints); 

  while(*nWinningPoints <= 0)
  {
    printf("Invalid input. Please enter a positive integer: ");
    scanf("%d", nWinningPoints);
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