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


class CandyCrush: public Game<GameBoard::CellSwapMove> {
public:
    enum Cell {Green, Blue, Orange, Red};
    //enum Cell {Green, Blue, Orange, Red, Purple};
    int numberOfMovesLeft = 7;
private:
    friend std::ostream& operator<<(std::ostream&, const CandyCrush&);
    
    GameBoard::GameBoard<6, 6, Cell> gameBoard = GameBoard::GameBoard<6, 6, Cell>([](auto rows, auto columns) {
        std::vector<CandyCrush::Cell> cells = {Green, Blue, Orange, Red};
        return cells[rand() % cells.size()];
    });
    
    int score = 0;
    
    Cell randomCell() {
        std::vector<CandyCrush::Cell> cells = {Green, Blue, Orange, Red};
        return cells[rand() % cells.size()];
    }
    
    // When randomly generating new cells some of them will create matches that must be cleared after each move and when initializing the game
    void clearAllMatches() {
        while (isLegalMove(GameBoard::CellSwapMove(GameBoard::CellPosition(0,0), GameBoard::CellPosition(0,0)))) {
            performMove(GameBoard::CellSwapMove(GameBoard::CellPosition(0,0), GameBoard::CellPosition(0,0)));
        }
    }
    
    bool isLegalMove(GameBoard::CellSwapMove move) const {
        if (!gameBoard.isCellValid(move.from) || !gameBoard.isCellValid(move.to)) {
            return false;
        }
        
        // Perform the move on a copy of the game
        auto game = *this;
        game.performMove(move);
        
        // All legal moves increases score!
        return game.score != score;
    }
    
    void performMove(GameBoard::CellSwapMove move) {
        
        // Move pieces
        gameBoard.swapCells(move.from, move.to);
        
        // Horizontal matching
        for (auto row = 0; row < gameBoard.rows; row++) {
            int numberOfMatches = 0;
            auto lastCell = gameBoard[row][0];
            for (auto column = 0; column < gameBoard.columns; column++) {
                if (lastCell == gameBoard[row][column]) {
                    numberOfMatches++;
                } else {
                    if (numberOfMatches >= 3) {
                        score += numberOfMatches + (numberOfMatches >= 4 ? 5 : 0);
                        for (auto matchedColumn = column-numberOfMatches; matchedColumn < column; matchedColumn++) {
                            for (auto matchedRow = row-1; matchedRow >= 0; matchedRow--) {
                                gameBoard[matchedRow+1][matchedColumn] = gameBoard[matchedRow][matchedColumn];
                            }
                            gameBoard[0][matchedColumn] = randomCell();
                        }
                    }
                    numberOfMatches = 1;
                }
                lastCell = gameBoard[row][column];
            }
        }
        
        // Vertical matching
        for (auto column = 0; column < gameBoard.columns; column++) {
            int numberOfMatches = 0;
            auto lastCell = gameBoard[0][column];
            for (auto row = 0; row < gameBoard.rows; row++) {
                if (lastCell == gameBoard[row][column]) {
                    numberOfMatches++;
                } else {
                    if (numberOfMatches >= 3) {
                        score += numberOfMatches + (numberOfMatches >= 4 ? 5 : 0);
                        int prevRow = row-numberOfMatches-1;
                        while (prevRow >= 0) {
                            gameBoard[prevRow+numberOfMatches][column] = gameBoard[prevRow][column];
                            prevRow--;
                        }
                        
                        for (auto i = 0; i < numberOfMatches; i++) {
                            gameBoard[i][column] = randomCell();
                        }
                        
                    }
                    numberOfMatches = 1;
                }
                lastCell = gameBoard[row][column];
            }
        }
        
    }
public:
    
    CandyCrush() {
        clearAllMatches();
        score = 0;
    }
    
    const auto& getGameBoard() const {
        return gameBoard;
    }
    
    bool operator==(const CandyCrush & game) const {
        return numberOfMovesLeft == game.numberOfMovesLeft && gameBoard == game.gameBoard;
    }
    
    int getScore() const {
        return score;
    }
    
    bool play(GameBoard::CellSwapMove move) {
        if (isLegalMove(move) && !gameOver()) {
            performMove(move);
            clearAllMatches();
            numberOfMovesLeft--;
            return true;
        }
        return false;
    }
    
    bool gameOver() const {
        return numberOfMovesLeft <= 0 || legalMoves().empty();
    }
    
    std::vector<GameBoard::CellSwapMove> legalMoves() const {
        std::vector<GameBoard::CellSwapMove> moves;
            for (auto row = 0 ; row < gameBoard.rows; row++) {
                for (auto column = 0; column < gameBoard.columns; column++) {
                    GameBoard::CellPosition cell(row, column);
                    for (auto direction: {GameBoard::Up, GameBoard::Right, GameBoard::Down, GameBoard::Left}) {
                        auto adjacentCell = cell.cellAtDirection(direction);
                        if (isLegalMove(GameBoard::CellSwapMove(cell, adjacentCell))) {
                            moves.push_back(GameBoard::CellSwapMove(cell, adjacentCell));
                        }
                    }
                }
            }
        return moves;
    }
    
    static int run(CandyCrushPlayer& player, bool showOutput = false) {
        auto game = CandyCrush();
        while (!game.gameOver()) {
            if (showOutput) {
                std::cout << game;
            }
            game.play(player.selectMove(game));
        }
        std::cout << game;
        return game.score;
    }
    
    static int run(CandyCrushPlayer& player, int numberOfGames) {
        auto totalScore = 0;
        for (int i = 0; i < numberOfGames; i++) {
            totalScore += run(player);
        }
        std::cout << "Average score: " << totalScore / numberOfGames << std::endl;
        return totalScore / numberOfGames;
    }
    
    CandyCrush gameForMove(GameBoard::CellSwapMove move) const {
        auto nextGame = *this;
        nextGame.play(move);
        return nextGame;
    }
};

namespace std {
    
    template <>
    struct hash<CandyCrush>
    {
        std::size_t operator()(const CandyCrush& k) const
        {
            using std::size_t;
            using std::hash;
            using std::string;
            
            
            
            // Compute individual hash values for first,
            // second and third and combine them using XOR
            // and bit shifting:
            
            
            auto& gameBoard = k.getGameBoard();
            std::size_t seed = k.numberOfMovesLeft;
            
            for (auto row = 0; row < gameBoard.rows; row++) {
                for (auto column = 0; column < gameBoard.columns; column++) {
                        seed ^= gameBoard[row][column] + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                }
            }
            
            
            return seed;
            return 0;
            return k.numberOfMovesLeft;
        }
    };
}

std::ostream& operator<<(std::ostream& os, const CandyCrush& game) {
    os << "--------------------" << std::endl;
    os << "Moves left: " << game.numberOfMovesLeft << std::endl;
    os << "Score: " << game.score << std::endl;
    std::unordered_map<CandyCrush::Cell, std::string> cellString {
        {CandyCrush::Green, "O"},
        {CandyCrush::Blue, "-"},
        {CandyCrush::Orange, "$"},
        {CandyCrush::Red, "@"},
        //{CandyCrush::Purple, "!"}
    };
    
    std::cout << std::endl;
    for (auto i = 0; i < game.gameBoard.rows; i++) {
        for (auto j = 0; j < game.gameBoard.columns; j++) {
            os << cellString[game.gameBoard[i][j]] << " ";
        }
        os << std::endl;
    }
    std::cout << std::endl;
    
    return os;
}


class CandyCrushRandomBot: public CandyCrushPlayer {
public:
    GameBoard::CellSwapMove selectMove(const CandyCrush& game) {
        return RandomBot<GameBoard::CellSwapMove>().selectMove(game);
    }
    
    std::string description() const {
        return RandomBot<GameBoard::CellSwapMove>().description();
    }
};


class CandyCrushHumanPlayer: public CandyCrushPlayer {
public:
    GameBoard::CellSwapMove selectMove(const CandyCrush& game) {
        return HumanPlayer<GameBoard::CellSwapMove>().selectMove(game);
    }
    
    std::string description() const {
        return HumanPlayer<GameBoard::CellSwapMove>().description();
    }
};


// Selects the move that gives the highest score
class CandyCrushGreedyBot: public CandyCrushPlayer {
public:
    GameBoard::CellSwapMove selectMove(const CandyCrush& game) {
        auto legalMoves = game.legalMoves();
        GameBoard::CellSwapMove bestMove = legalMoves[0];
        auto bestMoveScore = -1;
        for (auto move: legalMoves) {
            auto score = game.gameForMove(move).getScore();
            if (score > bestMoveScore) {
                bestMoveScore = score;
                bestMove = move;
            }
        }
        return bestMove;
    }
    
    std::string description() const {
        return "Greedy bot - selects the next move that maximises immediate score";
    }
};


class CandyCrushMonteCarloBot: public CandyCrushPlayer {
public:
    
    mutable std::unordered_map<CandyCrush, int> totalScore;
    mutable std::unordered_map<CandyCrush, int> numberOfGames;
    
    ~CandyCrushMonteCarloBot() {
        std::cout << "Number of states in monte carlo: " << numberOfGames.size() << std::endl;
//        for (auto games: numberOfGames) {
//            std::cout << games.second << " - " << totalScore[games.first] << std::endl;
//        }
    }
    
    void simulate(const CandyCrush& game) const {
        std::unordered_set<CandyCrush> visitedStates;
        visitedStates.insert(game);
        
        CandyCrush nextState = game;
        
        while (!nextState.gameOver()) {
            auto legalMoves = nextState.legalMoves();
            nextState = nextState.gameForMove(legalMoves[rand() % legalMoves.size()]);
            visitedStates.insert(nextState);
        }
        
        for (auto state: visitedStates) {
            numberOfGames[state]++;
            totalScore[state] += state.getScore();
        }
        
    }
    
    GameBoard::CellSwapMove selectMove(const CandyCrush& game) {
        
        std::vector<std::pair<GameBoard::CellSwapMove, CandyCrush>> nextStates;
        for (auto move: game.legalMoves()) {
            auto nextState = game.gameForMove(move);
            nextStates.push_back(std::pair<GameBoard::CellSwapMove, CandyCrush>(move, nextState));
        }
        
        for (auto i = 0; i < 3; i++) {
            for (auto nextState: nextStates) {
                simulate(nextState.second);
            }
        }
        
        auto bestWinPercentage = -1;
        
        auto bestMove = nextStates[0].first;
        for (auto nextStateAndMove: nextStates) {
            auto nextState = nextStateAndMove.second;
            if (numberOfGames.find(nextState) != numberOfGames.end()) {
                //std::cout << "Hm:" << " - " << numberOfGames[nextState] << " - " << totalScore[nextStateAndMove.second] << std::endl;
                
                auto winPercentage = totalScore[nextState] / (double)numberOfGames[nextState];
                if (winPercentage > bestWinPercentage) {
                    bestWinPercentage = winPercentage;
                    bestMove = nextStateAndMove.first;
                }
            }
        }

        if (game.gameOver()) {
            numberOfGames.clear();
            totalScore.clear();
        }
        return bestMove;
    }
    
    std::string description() const {
        return "Monte Carlo";
    }
};

#endif /* CandyCrush_hpp */

