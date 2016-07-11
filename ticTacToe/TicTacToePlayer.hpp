#ifndef TicTacToePlayer_hpp
#define TicTacToePlayer_hpp

#include "TicTacToe.hpp"


class TicTacToeRandomBot: public TicTacToePlayer {
public:
    GameBoard::CellPosition selectMove(const TicTacToe& game);
    std::string description() const;
};


class TicTacToeHumanPlayer: public TicTacToePlayer {
public:
    
    GameBoard::CellPosition selectMove(const TicTacToe& game);
    std::string description() const;
};

class MiniMaxBot: public TicTacToePlayer {
public:
//    int scoreForGame(const TicTacToe& game);
////    std::pair<GameBoard::CellPosition, int> bestMoveForGame(const TicTacToe& game);
    GameBoard::CellPosition selectMove(const TicTacToe& game);
    std::string description() const;
};

class MonteCarloBot: public TicTacToePlayer {
public:
    
    mutable std::unordered_map<TicTacToe, int> numberOfWins;
    mutable std::unordered_map<TicTacToe, int> numberOfGames;
    
    void simulate(const TicTacToe game) const;
    GameBoard::CellPosition selectMove(const TicTacToe& game);
    std::string description() const;
};


#endif /* TicTacToePlayer_hpp */
