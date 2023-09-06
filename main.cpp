#include "libs.hpp"

// to be compiled afterwards
int mainTitle(), mainGame(int);

int main(){
	int x = mainTitle();

	if(x == 2) {
		return 0;
	}

	if(mainGame(x)) {
		std::cout << "Error in main game!" << std::endl;
		return -1;
	}

	return 0;
}
