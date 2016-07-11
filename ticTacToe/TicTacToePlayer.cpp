#include "TicTacToePlayer.hpp"


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

int MiniMaxBot::scoreForGame(const TicTacToe& game) {
    if (game.gameResult() == TicTacToe::Loss) {
        return 1;
    } else if (game.gameResult() == TicTacToe::Win) {
        return -1;
    } else if (game.gameResult() == TicTacToe::Draw) {
        return 0;
    } else {
        auto bestScore = game.isWhitePlayersTurn() ? 99999999 : -999999;
        for (auto move: game.legalMoves()) {
            auto score = scoreForGame(game.gameForMove(move));
            if (game.isWhitePlayersTurn() && score <= bestScore) {
                bestScore = score;
            }
            if (!game.isWhitePlayersTurn() && score >= bestScore) {
                bestScore = score;
            }
            
            
        }
        return bestScore;
    }
}

GameBoard::CellPosition MiniMaxBot::selectMove(const TicTacToe& game) {
    auto legalMoves = game.legalMoves();
    GameBoard::CellPosition bestMove = legalMoves[0];
    auto bestMoveScore = game.isWhitePlayersTurn() ? 999999 : -999999;
    for (auto move: legalMoves) {
        auto score = scoreForGame(game.gameForMove(move));
        if (game.isWhitePlayersTurn() && score <= bestMoveScore) {
            bestMoveScore = score;
            bestMove = move;
        }
        if (!game.isWhitePlayersTurn() && score >= bestMoveScore) {
            bestMoveScore = score;
            bestMove = move;
        }
    }
    return bestMove;
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
