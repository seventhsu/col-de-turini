#include "Pyramid.hpp"

<<<<<<< HEAD
/* Initialises the table (the pyramid and the stock) given a file with card values in it.
 * Card file can be written in 1-13 or A-JQK, as long as the structure is a correctly shaped pyramid.
 */
Pyramid::Pyramid(std::string fileloc) {
	std::ifstream fs(fileloc);
=======
void Pyramid::initPyramid(std::string fileloc) {
>>>>>>> bf2104c64bdbb0bed274c90ad1292ded2392566a
    // Init array of row arrays
    pyramidArr = (int**) malloc(7 * sizeof(int*));

    // Initialize the stock as full. 13 types of cards, 4 cards each
    stock = new std::map<int, int>;
    for (int val = 1; val <= 13; val++) stock->insert(std::make_pair(val, 4));

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

            // Take this card out of the stock
            (*stock)[cardValue] -= 1;

            // Put this card on the pyramid (array)
            pyramidArr[r][pos] = cardValue;
        }
    }
}
