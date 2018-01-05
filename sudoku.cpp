#include "sudoku.h"
#include "draw.h"
#include <iostream>
#include <string.h>

using namespace std;

bool firstpass = 1;

game sudoku = {0};

int main (){
	initgame();
	getgame();
	draw_screen(sudoku.solution);
	int count = 0;
	int count_new = 0;

	while(count < GAME_SIZE){
		count_new = solvegame();
		if(count == count_new){
			cout<<"Something went wrong!! solvegame() returned the same value twice of: "<<count<<endl;
			count = GAME_SIZE; // lazy way to exit loop
		}
		else count = count_new;
	}
	cout<<endl;
	draw_screen(sudoku.solution);

/*
	solvegame();
	draw_notes(3);
	draw_notes(4);
*/
}

void initgame(){
//set all notes to 1, solution to 0
	for(int i=0; i<(GAME_SIZE); i++) {
		sudoku.solution[i] = 0;
		sudoku.notes[i*9+0] = 1;
		sudoku.notes[i*9+1] = 1;
		sudoku.notes[i*9+2] = 1;
		sudoku.notes[i*9+3] = 1;
		sudoku.notes[i*9+4] = 1;
		sudoku.notes[i*9+5] = 1;
		sudoku.notes[i*9+6] = 1;
		sudoku.notes[i*9+7] = 1;
		sudoku.notes[i*9+8] = 1;

	}
}

void getgame(){

//Fills an array with user data and copies it to the solution member of game sudoku
 /*	int x = 0;
	char y = 0;
	for( int i=0; i<9; i++){
		cout << "\nEnter Row " << (i+1) << ":";
		for (int j = 0; j<9; j++){
			//cin >> x;
			//x = y - '0';
			sudoku.solution[j+i*9] = i+1;
		}
	}
	cout<<endl;*/

	//type game here, or include above code to input at runtime
	int a[GAME_SIZE] = { 7, 3, 9, 	0, 0, 5, 	2, 0, 0,
								4, 8, 0, 	0, 6, 0, 	9, 0, 1,
								2, 0, 0, 	3, 0, 9, 	0, 8, 0,

								0, 5, 3, 	6, 1, 0, 	0, 0, 0,
								0, 0, 0, 	8, 0, 7, 	0, 0, 0,
								0, 0, 0, 	0, 5, 3, 	6, 1, 0,

								0, 4, 0, 	5, 0, 0, 	0, 0, 7,
								3, 0, 7, 	0, 2, 0, 	0, 5, 8,
								0, 0, 8,		4, 0, 0, 	3, 2, 6
							};

	memcpy(sudoku.solution, a, sizeof(sudoku.solution));
}

int solvegame(){
//runs through a single sweep of the game.  Must be called until it returns count == GAME_SIZE
	int count=0;
	for(int i=0; i<(GAME_SIZE); i++) {
		solvesquare(i);
		if(sudoku.solution[i] == 0){
			checkrow(i);
			checkcolumn(i);
			checksextant(i);
		}
		else{
			clearallnotes(i);
	   	count++;
		}
	}
	if (count == GAME_SIZE) cout << "Game Solved\n";
	return count;
}

void checkrow(int i){
//Checks if a solution already exits in the same row as square i, if so it clears that note for square i
	int x = 0;
	for(int j = 0; j < ROW_SIZE; j++){
		x = ((int)i / ROW_SIZE)*ROW_SIZE+j;
		if(x != i){
			if( sudoku.solution[x] == 1) sudoku.notes[i*9+0] = 0;
			if( sudoku.solution[x] == 2) sudoku.notes[i*9+1] = 0;
			if( sudoku.solution[x] == 3) sudoku.notes[i*9+2] = 0;
			if( sudoku.solution[x] == 4) sudoku.notes[i*9+3] = 0;
			if( sudoku.solution[x] == 5) sudoku.notes[i*9+4] = 0;
			if( sudoku.solution[x] == 6) sudoku.notes[i*9+5] = 0;
			if( sudoku.solution[x] == 7) sudoku.notes[i*9+6] = 0;
			if( sudoku.solution[x] == 8) sudoku.notes[i*9+7] = 0;
			if( sudoku.solution[x] == 9) sudoku.notes[i*9+8] = 0;
		}
	}
}

void checkcolumn(int i){
//Checks if a solution already exits in the same column as square i, if so it clears that note for square i
	int x = 0;
	for(int j = 0; j < ROW_SIZE; j++){
		x = (i%ROW_SIZE)+j*ROW_SIZE;
		if(x != i){
			if( sudoku.solution[x] == 1) sudoku.notes[i*9+0] = 0;
			if( sudoku.solution[x] == 2) sudoku.notes[i*9+1] = 0;
			if( sudoku.solution[x] == 3) sudoku.notes[i*9+2] = 0;
			if( sudoku.solution[x] == 4) sudoku.notes[i*9+3] = 0;
			if( sudoku.solution[x] == 5) sudoku.notes[i*9+4] = 0;
			if( sudoku.solution[x] == 6) sudoku.notes[i*9+5] = 0;
			if( sudoku.solution[x] == 7) sudoku.notes[i*9+6] = 0;
			if( sudoku.solution[x] == 8) sudoku.notes[i*9+7] = 0;
			if( sudoku.solution[x] == 9) sudoku.notes[i*9+8] = 0;
		}
	}
}


void checksextant(int square){
//checks for an existing solution in each other square in the same sextant, if found clears that note for square i

// attempting general solution ....
//check each other square in the sextant, if there is a non-zero solution, clear the associated note for square
	int a = ((int) (square / (9 * 3))); // = 0, 1 or 2 depending on which row of sextants square is in
	int b = ((int) (square % 9)/(3)); //= 0, 1 or 2 depending on which column of sextants square is in 
	// a*9*3+b*3 is the top corner of whichever sextant square is in
	//int topcorner = ((int)(square / (9 * 3))*9*3 + (int)((square - a) - ((int) square/9)*9)/3;
	int topcorner = a*9*3+b*3;

	//cout<<"Square: "<<square<<" Topcorner: "<<topcorner<<endl;

	for(int i = 0; i < 3; i++){ //for each row in sextant...
		for(int j = 0; j < 3; j ++){ //for each square in each row...			
			if(topcorner + j + i*9 != square){ //check that this is not square
				if (sudoku.solution[topcorner + j + i*9] != 0) // check there is a solution 
					sudoku.notes[square*9 + (sudoku.solution[topcorner + j + i*9] - 1)] = 0;
			}
		}
	}
}


int sumallnotes(int square){
	int check = sudoku.notes[square*9+0] + 
					sudoku.notes[square*9+1] +
					sudoku.notes[square*9+2] +
					sudoku.notes[square*9+3] +
					sudoku.notes[square*9+4] +
					sudoku.notes[square*9+5] +
					sudoku.notes[square*9+6] +
					sudoku.notes[square*9+7] +
					sudoku.notes[square*9+8];
	return check;
}


void clearallnotes(int square){
//This funciton is called during the first call of solvegame() when there are given solutions.
	clearallothernotes(square, sudoku.solution[square]);
}

void clearallothernotes(int square, int number){
//this funciton clears all other notes except for number
	if(number != 0){
		int zeros[9] = {0,0,0,0,0,0,0,0,0};
		memcpy(&sudoku.notes[square*9], zeros, sizeof(zeros));
		sudoku.notes[square*9+number-1] = 1;
	}
}

void solvesquare(int square){
	//check if only a single note remains checked, if so set the solution.
	if(sumallnotes(square) == 1){
		for(int i = 0; i < 9; i++){
			if(sudoku.notes[square*9+i] != 0) sudoku.solution[square] = i+1;
		}
	}
	else if(sumallnotes(square) == 0)
		cout<<"something went wrong!! Square: "<<square<<" has all it's notes cleared\n";
}

