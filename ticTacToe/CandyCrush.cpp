#include "CandyCrush.hpp"

CandyCrush::Cell CandyCrush::randomCell() {
    std::vector<CandyCrush::Cell> cells = {Green, Blue, Orange, Red};
    return cells[rand() % cells.size()];
}

// When randomly generating new cells some of them will create matches that must be cleared after each move and when initializing the game
void CandyCrush::clearAllMatches() {
    while (isLegalMove(GameBoard::CellSwapMove(GameBoard::CellPosition(0,0), GameBoard::CellPosition(0,0)))) {
        performMove(GameBoard::CellSwapMove(GameBoard::CellPosition(0,0), GameBoard::CellPosition(0,0)));
    }
}

bool CandyCrush::isLegalMove(GameBoard::CellSwapMove move) const {
    if (!gameBoard.isCellValid(move.from) || !gameBoard.isCellValid(move.to)) {
        return false;
    }
    
    // Perform the move on a copy of the game
    auto game = *this;
    game.performMove(move);
    
    // All legal moves increases score!
    return game.score != score;
}

int CandyCrush::scoreForMatches(int numberOfMatches) {
    return numberOfMatches + (numberOfMatches >= 4 ? 5 : 0);
}

void CandyCrush::performMove(GameBoard::CellSwapMove move) {
    
    // Move pieces
    gameBoard.swapCells(move);
    
    // Horizontal matching
    for (auto row = 0; row < gameBoard.rows; row++) {
        int numberOfMatches = 0;
        auto lastCell = gameBoard[row][0];
        for (auto column = 0; column < gameBoard.columns; column++) {
            if (lastCell == gameBoard[row][column]) {
                numberOfMatches++;
            } else {
                if (numberOfMatches >= 3) {
                    score += scoreForMatches(numberOfMatches);
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
                    score += scoreForMatches(numberOfMatches);
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

CandyCrush::CandyCrush() {
    clearAllMatches();
    score = 0;
}

const GameBoard::GameBoard<6, 6, CandyCrush::Cell>& CandyCrush::getGameBoard() const {
    return gameBoard;
}

bool CandyCrush::operator==(const CandyCrush & game) const {
    return numberOfMovesLeft == game.numberOfMovesLeft && gameBoard == game.gameBoard;
}

int CandyCrush::getScore() const {
    return score;
}

int CandyCrush::getNumberOfMovesLeft() const {
    return numberOfMovesLeft;
}

bool CandyCrush::play(GameBoard::CellSwapMove move) {
    if (isLegalMove(move) && !gameOver()) {
        performMove(move);
        clearAllMatches();
        numberOfMovesLeft--;
        return true;
    }
    return false;
}

bool CandyCrush::gameOver() const {
    return numberOfMovesLeft <= 0 || legalMoves().empty();
}

std::vector<GameBoard::CellSwapMove> CandyCrush::legalMoves() const {
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

 int CandyCrush::run(CandyCrushPlayer& player, bool showOutput = false) {
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

 int CandyCrush::run(CandyCrushPlayer& player, int numberOfGames) {
    auto totalScore = 0;
    for (int i = 0; i < numberOfGames; i++) {
        totalScore += run(player);
    }
    std::cout << "Average score: " << totalScore / numberOfGames << std::endl;
    return totalScore / numberOfGames;
}

CandyCrush CandyCrush::gameForMove(GameBoard::CellSwapMove move) const {
    auto nextGame = *this;
    nextGame.play(move);
    return nextGame;
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