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
    
    bool isWhitePlayersTurn() const {
        return whitePlayersTurn;
    }
    
    bool play(GameBoard::CellPosition cellPosition) {
        return play(cellPosition.row, cellPosition.column);
    }
    
    bool play(const size_t row, const size_t column) {
        if (gameBoard[row][column] != Empty) {
            return false;
        }
        gameBoard[row][column] = whitePlayersTurn ? White : Black;
        whitePlayersTurn = !whitePlayersTurn;
        return true;
    }
    
    GameResult gameResult() const {
        for (const auto cell: {White, Black}) {
            for (auto i = 0; i < gameBoard.rows; i++) {
                auto hasWon = true;
                for (auto j = 0; j < gameBoard.columns; j++) {
                    if (gameBoard[i][j] != cell) { hasWon = false; }
                }
                if (hasWon) { return cell == White ? Win : Loss; }
            }
            for (auto j = 0; j < gameBoard.columns; j++) {
                auto hasWon = true;
                for (auto i = 0; i < gameBoard.rows; i++) {
                    if (gameBoard[i][j] != cell) { hasWon = false; }
                }
                if (hasWon) { return cell == White ? Win : Loss; }
            }
            {
                auto hasWon = true;
                for (auto i = 0; i < gameBoard.rows; i++) {
                    if (gameBoard[i][i] != cell) { hasWon = false; }
                }
                if (hasWon) { return cell == White ? Win : Loss; }
            };
            {
                auto hasWon = true;
                for (auto i = 0; i < gameBoard.rows; i++) {
                    if (gameBoard[gameBoard.rows-1-i][i] != cell) { hasWon = false; }
                }
                if (hasWon) { return cell == White ? Win : Loss; }
            };
        }
        for (auto i = 0; i < gameBoard.rows; i++) {
            for (auto j = 0; j < gameBoard.columns; j++) {
                if (gameBoard[i][j] == Empty) { return Running; }
            }
        }
        return Draw;
    }
    
    std::vector<GameBoard::CellPosition> legalMoves() const {
        std::vector<GameBoard::CellPosition> moves;
        for (auto i = 0; i < gameBoard.rows; i++) {
            for (auto j = 0; j < gameBoard.columns; j++) {
                if (gameBoard[i][j] == Empty) {
                    moves.push_back(GameBoard::CellPosition(i, j));
                }
            }
        }
        return moves;
    }
    
    TicTacToe gameForMove(GameBoard::CellPosition move) const {
        auto nextGame = *this;
        nextGame.play(move.row, move.column);
        return nextGame;
    }
    
    bool operator==(const TicTacToe & game) const {
        return isWhitePlayersTurn() == game.isWhitePlayersTurn() && gameBoard == game.gameBoard;
    }
    
    bool gameOver() const {
        return gameResult() != Running;
    }
    
    static GameResult run(TicTacToePlayer& whitePlayer, TicTacToePlayer& blackPlayer) {
        auto game = TicTacToe();
        while (!game.gameOver()) {
            std::cout << game;
            game.play((game.isWhitePlayersTurn() ? whitePlayer : blackPlayer).selectMove(game));
        }
        std::cout << game;
        switch (game.gameResult()) {
            case Win:
                std::cout << "White wins" << std::endl;
                break;
            case Loss:
                std::cout << "Black wins" << std::endl;
                break;
            case Draw:
                std::cout << "Draw" << std::endl;
                break;
        }
        return game.gameResult();
    }
    
    
    struct TestResult {
        int wins = 0;
        int losses = 0;
        int draws = 0;
        
        int numberOfGames() {
            return wins + losses + draws;
        }
    };
    //
    
//    static TestResult testBots(Player<TicTacToe>& firstPlayer, Player<TicTacToe>& secondPlayer, const int numberOfGames) {
//        
//        int whiteWins = 0;
//        int blackWins = 0;
//        int draws = 0;
//        
//        auto testResult = TestResult();
//        
//        for (auto i = 0; i < numberOfGames; i++) {
//            auto gameResult = TicTacToe::run(firstPlayer, secondPlayer);
//            
//            if (gameResult == TicTacToe::Win) {
//                testResult.wins++;
//                whiteWins++;
//            }
//            
//            if (gameResult == TicTacToe::Loss) {
//                testResult.losses++;
//                blackWins++;
//            }
//            
//            if (gameResult == TicTacToe::Draw) {
//                testResult.draws++;
//                draws++;
//            }
//        }
//        
//        std::cout << "White won: " << whiteWins / (double)numberOfGames * 100 << std::endl;
//        std::cout << "Black won: " << blackWins  / (double)numberOfGames * 100 << std::endl;
//        std::cout << "Draws: " << draws  / (double)numberOfGames * 100 << std::endl;
//        
//        
//        return testResult;
//    }
};

std::ostream& operator<<(std::ostream& os, const TicTacToe& game) {
    std::unordered_map<TicTacToe::Cell, std::string> cellString {
        {TicTacToe::White, "X"},
        {TicTacToe::Black, "O"},
        {TicTacToe::Empty, " "}
    };
    
    for (auto i = 0; i < game.gameBoard.rows; i++) {
        os << "-------";
        os << std::endl;
        os << "|";
        for (auto j = 0; j < game.gameBoard.columns; j++) {
            os << cellString[game.gameBoard[i][j]] << "|";
        }
        os << std::endl;
    }
    os << "-------";
    os << std::endl;
    return os;
}

namespace std {
    
    template <>
    struct hash<TicTacToe>
    {
        std::size_t operator()(const TicTacToe& k) const
        {
            using std::size_t;
            using std::hash;
            using std::string;
            
            // Compute individual hash values for first,
            // second and third and combine them using XOR
            // and bit shifting:
            
            return 0;
        }
    };
    
}

class TicTacToeRandomBot: public TicTacToePlayer {
public:
    GameBoard::CellPosition selectMove(const TicTacToe& game) {
        return RandomBot<GameBoard::CellPosition>().selectMove(game);
    }
    
    std::string description() const {
        return RandomBot<GameBoard::CellSwapMove>().description();
    }
};


class TicTacToeHumanPlayer: public TicTacToePlayer {
public:
    GameBoard::CellPosition selectMove(const TicTacToe& game) {
        return HumanPlayer<GameBoard::CellPosition>().selectMove(game);
    }
    
    std::string description() const {
        return HumanPlayer<GameBoard::CellSwapMove>().description();
    }
};

class MiniMaxBot: public TicTacToePlayer {
public:
    
    int scoreForGame(TicTacToe game) {
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
    
    GameBoard::CellPosition selectMove(const TicTacToe& game) {
        GameBoard::CellPosition bestMove = GameBoard::CellPosition(0,0);
        auto bestMoveScore = game.isWhitePlayersTurn() ? 999999 : -999999;
        for (auto move: game.legalMoves()) {
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
    
    std::string description() const {
        return "Minimax bot";
    }
};


class MonteCarloBot: public TicTacToePlayer {
public:

    mutable std::unordered_map<TicTacToe, int> numberOfWins;
    mutable std::unordered_map<TicTacToe, int> numberOfGames;

    void simulate(const TicTacToe game) const {
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

    GameBoard::CellPosition selectMove(const TicTacToe& game) {
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
    
    std::string description() const {
        return "Monte Carlo";
    }
};


#endif /* TicTacToe_hpp */
