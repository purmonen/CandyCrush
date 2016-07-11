# CandyCrush
##What is it?
This program can run Tic Tac Toe and Candy Crush with humans and AI. It can be played interactively or as a spectator of the AI battle.

###1. Tic Tac Toe
AI: Random, Minimax, Monte Carlo. Minimax is superior so far. Monte Carlo outperforms Random but loses 100% of the time against Minimax (that should not be the case).

###2. Candy Crush
AI: Random, Monte Carlo, Greedy. Monte Carlo is best followed by the greedy strategy which chooses the move that maximises score in the next state.
It's simplified version of Candy Crush, three or more cells of the same type must be in a horizontal or vertical line in order to get points, no fancy special candy (yet).

##How to run it?
I've only tested on Mac OS X, C++14 compiler is required
g++ -std=c++14 *.cpp; ./a.out
