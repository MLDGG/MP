/******************************************************************************
 *  Description     : <short description of the file>
 *  Author/s        : <student1 full name (last name, first name)>
 *                    <student2 full name (last name, first name)>
 *  Section         : <your section>
 *  Last Modified   : <date when last revision was made>
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

struct Card
{
  char front; // front of card has a single color
  char back[4]; // back shows 3 different color
  int points; // point value of card
};

struct Deck
{
  struct Card cards[84]; // Cards in the deck
  int nCards;     // Number of cards in the deck
};

struct Player
{
  char username[37]; // name of player, max 36 characters + null terminator
  int tank[7]; // cards in player's hand
  int nHand; // number of cards in player's hand
  int playerNum;
  int score; 
  int numWins;
};

#endif // DEFS_H; Include this to prevent redefinition error