#ifndef CandyCrush_hpp
#define CandyCrush_hpp

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "GameBoard.hpp"
#include "Game.hpp"


class CandyCrush;
class CandyCrushPlayer {
public:
    virtual GameBoard::CellSwapMove selectMove(const CandyCrush&)= 0;
    virtual std::string description() const = 0;
};

struct CandyCrushGameBoardChange;

class CandyCrush {
public:
    enum Cell {Green, Blue, Purple, Red, Yellow};
    typedef std::function<void(CandyCrushGameBoardChange)> GameBoardChangeCallback;
    //enum Cell {Green, Blue, Orange, Red, Purple};
    
private:
    int numberOfMovesLeft = 100;
    friend std::ostream& operator<<(std::ostream&, const CandyCrush&);
    GameBoard::GameBoard<6, 6, Cell> gameBoard = GameBoard::GameBoard<6, 6, Cell>([](auto rows, auto columns) {
        std::vector<CandyCrush::Cell> cells = {Green, Blue, Purple, Red, Yellow};
        return cells[rand() % cells.size()];
    });
    int score = 0;
    Cell randomCell();
    void clearAllMatches(GameBoardChangeCallback callback = nullptr);
    
    int scoreForMatches(int numberOfMatches);
//    void performMove(GameBoard::CellSwapMove move);
    void performMove(GameBoard::CellSwapMove move, GameBoardChangeCallback callback = nullptr);
public:
    CandyCrush();
    const GameBoard::GameBoard<6, 6, Cell>& getGameBoard() const;
    bool isLegalMove(GameBoard::CellSwapMove move) const;
    bool operator==(const CandyCrush & game) const;
    int getScore() const;
    int getNumberOfMovesLeft() const;
    
    
    
    bool play(GameBoard::CellSwapMove move, GameBoardChangeCallback callback = nullptr);
    bool gameOver() const;
    std::vector<GameBoard::CellSwapMove> legalMoves() const;
    static int run(CandyCrushPlayer& player, bool showOutput);
    static int run(CandyCrushPlayer& player, int numberOfGames);
    CandyCrush gameForMove(GameBoard::CellSwapMove move) const;
};


namespace std {
    
    template <>
    struct hash<CandyCrush>
    {
        std::size_t operator()(const CandyCrush& game) const
        {
            using std::size_t;
            using std::hash;
            using std::string;
            
            
            auto& gameBoard = game.getGameBoard();
            std::size_t seed = game.getNumberOfMovesLeft();
            
            for (auto row = 0; row < gameBoard.rows; row++) {
                for (auto column = 0; column < gameBoard.columns; column++) {
                    seed ^= gameBoard[row][column] + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                }
            }
            
            return seed;
        }
    };
}

struct CandyCrushGameBoardChange {
    std::unordered_map<GameBoard::CellPosition, GameBoard::CellPosition> cellPositions;
    std::unordered_set<GameBoard::CellPosition> removedCells;
//    std::unordered_set<GameBoard::CellPosition>
    CandyCrush game;
    std::vector<std::tuple<GameBoard::CellPosition, CandyCrush::Cell, int>> newCells;
    CandyCrushGameBoardChange(std::unordered_map<GameBoard::CellPosition, GameBoard::CellPosition> cellPositions, std::unordered_set<GameBoard::CellPosition> removedCells, CandyCrush game, std::vector<std::tuple<GameBoard::CellPosition, CandyCrush::Cell, int>> newCells): cellPositions(cellPositions), removedCells(removedCells), game(game), newCells(newCells) {
        
    }
    
};

std::ostream& operator<<(std::ostream& os, const CandyCrush& game);
//
//

#endif /* CandyCrush_hpp */

