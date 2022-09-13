#include "Pyramid.hpp"

/* Initialises the table (the pyramid and the stock) given a file with card values in it.
 * Card file can be written in 1-13 or A-JQK, as long as the structure is a correctly shaped pyramid.
 */
Pyramid::Pyramid(std::string fileloc) {
    std::ifstream fs(fileloc);
    // Init array of row arrays
    pyramidArr = new int*[7];

    // Loop over rows
    for (int r = 0; r < 7; r++) {
        // Malloc space for each pyramid row, just in time
        pyramidArr[r] = new int[r + 1];
        
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
    delete[] pyramidArr; // This is probably enough to delete everything, check with Valgrind later
    delete stock;
}

/* We pass the list of moves made so far to construct the state of the game at each recursion
 * Default arg is NULL for a game with no matches made already
 */
MatchNode* Pyramid::buildMatchTree(std::vector<CardPair*> *moveList) {
    // Create an exact copy of pyramidArr to operate on
    int** replicaPyramid = new int*[7]; // 7 rows
    for (int r = 0; r < 7; r++) {
        replicaPyramid[r] = new int[r + 1]; // Pyramid: rows get longer as they go down
        for (int c = 0; c < r + 1; c++) replicaPyramid[r][c] = pyramidArr[r][c]; // Fill the row
    }

    // Make copy of the starting stock to modify
    std::vector<int> *replicaStock = new std::vector<int>(*stock);
    
    // Go through all moves made and reconstruct the game state in the replica pyramid and stock
    for (CardPair* move : *moveList) {
        // For ease of reading, let's create references to the cards used in the move
        const Card &c1 = *(move->card1);
        const Card &c2 = *(move->card2);
        
        // Safety check: make sure we didn't match a card with itself
        if (c1.row == c2.row && c1.pos == c2.pos) {
            std::cerr << "Fundamental moveList error! A move describes two of the same card" << std::endl;
            exit(1);
        }
        // Another safety check: make sure the cards actually sum to 13
        if (replicaPyramid[c1.row][c1.pos] + replicaPyramid[c2.row][c2.pos] != 13) {
            std::cerr << "Fundamental moveList error! Cards in move do not sum to 13" << std::endl;
            exit(1);
        }

        // Remember, a row value of -1 means the card specified is on the stock
        if (c1.row == -1) replicaStock->erase(replicaStock->begin() + c1.pos); // Remove from stock
        else replicaPyramid[c1.row][c1.pos] = 0; // Clear card on pyramid
        
        // Same thing for card 2
        if (c2.row == -1) replicaStock->erase(replicaStock->begin() + c2.pos); // Remove from stock
        else replicaPyramid[c2.row][c2.pos] = 0; // Clear card on pyramid
    }

    // Just printing the pyramid
    std::cout << "Test print:" << std::endl;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < i + 1; j++) std::cout << replicaPyramid[i][j] << " ";
        std::cout << std::endl;
    }

    std::vector<Card*> *touchables = new std::vector<Card*>();
    // TODO: done making moves, time to enumerate the touchable cards
    //       Loop over the whole pyramid: if both children are 0 and current card is not, add to touchables
    
    // TODO: For all valid combinations of cards in touchables and/or the stock:
    //       Init each one as a node in this vector's nextlist (since it's a valid next move)
    
    // Done calculating the game state, so we can free some space up on the stack
    delete[] replicaPyramid;

    // TODO: Loop over nextlist again and recurse for each one (breadth-first strat)

    return NULL;
}