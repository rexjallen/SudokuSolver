//#include "sudoku.h"
#include "fileio.h"

int main(){
	readgame();
}

void readgame(){
	FILE* fd = NULL;

	fd = fopen("sample.txt","r+");

	long int sz = fsizeof(fd);

	char buff[sz/sizeof(char)];
	memset(buff, 0, sizeof(buff));

	size_t buffsize = sizeof(buff)/sizeof(char);

	fread(buff, sizeof(char), buffsize, fd);

	for(int i = 0; i < buffsize; i ++){
		std::cout<<buff[i];
	}
	
}


long int fsizeof(FILE* fd){
	long int spot = 0;
	long int sz = 0;

	spot = ftell(fd);
	fseek(fd, 0L, SEEK_END);
	sz = ftell(fd);
	fseek(fd, spot, SEEK_SET);
	return sz;
}
