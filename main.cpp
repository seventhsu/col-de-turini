#include "Pyramid.hpp"

int main() {
    Pyramid *p = new Pyramid("alps.txt");
    
    // Match a Q and a 1 for testing
    Card *move1card1 = new Card{.row=6, .pos=4};
    Card *move1card2 = new Card{.row=6, .pos=1};
    CardPair *move1 = new CardPair{.card1=move1card1, .card2=move1card2};
    std::vector<CardPair*> *moveList = new std::vector<CardPair*> {move1};
    
    // Build a match tree starting from here
    p->buildMatchTree(moveList);
    return 0;
}