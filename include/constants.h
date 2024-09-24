#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

// System Parameters
#define TICK 10

// Map Parameters
#define N_LAYER 2
#define MAP_WIDTH 60
#define MAP_HEIGHT 18

// Game Object Parameters
#define MAX_OBJECTS 1000
#define MAX_MESSAGES 10
#define MESSAGE_LENGTH 100

// Colors
#define COLOR_DEFAULT 15
#define COLOR_CURSOR 112
#define COLOR_RESOURCE 112
#define COLOR_PLAYER 9   // Blue for player
#define COLOR_AI 12      // Red for AI
#define COLOR_NEUTRAL 7  // White for neutral

/* ================= Display Section Parameters ==================*/
#define COLOR_DEFAULT   7   // Default color
#define COLOR_CURSOR    112 // Cursor color
#define COLOR_RESOURCE  15  // Resource display color
#define COLOR_BORDER    15  // Border color
#define COLOR_TITLE     15  // Title color
#define SYSTEM_MESSAGE_HEIGHT 5  // Height of system message area
#define COMMAND_HEIGHT 3         // Height of command area
#define STATUS_WIDTH 30          // Width of status area
#define TOTAL_WIDTH (MAP_WIDTH + STATUS_WIDTH + 3)  // Total width of display
#define TOTAL_HEIGHT (MAP_HEIGHT + SYSTEM_MESSAGE_HEIGHT + COMMAND_HEIGHT + 4)  // Total height of display

// Team IDs
#define TEAM_NEUTRAL 0
#define TEAM_PLAYER 1
#define TEAM_AI 2

// Object Types
#define TYPE_TERRAIN 'T'
#define TYPE_BUILDING 'B'
#define TYPE_UNIT 'U'

#endif