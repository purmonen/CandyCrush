#include "TicTacToe.hpp"


bool TicTacToe::isWhitePlayersTurn() const {
        return whitePlayersTurn;
    }
    
bool TicTacToe::play(GameBoard::CellPosition cellPosition) {
        return play(cellPosition.row, cellPosition.column);
    }
    
bool TicTacToe::play(const size_t row, const size_t column) {
        if (gameBoard[row][column] != Empty) {
            return false;
        }
        gameBoard[row][column] = whitePlayersTurn ? White : Black;
        whitePlayersTurn = !whitePlayersTurn;
        return true;
    }
    
TicTacToe::GameResult TicTacToe::gameResult() const {
    for (const auto cell: {TicTacToe::White, TicTacToe::Black}) {
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
    
std::vector<GameBoard::CellPosition> TicTacToe::legalMoves() const {
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
    
TicTacToe TicTacToe::gameForMove(GameBoard::CellPosition move) const {
        auto nextGame = *this;
        nextGame.play(move.row, move.column);
        return nextGame;
    }
    
bool TicTacToe::operator==(const TicTacToe & game) const {
        return isWhitePlayersTurn() == game.isWhitePlayersTurn() && gameBoard == game.gameBoard;
    }
    
bool TicTacToe::gameOver() const {
        return gameResult() != Running;
    }
    
TicTacToe::GameResult TicTacToe::run(TicTacToePlayer& whitePlayer, TicTacToePlayer& blackPlayer, bool showOutput) {
        auto game = TicTacToe();
        while (!game.gameOver()) {
            if (showOutput) {
                std::cout << game;
            }
            game.play((game.isWhitePlayersTurn() ? whitePlayer : blackPlayer).selectMove(game));
        }
    
    if (showOutput) {
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
            case Running:
                // Can't happen when game is over
                throw;
        }
    }
        return game.gameResult();
    }


TicTacToe::TestResult TicTacToe::runMany(TicTacToePlayer& whitePlayer, TicTacToePlayer& blackPlayer, int numberOfGames) {
    TicTacToe::TestResult result;
    for (auto i = 0; i < numberOfGames; i++) {
        auto gameResult = TicTacToe::run(whitePlayer, blackPlayer, false);
        switch (gameResult) {
            case TicTacToe::Win:
                result.wins++;
                break;
            case TicTacToe::Loss:
                result.losses++;
                break;
            case TicTacToe::Draw:
                result.draws++;
                break;
            case TicTacToe::Running:
                // Can't happen when game is over
                throw;
        }
    }
    return result;
}

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

