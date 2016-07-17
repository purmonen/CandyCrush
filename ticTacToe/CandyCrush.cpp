#include "CandyCrush.hpp"

CandyCrush::Cell CandyCrush::randomCell() {
    std::vector<CandyCrush::Cell> cells = {Green, Blue, Purple, Red, Yellow};
    return cells[rand() % cells.size()];
}

// When randomly generating new cells some of them will create matches that must be cleared after each move and when initializing the game
void CandyCrush::clearAllMatches(GameBoardChangeCallback callback) {
    while (true) {
        auto oldScore = score;
        performMove(GameBoard::CellSwapMove(GameBoard::CellPosition(0,0), GameBoard::CellPosition(0,0)), callback);
        if (oldScore == score) {
            break;
        }
    }
}

bool CandyCrush::isLegalMove(GameBoard::CellSwapMove move) const {
    
    if (!gameBoard.isCellValid(move.from) || !gameBoard.isCellValid(move.to)) {
        return false;
    }
    
    auto adjacentCells = {move.from.cellAtDirection(GameBoard::Up), move.from.cellAtDirection(GameBoard::Right), move.from.cellAtDirection(GameBoard::Down), move.from.cellAtDirection(GameBoard::Left)};
    
    if (std::find(adjacentCells.begin(), adjacentCells.end(), move.to) == adjacentCells.end()) {
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

std::unordered_map<GameBoard::CellPosition, GameBoard::CellPosition> identityCellPositionMapForGameBoard(GameBoard::GameBoard<6, 6, CandyCrush::Cell> gameBoard) {
    std::unordered_map<GameBoard::CellPosition, GameBoard::CellPosition> cellPositions;
    for (auto row = 0; row < gameBoard.rows; row++) {
        for (auto column = 0; column < gameBoard.columns; column++) {
            cellPositions[GameBoard::CellPosition(row, column)] = GameBoard::CellPosition(row, column);
        }
    }
    return cellPositions;
}

void CandyCrush::performMove(GameBoard::CellSwapMove move, GameBoardChangeCallback callback) {
    
    std::unordered_map<GameBoard::CellPosition, GameBoard::CellPosition> cellPositions = identityCellPositionMapForGameBoard(gameBoard);
    std::unordered_set<GameBoard::CellPosition> removedCells;
    std::vector<std::tuple<GameBoard::CellPosition, CandyCrush::Cell, int>> newCells;
    
    cellPositions[move.from] = move.to;
    cellPositions[move.to] = move.from;
    
    if (callback != nullptr) {
        std::cout << "Callback should block for a second!" << std::endl;
        callback(CandyCrushGameBoardChange(cellPositions, removedCells, *this, newCells));
    }
    
    newCells.clear();
    removedCells.clear();
    cellPositions = identityCellPositionMapForGameBoard(gameBoard);
    
    // Move pieces
    gameBoard.swapCells(move);
    std::cout << "Proceeding!" << std::endl;
    
    
    // Horizontal matching
    for (auto row = 0; row < gameBoard.rows; row++) {
        int numberOfMatches = 0;
        auto lastCell = gameBoard[row][0];
        for (auto column = 0; column < gameBoard.columns; column++) {
            bool cellsMatched = lastCell == gameBoard[row][column];
            if (cellsMatched) {
                numberOfMatches++;
            }
        
            if ((!cellsMatched || column == gameBoard.rows -1 ) && numberOfMatches >= 3) {
                score += scoreForMatches(numberOfMatches);
                
                
//                GameBoard::GameBoard<6, 6, CandyCrush::Cell> oldGameBoard = gameBoard;
                
                CandyCrush oldGame = *this;
                for (auto matchedColumn = column-numberOfMatches; matchedColumn < column; matchedColumn++) {
                    removedCells.insert(GameBoard::CellPosition(row, matchedColumn));
                    for (auto matchedRow = row-1; matchedRow >= 0; matchedRow--) {
                        cellPositions[GameBoard::CellPosition(matchedRow, matchedColumn)] = GameBoard::CellPosition(matchedRow+1, matchedColumn);
                        gameBoard[matchedRow+1][matchedColumn] = gameBoard[matchedRow][matchedColumn];
                    }
                    gameBoard[0][matchedColumn] = randomCell();
                    
                    newCells.push_back({GameBoard::CellPosition(0, matchedColumn), gameBoard[0][matchedColumn], 1});
                }
                
                if (callback != nullptr) {
                    callback(CandyCrushGameBoardChange(cellPositions, removedCells, oldGame, newCells));
                    
                    std::cout << oldGame << std::endl;
                    
                    std::cout << *this << std::endl;
                    for (auto x: cellPositions) {
                        if (!(x.first == x.second)) {
                            std::cout << x.first << " ______" << x.second << std::endl;
                        }
                    }
                    std::cout << "BREAK!" << (gameBoard == oldGame.gameBoard) << std::endl;
                }
                newCells.clear();
                removedCells.clear();
                cellPositions = identityCellPositionMapForGameBoard(gameBoard);
            }
            
            if (!cellsMatched) {
                

                
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
            bool cellsMatched = lastCell == gameBoard[row][column];
            if (cellsMatched) {
                numberOfMatches++;
            }
            if ((!cellsMatched || row == gameBoard.rows-1) && numberOfMatches >= 3) {
                score += scoreForMatches(numberOfMatches);
                int prevRow = row-numberOfMatches-1;
                auto oldGame = *this;
                while (prevRow >= 0) {
                    cellPositions[GameBoard::CellPosition(prevRow, column)] = GameBoard::CellPosition(prevRow+numberOfMatches, column);
                    gameBoard[prevRow+numberOfMatches][column] = gameBoard[prevRow][column];
                    prevRow--;
                }
                
                for (auto i = 0; i < numberOfMatches; i++) {
                    gameBoard[i][column] = randomCell();
                    newCells.push_back({GameBoard::CellPosition(i, column), gameBoard[i][column], numberOfMatches});
                }
                
                int matchedRow = row;
                if (!cellsMatched) {
                    matchedRow--;
                }
                for (auto i = 0; i < numberOfMatches; i++) {
                    removedCells.insert(GameBoard::CellPosition(matchedRow, column));
                    matchedRow--;
                }
                
                if (callback != nullptr) {
                    callback(CandyCrushGameBoardChange(cellPositions, removedCells, oldGame, newCells));
                }
                newCells.clear();
                removedCells.clear();
                cellPositions = identityCellPositionMapForGameBoard(gameBoard);
            }
        
            
            if (!cellsMatched) {
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

bool CandyCrush::play(GameBoard::CellSwapMove move, GameBoardChangeCallback callback) {
    if (isLegalMove(move) && !gameOver()) {
        performMove(move, callback);
        clearAllMatches(callback);
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
    if (showOutput) {
        std::cout << game;
    }
    return game.score;
}

int CandyCrush::run(CandyCrushPlayer& player, int numberOfGames) {
    auto totalScore = 0;
    for (int i = 0; i < numberOfGames; i++) {
        totalScore += run(player, false);
    }
    //    std::cout << "Average score: " << totalScore / numberOfGames << std::endl;
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
        {CandyCrush::Green, "G"},
        {CandyCrush::Blue, "B"},
        {CandyCrush::Purple, "P"},
        {CandyCrush::Yellow, "Y"},
        {CandyCrush::Red, "R"},
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
