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
    stock = new std::vector<int>();
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

/* We pass the list of moves made so far to construct the state of the game at each recursion
 * Default arg is NULL for a game with no matches made already
 */
MatchNode* Pyramid::buildMatchTree(std::vector<CardPair*> *moveList) {
    // Touchable cards on the pyramid always start as the bottom row and nothing else
    std::vector<Card*> *touchables = new std::vector<Card*>();
    for (int i = 0; i < 7; i++) touchables->push_back(new Card{.row = 6, .pos = i});
    // Make copy of the starting stock to modify
    std::vector<int> *currentStock = new std::vector<int>(*stock);
    
    // Go through all moves made and reconstruct the game state in touchables and currentStock
    for (CardPair* move : *moveList) {
        // Just make sure the cards sum to 13, just in case...
        if (pyramidArr[move->card1.row][move->card1.pos] + pyramidArr[move->card2.row][move->card2.pos] != 13) {
            std::cerr << "Fundamental moveList error! Cards in move do not sum to 13" << std::endl;
            exit(1);
        }

    }
    
    // For all valid combinations of cards on either the pyramid or the stock:
    // Init each one as a node in this vector's nextlist
    
    // Done calculating the game state, so we can free some space up on the stack
    delete touchables;
    delete stock;

    // Loop over nextlist again and recurse for each one (breadth-first strat)

    return NULL;
}