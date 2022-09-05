# col-de-turini

Col de Turini is a famous driving road in the French Alps, and this program is true to its name: something that traverses a mountain. col-de-turini is designed to find the optimal solution to a game of Pyramid Solitaire.

Pyramid Solitaire is a 1-player card game/puzzle where the object is to clear the entire board by matching cards whose values add to 13. The difficulty lies in the order the decisions are made. Match one pair and not another another early on in the game, and it could end in a loss due to a lack of valid moves later.

col-de-turini forever changes Pyramid Solitaire by analysing the starting state of the game, building a tree of all possible places where move decisions could cause divergences in game traces, and calculating which path(s) win the game and score the most points.

col-de-turini is written entirely from scratch in C++.
