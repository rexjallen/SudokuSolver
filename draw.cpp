#include "draw.h"
#include <iostream>

using namespace std;

void draw_screen(int page[GAME_SIZE]){
	for(int h = 0; h < 3; h++){
		for(int i = 0; i < 3; i++){
			for( int j = 0; j < 3; j++){
				switch (j) {
					case 1 : 
						cout << "|";
						break;
					case 2 :
						cout << "|";
					break;
				}
				for( int k = 0; k < 3; k++){
					cout << page[(k+j*3+i*9+h*27)];
				}
				switch (j) {
					case 2 :
						cout << "\n";
					break;
				}
			}
		}
		switch (h) {
			case 0 :
				cout <<"-----------\n";
			break;
			case 1 :
				cout <<"-----------\n";
			break;
		}
	}
}

void draw_notes(int number){
	int page[GAME_SIZE];
	for(int i = 0; i < GAME_SIZE; i++){
		page[i] == sudoku.notes[i*9+(number-1)];
	}
	draw_screen(page);
}

