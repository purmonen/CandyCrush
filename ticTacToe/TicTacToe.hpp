#ifndef TicTacToe_hpp
#define TicTacToe_hpp

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "GameBoard.hpp"
#include "Game.hpp"


class TicTacToe;

class TicTacToePlayer {
public:
    virtual GameBoard::CellPosition selectMove(const TicTacToe&)= 0;
    virtual std::string description() const = 0;
};


class TicTacToe: public Game<GameBoard::CellPosition> {
public:
    enum Cell {White, Black, Empty};
    enum GameResult {Win, Loss, Draw, Running};
private:
    static const size_t numberOfRowsToWin = 3;
    bool whitePlayersTurn = true;
    friend std::ostream& operator<<(std::ostream&, const TicTacToe&);
    GameBoard::GameBoard<3, 3, Cell> gameBoard = GameBoard::GameBoard<3, 3, Cell>(Empty);
public:
    
    const GameBoard::GameBoard<3, 3, Cell> getGameBoard() const {
        return gameBoard;
    }
    bool isWhitePlayersTurn() const;
    bool play(GameBoard::CellPosition cellPosition);
    bool play(const size_t row, const size_t column);
    
    GameResult gameResult() const;
    std::vector<GameBoard::CellPosition> legalMoves() const;
    
    TicTacToe gameForMove(GameBoard::CellPosition move) const;
    
    bool operator==(const TicTacToe & game) const;
    
    bool gameOver() const;
    
    struct TestResult {
        int wins = 0;
        int losses = 0;
        int draws = 0;
        
        int numberOfGames() {
            return wins + losses + draws;
        }
    };
    
    static GameResult run(TicTacToePlayer& whitePlayer, TicTacToePlayer& blackPlayer, bool showOutput = true);
    static TestResult runMany(TicTacToePlayer& whitePlayer, TicTacToePlayer& blackPlayer, int numberOfGames);
};

std::ostream& operator<<(std::ostream& os, const TicTacToe& game);


namespace std {
    
    template <>
    struct hash<TicTacToe>
    {
        std::size_t operator()(const TicTacToe& game) const
        {
            using std::size_t;
            using std::hash;
            using std::string;
            
            
            auto& gameBoard = game.getGameBoard();
            std::size_t seed = 0;
            
            for (auto row = 0; row < gameBoard.rows; row++) {
                for (auto column = 0; column < gameBoard.columns; column++) {
                    seed ^= gameBoard[row][column] + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                }
            }
            
            return seed;
        }
    };
}


#endif /* TicTacToe_hpp */
