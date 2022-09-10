#include "Pyramid.hpp"

void Pyramid::initPyramid(std::string fileloc) {
	// Init array of row arrays
    pyramidArr = (int**) malloc(7 * sizeof(int*));
    // Init each row array with its correct size to make a pyramid
    for (int r = 0; r < 7; r++) {
        pyramidArr[r] = (int*) malloc((r + 1) * sizeof(int));
    }
    
    std::ifstream fs(fileloc);
    std::string row;
    while (std::getline(fs, row)) {
        int cardValue = -1;
        if (row.substr(0, 1) == "J") cardValue = 11;
        else if (row.substr(0, 1) == "Q") cardValue = 12;
        else if (row.substr(0, 1) == "K") cardValue = 13;
        else cardValue = stoi(row.substr(0, 1));
        
        pyramidArr[0][0] = cardValue;
        std::cout << row << std::endl;
    }
}