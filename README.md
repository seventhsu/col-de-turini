# col-de-turini

The Col de Turini is a famous driving road in the French Alps, and this program is true to its name: something that traverses mountains. col-de-turini is designed to find the optimal solution to a game of Pyramid solitaire.

Pyramid solitaire is a 1-player card game/puzzle that operates on a "pyramid", 7 cards high, of overlapping cards, and a "stock" consisting of the rest of the cards. The object is to clear the entire board by matching cards whose values add to 13, but the difficulty lies in the order the decisions are made due to the overlapping cards blocking certain moves: match one pair and not another another early on in the game, and it could end in loss due to a lack of valid moves later on.

col-de-turini forever changes Pyramid solitaire by analysing the starting state of the game, building a tree of all possible places where move decisions could cause divergences in game traces, and calculating which path(s) win the game and net the best score.

col-de-turini is written entirely from scratch in C++. Give it a pyramid of cards and a stock (first card being the top card) in a text file and run main.cpp.