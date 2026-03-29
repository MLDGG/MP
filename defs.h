/******************************************************************************
 *  Description     : This file contains the core data structure definitions
                       and constants used throughout the Mantis card game program.
                       It defines structures for cards, decks, players, player lists, 
                       and basic utility structures such as coordinates and dates, 
                       allowing consistent data organization and sharing across 
                       multiple source files through modular programming.
 *  Author/s        : <De Guzman, Mavrick>
 *                    <Morin, Eliana>
 *  Section         : <S13A>
 *  Last Modified   : <29/03/2026>
 ******************************************************************************/

#ifndef DEFS_H // Include this to prevent redefinition error
#define DEFS_H // Include this to prevent redefinition error

/******************************************************************************
 * NOTE: These definitions are placed here in defs.h to demonstrate code
 * modularization across multiple files. You may move them to different files
 * if it better fits your code organization.
 ******************************************************************************/

#define PI 3.1415
#define ARR_SIZE 10


/**
 * Represents a 2D point
 */
typedef struct
{
  int x; // The x-coordinate of a point
  int y; // The y-coordinate of a point
} Coordinate;

/**
 * Represents a date
 */
typedef struct
{
  int day;   // The day [1-31]
  int month; // The integer representation of the month [1-12]
  int year;  // The year
} Date;

/**
 * Represents a card with a front color, 3 back color, and its point value
 */
struct Card
{
  char front; // front of card has a single color
  char back[3]; // back shows 3 different color
  int points; // point value of card
};

/**
 * Represents a deck of cards
 */
struct Deck
{
  struct Card cards[84]; // Cards in the deck
  int nCards;     // Number of cards in the deck
};

/**
 * Represents a player
 */
struct Player
{
  char username[37]; // name of player, max 36 characters + null terminator
  int tank[7]; // cards in player's hand
  int nHand; // number of cards in player's hand
  int playerNum; // its player number
  int score;  // player score
  int numWins; // number of wins
  int highScore; // high score
};

/**
 * Represents a player list (loaded from player.txt)
 */
struct PlayerList
{
  struct Player players[50]; // Array of players
  int nLoadedPlayers; // Number of players loaded from file
};
#endif // DEFS_H; Include this to prevent redefinition error
