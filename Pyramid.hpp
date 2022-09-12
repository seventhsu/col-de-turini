#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

/* A struct that holds the location of a card on the pyramid.
 * Can use this to enumerate the locations of important cards for use later
 */
typedef struct PyramidCardStruct {
	int row; // Ranges from 0 to 6, -1 if card represented is in stock
	int pos; // If card is in stock, ranges from 0 to 23, else ranges from 0 to 6
} Card;

/* An m-ary tree that enumerates all possible moves in the game.
 * It holds information on which two cards should be matched,
 * and where the game can go from there (the child nodes).
 */

typedef struct MatchingPairStruct {
	// If card is from stock, row = -1 and pos will be position from top of stock
	Card card1;
	Card card2;
} CardPair;

typedef struct MatchTreeNodeStruct {
	CardPair pair;
	std::vector<MatchTreeNodeStruct*> *next; // The next possible "game states"
} MatchNode;

class Pyramid {
	public:
		Pyramid(std::string fileloc);
		~Pyramid();
		MatchNode* buildMatchTree(std::vector<CardPair*> *moveList);
	private:
		int** pyramidArr; // A pyramidal "2-D" array. pyramidArr[0] has 1 element, pyramidArr[1] has 2, etc.
		std::vector<int> *stock; // The stock is ordered: we cannot just match any two cards inside it

		// The tree of all possible moves. This is the big boy right here
		MatchNode *matchTree;
};
