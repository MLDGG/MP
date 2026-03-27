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
 * @param playerList The list of players loaded from players.txt
 */
void initializePlayers(struct Player players[], int nPlayers, struct PlayerList playerList)
{
  int i;
  for (i = 0; i < nPlayers; i++)
  {
    strcpy(players[i].username, ""); 

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
* Displays the players username and player number
* @param P the player array
* @param nPlayers the number of players
*/
void displayPlayers(struct Player P[], int nPlayers)
{
	int i;
	
	for(i = 0; i < nPlayers; i++)
	{
		printf("P%d: %s\n", i+1, P[i].username);
	}
}

/**
* Displays the player username and player number
* @param P the player array
* @param playerIndex contains the current player index
*/
void displayPlayer(struct Player P[], int playerIndex)
{
		printf("P%d: %s\n", playerIndex + 1, P[playerIndex].username);
}

/**
* Displays the list of players from players.txt for the user 
*to choose from, with  the option to add a new player as option 0
* @param playerList the list of players loaded from players.txt
* @param playerIndex is the current player index
*/
void displayPlayerList(struct PlayerList playerList, int playerIndex)
{
  int i;
  int j = 1;

  printf("\nSelect Player %d: \n", playerIndex + 1);
  printf("[0] <Add new Player>\n");
  for(i = 0; i < playerList.nLoadedPlayers; i++)
  {
    printf("[%d] %s\n", j, playerList.players[i].username);
    j++;
  }
}

/**
* Get user input for player choice from the displayed player list
* 
* @param nPlayers the number of players
* @param playerList the list of players loaded from players.txt
* @return the user's choice
*/
int getPlayerChoiceFromList(int nPlayers, struct PlayerList playerList)
{
  int choice;
  do
  {
    printf("Enter option: ");
    scanf("%d", &choice);
  } while (choice < 0 || choice > playerList.nLoadedPlayers + 1);

  return choice;
}

/**
* if user picks from the existing list of players, initialize the new player with the existing player's username from players.txt
* @param P the player array
* @param playerList the list of players loaded from players.txt
* @param playerIndex contains the current player index
* @param choice the user's choice for player username from the displayed player list
*/
void isExistingPlayer(struct Player P[], struct PlayerList playerList, int playerIndex, int choice)
{
 strcpy(P[playerIndex].username, playerList.players[choice - 1].username);
 printf("Player %d: %s\n", playerIndex + 1, P[playerIndex].username);
}

/**
* checks if a username is already taken
* @param P the player array
* @param playerIndex contains the current player index
* @param username is an array containing the username to be checked
*/
int checkTakenUsername(struct Player P[], int playerIndex, char username[])
{
  int found = 0;

  for (int i = 0; i < playerIndex; i++)
  {
    if (strcmp(P[i].username, username) == 0)
    {
      found = 1;
    }
  }
  return found;
}

/**
* checks if a username will be duplicated in the list of players
* @param playerList the list of players loaded from players.txt
* @param username contains the username to be checked
*/
int checkPlayerListUsername(struct PlayerList *playerList, char username[])
{
  int found = 0;
  for (int i = 0; i < playerList->nLoadedPlayers; i++)
  {
    if (strcmp(playerList->players[i].username, username) == 0)
    {
      found = 1;
    }
  }
  return found;
}

/**
 * gets the username of the new player
 * @param P the player array
 * @param playerIndex contains the current player index
 * @param playerList is the list of players loaded from players.txt
 * @param username is an array where the username will be stored
 */
void getUsername(struct Player P[], int playerIndex, struct PlayerList *playerList, char username[])
{
  do
  {
    printf("New player username: ");
    scanf("%36s", username);

    if (strlen(username) == 0)
    {
      printf("Username cannot be empty. Try again.\n");
    }
    else if (checkTakenUsername(P, playerIndex, username))
    {
      printf("That username is already taken by another current player. Please choose a different one.\n");
      username[0] = '\0';
    }
    else if (checkPlayerListUsername(playerList, username))
    {
      printf("That username already exists in the saved player list. Please choose a different one.\n");
      username[0] = '\0';
    }
  } while (strlen(username) == 0 || strlen(username) > 36);
}

/**
 * add new player and add it to the list of players.
 * @param P the player array
 * @param playerList is the list of players loaded from players.txt
 * @param playerIndex contains the current player index
 */
void addNewPlayer(struct Player P[], struct PlayerList* playerList, int playerIndex)
{
  FILE *fptr;

  getUsername(P, playerIndex, playerList, P[playerIndex].username); // get unique username for new player 
  printf("Player %d: %s\n", playerIndex + 1, P[playerIndex].username);

  fptr = fopen("players.txt", "a");
  if (fptr == NULL)
  {
    printf("File does not exist!\n");
  }

  fprintf(fptr, "\n%s %d %d", P[playerIndex].username, 0, 0); // adds new player to the file
  fclose(fptr);

  if (playerList != NULL) // updates playerList
  {
    strcpy(playerList->players[playerList->nLoadedPlayers].username, P[playerIndex].username);
    playerList->players[playerList->nLoadedPlayers].numWins = 0;
    playerList->players[playerList->nLoadedPlayers].highScore = 0;
    playerList->nLoadedPlayers++;
  }
}



/**
* loads the players from players.txt and returns the number of players loaded
* @param P the player array
*/
int loadPlayers(struct Player players[])
{
  FILE *fptr;
  int i = 0;

  fptr = fopen("players.txt", "r");
  if (fptr == NULL)
  {
    printf("File does not exist!\n");
  }

  while(fscanf(fptr, " %s %d %d", players[i].username, &players[i].numWins, &players[i].highScore) == 3)
  {
    i++;
  }
  fclose(fptr);
  return i;
}

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
    printf("File does not exist!\n");
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
 * @param seed the seed for the random number generator
 */
void shuffleDeck(struct Deck *deck, int seed)
{
  if(seed == 0)
  {
    seed = randomInt();
  }
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
 * draw the top card of the deck(index 0) and decrease the number of cards in the deck by 1
 * @param ptrDeck is a pointer to the deck
 * @returns the drawn card
 */
struct Card drawTopCard(struct Deck *ptrDeck)
{
   int i;

  struct Card topCard = ptrDeck->cards[0]; // Get the top card
  // Shift the remaining cards up
  for (int i = 0; i < ptrDeck->nCards - 1; i++)
  {
    ptrDeck->cards[i] = ptrDeck->cards[i + 1];
  }
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
    player[playerIndex].tank[colorIndex]++; // Add card to player hand
    player[playerIndex].score += drawnCard.points * player[playerIndex].tank[colorIndex]; // calculate score
    printf("- +%d points to Player %d's Score Pile!\n\n", drawnCard.points * player[playerIndex].tank[colorIndex], playerIndex+1);
    player[playerIndex].tank[colorIndex] = 0; //discard scored cards
  }
  else
  {
    printf("Resolving turn for Player %d...\n", playerIndex+1);
    printf("- Drawn card revealed: %c (%d pt/s)!\n", drawnCard.front, drawnCard.points);
    printf("- Player %d has no %c cards...\n", playerIndex+1, drawnCard.front);
    printf("- Adding drawn card to Player %d's tank\n\n", playerIndex+1);
    player[playerIndex] = addCardToHand(player[playerIndex], drawnCard); // add card to hand
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

  printf("player %d was chosen to be stolen from\n\n", index[nChoice-1]);

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
  colorIndex = colorToIndex(drawnCard.front); //get index of card color in tank

  if(checkIfColorExist(player, drawnCard, nPlayerToStealFrom-1) == 1) // if the drawn card color exists in the tank of the person you are stealing from
  {
    printf("Resolving turn for Player %d...\n", playerIndex+1); 
    printf("- Drawn card revealed: %c (%d pt/s)!\n", drawnCard.front, drawnCard.points);
    printf("- Player %d has (%d) %c card/s\n", nPlayerToStealFrom, player[nPlayerToStealFrom-1].tank[colorIndex], drawnCard.front);
    player[nPlayerToStealFrom-1].tank[colorIndex]++; //add card to the player you are stealing from
    printf("- +%d cards to Player %d's tank!\n\n", player[nPlayerToStealFrom-1].tank[colorIndex], playerIndex+1); 
    player[playerIndex].tank[colorIndex] += player[nPlayerToStealFrom-1].tank[colorIndex]; // add all cards from the person you are stealing from to the stealer
    player[nPlayerToStealFrom-1].tank[colorIndex] = 0; // stolen player now has zero of that card color
  }
  else //if stolen player has no card color of the drawn card
  {
    printf("Resolving turn for Player %d...\n", playerIndex+1);
    printf("- Drawn card revealed: %c (%d pt/s)!\n", drawnCard.front, drawnCard.points);
    printf("- Player %d has no %c cards...\n", nPlayerToStealFrom, drawnCard.front);
    printf("- Adding drawn card to Player %d's tank\n\n", nPlayerToStealFrom);
    player[nPlayerToStealFrom-1] = addCardToHand(player[nPlayerToStealFrom-1], drawnCard); //add drawn card to player to steal from
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
/**
 * prompts the user to set shuffle seed
 * @param seed contains the shuffle seed
 */
void setShuffleSeed(int *seed)
{
  printf("set shuffle seed (0 for random): ");
  scanf("%d", seed);
}

/**
 * displays settings interface
 */
void displaySettings()
{
  printf("Settings\n\t[1] Set Winning Points\n\t[2] Set Shuffle Seed\n\t[0] Back to Main Menu\n");
}

/**
 * get user's input for settings choice 
 */
int getSettingsChoice()
{
  int nChoice;
  displaySettings();
  do 
  {
    printf("Enter option: ");
    scanf("%d", &nChoice);
  } while (nChoice < 0 || nChoice > 2);
  return nChoice;
}

/**
 * saves player stats (number of wins and highest score) in playerList
 * @param player contains the array of players ingame
 * @param playerList contains the list of players loaded using players.txt
 * @param nplayers is the number of players playing 
 * @param winnerIndex is the index of the player who won the game
 */
void savePlayerStats(struct Player player[], struct PlayerList* playerList, int nPlayers, int winnerIndex)
{
  int i;
  int j;

  playerList->nLoadedPlayers = loadPlayers(playerList->players);

  // iterate through eeach players that are playing
  for(i = 0; i < nPlayers; i++) 
  {
    // iterate through the player list
    for(j = 0; j < playerList->nLoadedPlayers; j++)
    {
      if(strcmp(player[i].username, playerList->players[j].username) == 0) //find player in playerlist
      {
          if(player[i].score > playerList->players[j].highScore)// check if score is greater than previous high score
          {
            playerList->players[j].highScore = player[i].score; // update high score if current score is higher than previous high score
          }
          if(i == winnerIndex)
          {
            playerList->players[j].numWins++; // update number of wins for the player if they are the winner
          }
      }
    }
  }

}

/**
 * saves the player stats in the players.txt file
 * @param PlayerList contains the list of players to be saved in the file
 */
void savePlayerFile(struct PlayerList PlayerList)
{
  FILE *fptr;
  int i;

  fptr = fopen("players.txt", "w");
  if (fptr == NULL)
  {
    printf("File does not exist!\n");
  }

  for (i = 0; i < PlayerList.nLoadedPlayers; i++)
  {
    fprintf(fptr, "%s %d %d\n", PlayerList.players[i].username, PlayerList.players[i].numWins,PlayerList.players[i].highScore);
  }

  fclose(fptr);

}


/**
 * sorts PlayerWins in descending order
 * @param PlayerList contains the list of player information
 * @param sorted contains the sorted PlayerList 
 */
void sortPlayerWins(struct PlayerList PlayerList, struct PlayerList* sorted)
{
  int i, j, max;
  struct Player temp;

  *sorted = PlayerList;
  for(i = 0; i < sorted->nLoadedPlayers - 1; i++)
  {
    max = i;
    for(j = i+1; j < sorted->nLoadedPlayers; j++)
    {
      if(sorted->players[max].numWins < sorted->players[j].numWins)
      {
        max = j;
      }
    }
    if(i != max)
    {
      temp = sorted->players[i];
      sorted->players[i] = sorted->players[max];
      sorted->players[max] = temp;
    }
  }
}

/**
 * sorts player high scores in descending order
 * @param PlayerList contains the list of player information
 * @param sorted contains the sorted PlayerList 
 */
void sortPlayerHighScore(struct PlayerList PlayerList, struct PlayerList* sorted)
{
  int i, j, max;
  struct Player temp;

  *sorted = PlayerList;
  for(i = 0; i < sorted->nLoadedPlayers - 1; i++)
  {
    max = i;
    for(j = i+1; j < sorted->nLoadedPlayers; j++)
    {
      if(sorted->players[max].highScore < sorted->players[j].highScore)
      {
        max = j;
      }
    }
    if(i != max)
    {
      temp = sorted->players[i];
      sorted->players[i] = sorted->players[max];
      sorted->players[max] = temp;
    }
  }
}


/**
 * diplays player stats (number of wins)
 * @param sorted contains the sorted player list 
 */
void displayPlayerWins(struct PlayerList sorted)
{
  int i;

  for(i = 0; i < sorted.nLoadedPlayers; i++)
  {
    printf("%s %d\n", sorted.players[i].username, sorted.players[i].numWins);
  }
}

/**
 * diplays player stats (high scores)
 * @param sorted contains the sorted player list 
 */
void displayPlayerScores(struct PlayerList sorted)
{
  int i;

  for(i = 0; i < sorted.nLoadedPlayers; i++)
  {
    printf("%s %d\n", sorted.players[i].username, sorted.players[i].highScore);
  }
}

/**
 * Display statistics interface
 */
void displayStatistics()
{
  printf("View Statistics\n\t[1] Display Number of Wins\n\t[2] Display High Scores\n\t[0] Back to Main Menu\n");
}

/**
 * get user's input for statistics choice 
 */
int getStatisticsChoice()
{
  int nChoice;
  displayStatistics();
  do 
  {
    printf("Enter option: ");
    scanf("%d", &nChoice);
  } while (nChoice < 0 || nChoice > 2);
  return nChoice;
}

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