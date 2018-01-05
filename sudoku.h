#ifndef _SUDOKU_H
#define _SUDOKU_H

//defines
#define GAME_SIZE 81
#define ROW_SIZE 9


//funciton prototypes
void initgame();
void getgame();
int solvegame();
void checkrow(int);
void checkcolumn(int);
void checksextant(int);
int checkallnotes(int);
void clearallnotes(int);
void clearallothernotes(int, int);
void solvesquare(int square);

//Global variables
// extern int game[];

typedef struct {
	int solution[GAME_SIZE];
	int notes[GAME_SIZE*9];
	/*
	int ones[GAME_SIZE];
	int twos[GAME_SIZE];
	int threes[GAME_SIZE];
	int fours[GAME_SIZE];
	int fives[GAME_SIZE];
	int sixes[GAME_SIZE];
	int sevens[GAME_SIZE];
	int eights[GAME_SIZE];
	int nines[GAME_SIZE];
*/
}game;

extern game sudoku;

#endif

