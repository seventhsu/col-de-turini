#include "Pyramid.hpp"

/* Initialises the table (the pyramid and the stock) given a file with card values in it.
 * Card file can be written in 1-13 or A-JQK, as long as the structure is a correctly shaped pyramid.
 */
Pyramid::Pyramid(std::string fileloc) {
	std::ifstream fs(fileloc);
    // Init array of row arrays
    pyramidArr = (int**) malloc(7 * sizeof(int*));

    // Loop over rows
    for (int r = 0; r < 7; r++) {
        // Malloc space for each pyramid row, just in time
        pyramidArr[r] = (int*) malloc((r + 1) * sizeof(int));
        
        // Get line of text from file and put it in a stringstream
        std::string row;
        std::getline(fs, row);
        std::istringstream iss(row);
        
        for (int pos = 0; pos < r + 1; pos++) {
            // Grab the first space-delimited chunk and store it in token
            std::string token;
            std::getline(iss, token, ' ');
            
            // Attempt to interpret it as a value
            int cardValue = -1;
            if (token == "A") cardValue = 1;
            else if (token == "J") cardValue = 11;
            else if (token == "Q") cardValue = 12;
            else if (token == "K") cardValue = 13;
            else cardValue = stoi(token);

            // Put this card on the pyramid (array)
            pyramidArr[r][pos] = cardValue;
        }
    }

    // Initialize the stock
    stock = new std::vector<int>;
    std::string stockstr;
    std::getline(fs, stockstr);
    std::istringstream iss(stockstr);
    for (int pos = 0; pos < 24; pos++) { // In a 7-high pyramid of 52 cards, the stock must be 24 cards long
        // Grab the first space-delimited chunk and store it in token
        std::string token;
        std::getline(iss, token, ' ');

        // Attempt to interpret it as a value
        int cardValue = -1;
        if (token == "A") cardValue = 1;
        else if (token == "J") cardValue = 11;
        else if (token == "Q") cardValue = 12;
        else if (token == "K") cardValue = 13;
        else cardValue = stoi(token);

        // Put this card on the stack
        stock->push_back(cardValue);
    }
}

Pyramid::~Pyramid() {
    for (int i = 0; i < 7; i++) delete pyramidArr[i];
    delete pyramidArr;
    delete stock;
}

// We pass the list of moves made so far to construct the state of the game at each recursion
MatchNode* Pyramid::constructMatchTree(std::vector<CardPair> moveList) {
    // Reconstruct game state (i.e. touchables and stock) from move list
    // Enumerate all valid combinations of P-P, P-S, S-S (P = pyramid, S = stock)
    // Init each one as a node in this vector's nextlist
    // Loop over nextlist again and recurse for each one (breadth-first strat)
    return NULL;
}