#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

/* A struct that holds the location of a card on the pyramid.
 * Can use this to enumerate the locations of important cards for use later
 */
typedef struct PyramidCardStruct {
	int r;
	int pos;
} Card;

/* An m-ary tree that enumerates all possible moves in the game.
 * It holds information on which two cards should be matched,
 * and where the game can go from there (the child nodes).
 */
typedef struct MatchTreeNodeStruct {
	bool both_pyramid; // = true if matching two pyramid cards, = false if matching a pyramid card and a stock card
	Card card1;
	Card card2; // defined if both_pyramid == true, (-1, -1) otherwise
	// No need to store stock card if we are matching from pyramid and stock. We know card1's value + stock card = 13
	
	std::vector<MatchTreeNodeStruct*> nextMatches; // The next possible "game states"
} MatchNode;

class Pyramid {
	public:
		void initPyramid(std::string fileloc);
	private:
		int** pyramidArr; // A pyramidal "2-D" array. pyramidArr[0] has 1 element, pyramidArr[1] has 2, etc.
		std::map<int, int> stock; // arg0 is card face value (1-13), arg1 is how many in stock

		std::vector<Card> touchables; // Locations of all pyramid cards which are not covered off by other cards
		MatchNode *moveTree;
};
