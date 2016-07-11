# CandyCrush
##What is it?
This program can run Tic Tac Toe and Candy Crush with humans and AI. It can be played interactively or as a spectator of the AI battle.

###1. Tic Tac Toe
AI: Random, Minimax, Monte Carlo. Minimax is superior so far. Monte Carlo outperforms Random but loses 100% of the time against Minimax (that should not be the case).

Results for 50 games

	Random VS Random: 62% wins, 14% draws, 24% losses
	Random VS Minimax: 0% wins, 10% draws, 90% losses
	Random VS Monte Carlo: 28% wins, 10% draws, 62% losses
	Minimax VS Random: 98% wins, 2% draws, 0% losses
	Minimax VS Minimax: 0% wins, 100% draws, 0% losses
	Minimax VS Monte Carlo: 100% wins, 0% draws, 0% losses
	Monte Carlo VS Random: 88% wins, 4% draws, 8% losses
	Monte Carlo VS Minimax: 0% wins, 0% draws, 100% losses
	Monte Carlo VS Monte Carlo: 0% wins, 0% draws, 100% losses

###2. Candy Crush
AI: Random, Monte Carlo, Greedy. Monte Carlo is best followed by the greedy strategy which chooses the move that maximises score in the next state.
It's simplified version of Candy Crush, three or more cells of the same type must be in a horizontal or vertical line in order to get points, no fancy special candy (yet).


Average score for 20 games

	Random: 47 points
	Greedy: 58 points
	Monte Carlo: 74 points
	
	
##How to run it?
I've only tested on Mac OS X, C++14 compiler is required
g++ -std=c++14 *.cpp; ./a.out
