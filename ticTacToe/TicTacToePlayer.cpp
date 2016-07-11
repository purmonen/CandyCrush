#include "TicTacToePlayer.hpp"
#include <assert.h>


GameBoard::CellPosition TicTacToeRandomBot::selectMove(const TicTacToe& game) {
    return RandomBot<GameBoard::CellPosition>().selectMove(game);
}

std::string TicTacToeRandomBot::description() const {
    return RandomBot<GameBoard::CellSwapMove>().description();
}

GameBoard::CellPosition TicTacToeHumanPlayer::selectMove(const TicTacToe& game) {
    return HumanPlayer<GameBoard::CellPosition>().selectMove(game);
}

std::string TicTacToeHumanPlayer::description() const {
    return HumanPlayer<GameBoard::CellSwapMove>().description();
}


std::pair<GameBoard::CellPosition, int> miniMaxWithAlphaBetaPruning(const TicTacToe& game, int alpha, int beta) {
    
    // The dummy move is not going to be performed since the game will be over already
    const auto dummyMove = GameBoard::CellPosition(0,0);
    if (game.gameResult() == TicTacToe::Win) {
        return {dummyMove, 1};
    } else if (game.gameResult() == TicTacToe::Loss) {
        return {dummyMove, -1};
    } else if (game.gameResult() == TicTacToe::Draw) {
        return {dummyMove, 0};
    } else {
        bool foundBetterMove = false;
        if (game.isWhitePlayersTurn()) {
            auto bestScore = std::numeric_limits<int>::min();
            auto legalMoves = game.legalMoves();
            auto bestMove = legalMoves[0];
            for (auto move: legalMoves) {
                auto score = miniMaxWithAlphaBetaPruning(game.gameForMove(move), alpha, beta).second;
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = move;
                }
                alpha = std::max(alpha, bestScore);
                if (alpha >= beta) {
                    break;
                }
            }
            return {bestMove, bestScore};
        } else {
            auto bestScore = std::numeric_limits<int>::max();
            auto legalMoves = game.legalMoves();
            auto bestMove = legalMoves[0];
            for (auto move: legalMoves) {
                auto score = miniMaxWithAlphaBetaPruning(game.gameForMove(move), alpha, beta).second;
                if (score < bestScore) {
                    bestScore = score;
                    bestMove = move;
                }
                beta = std::min(beta, bestScore);
                if (alpha >= beta) {
                    break;
                }
            }
            assert(foundBetterMove);
            return {bestMove, bestScore};
        }

    }
}


GameBoard::CellPosition MiniMaxBot::selectMove(const TicTacToe& game) {
    return miniMaxWithAlphaBetaPruning(game, std::numeric_limits<int>::min(), std::numeric_limits<int>::max()).first;
}

std::string MiniMaxBot::description() const {
    return "Minimax";
}


void MonteCarloBot::simulate(const TicTacToe game) const {
    std::unordered_set<TicTacToe> visitedStates;
    visitedStates.insert(game);
    
    TicTacToe nextState = game;
    while (nextState.gameResult() == TicTacToe::Running) {
        auto legalMoves = nextState.legalMoves();
        nextState = nextState.gameForMove(legalMoves[rand() % legalMoves.size()]);
        visitedStates.insert(nextState);
    }
    
    for (auto state: visitedStates) {
        numberOfGames[state]++;
        if (nextState.gameResult() == (game.isWhitePlayersTurn() ? TicTacToe::Win : TicTacToe::Loss)) {
            numberOfWins[state]++;
        }
    }
}

GameBoard::CellPosition MonteCarloBot::selectMove(const TicTacToe& game) {
    for (auto i = 0; i < 100; i++) { simulate(game); }
    
    auto bestWinPercentage = -1;
    auto bestMove = game.legalMoves()[0];
    for (auto move: game.legalMoves()) {
        auto nextState = game.gameForMove(move);
        if (numberOfGames[nextState] > 0) {
            auto winPercentage = numberOfWins[nextState] / (double)numberOfGames[nextState];
            if (winPercentage > bestWinPercentage) {
                bestWinPercentage = winPercentage;
                bestMove = move;
            }
            
        }
    }
    return bestMove;
}

std::string MonteCarloBot::description() const {
    return "Monte Carlo";
}
