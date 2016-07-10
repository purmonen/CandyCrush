//
//  CandyCrushPlayer.hpp
//  ticTacToe
//
//  Created by Sami Purmonen on 11/07/16.
//  Copyright © 2016 Sami Purmonen. All rights reserved.
//

#ifndef CandyCrushPlayer_hpp
#define CandyCrushPlayer_hpp


#include "GameBoard.hpp"
#include "CandyCrush.hpp"


class CandyCrushRandomBot: public CandyCrushPlayer {
public:
    GameBoard::CellSwapMove selectMove(const CandyCrush& game);
    std::string description() const;
};


class CandyCrushHumanPlayer: public CandyCrushPlayer {
public:
    GameBoard::CellSwapMove selectMove(const CandyCrush& game);
    std::string description() const;
};


// Selects the move that gives the highest score
class CandyCrushGreedyBot: public CandyCrushPlayer {
public:
    GameBoard::CellSwapMove selectMove(const CandyCrush& game);
    std::string description() const;
};


class CandyCrushMonteCarloBot: public CandyCrushPlayer {
public:
    mutable std::unordered_map<CandyCrush, int> totalScore;
    mutable std::unordered_map<CandyCrush, int> numberOfGames;
    ~CandyCrushMonteCarloBot();
    void simulate(const CandyCrush& game) const;
    
    GameBoard::CellSwapMove selectMove(const CandyCrush& game);
    std::string description() const;
};


#endif /* CandyCrushPlayer_hpp */

