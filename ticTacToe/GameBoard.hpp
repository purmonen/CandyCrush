#ifndef GameBoard_hpp
#define GameBoard_hpp

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>


namespace GameBoard {
    
    enum Direction {Up, Right, Down, Left};
    
    struct CellPosition {
        size_t row;
        size_t column;
        
        CellPosition(size_t row, size_t column): row(row), column(column) {}
        
        CellPosition cellAtDirection(Direction direction) {
            switch (direction) {
                case Up: return CellPosition(row-1, column);
                case Right: return CellPosition(row, column+1);
                case Down: return CellPosition(row+1, column);
                case Left: return CellPosition(row, column-1);
            }
        }
        
        bool operator ==(const CellPosition& position) const {
            return row == position.row && column == position.column;
        }
    };
    
    std::ostream& operator<<(std::ostream& os, const CellPosition& cellPosition);
    
    struct CellSwapMove {
        CellPosition from;
        CellPosition to;
        
        CellSwapMove(CellPosition from, CellPosition to): from(from), to(to) {}
    };
    
    std::ostream& operator<<(std::ostream& os, const CellSwapMove& move);
    
    template<size_t ROWS, size_t COLUMNS, typename CellType>
    class GameBoard {
    private:
        CellType gameBoard[ROWS][COLUMNS];
    public:
        
        size_t rows = ROWS;
        size_t columns = COLUMNS;
        
        GameBoard(const std::function<CellType(size_t, size_t)> defaultValueForCell) {
            performActionOnCell([&](auto row, auto column, auto& cell) {
                cell = defaultValueForCell(row, column);
            });
        }
        
        GameBoard(const CellType defaultValue) {
            performActionOnCell([&](auto row, auto column, auto& cell) {
                cell = defaultValue;
            });
        }
        
        CellType* operator[](const size_t index) {
            return gameBoard[index];
        }
        
        
        const CellType* operator[](const size_t index) const {
            return gameBoard[index];
        }
        
        
        CellType& operator[](const CellPosition cell) {
            return gameBoard[cell.row][cell.column];
        }
        
        const CellType& operator[](const CellPosition cell) const {
            return gameBoard[cell.row][cell.column];
        }
        
        void swapCells(const CellSwapMove cellSwapMove) {
            swapCells(cellSwapMove.from, cellSwapMove.to);
        }
        
        void swapCells(const CellPosition firstCell, const CellPosition secondCell) {
            std::swap((*this)[firstCell], (*this)[secondCell]);
        }
        
        bool isCellValid(CellPosition cell) const {
            return cell.row >= 0 && cell.row < rows && cell.column >= 0 && cell.column < columns;
        }
        
        void performActionOnCell(const std::function<void(size_t, size_t, CellType&)> action) {
            for (auto rowIndex = 0; rowIndex < rows; rowIndex++) {
                for (auto columnIndex = 0; columnIndex < columns; columnIndex++) {
                    action(rowIndex, columnIndex, (*this)[rowIndex][columnIndex]);
                }
            }
        }
        
        bool operator==(const GameBoard & gameBoard) const {
            if (rows != gameBoard.rows || columns != gameBoard.columns) {
                return false;
            }
            for (auto i = 0; i < rows; i++) {
                for (auto j = 0; j < columns; j++) {
                    if ((*this)[i][j] != gameBoard[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }
    };
}

#endif /* GameBoard_hpp */
