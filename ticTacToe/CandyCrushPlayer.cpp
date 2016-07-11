#include "CandyCrushPlayer.hpp"
#include "CandyCrush.hpp"

GameBoard::CellSwapMove CandyCrushRandomBot::selectMove(const CandyCrush& game) {
    return RandomBot<GameBoard::CellSwapMove>().selectMove(game);
}

std::string CandyCrushRandomBot::description() const {
    return RandomBot<GameBoard::CellSwapMove>().description();
}


GameBoard::CellSwapMove CandyCrushHumanPlayer::selectMove(const CandyCrush& game) {
    return HumanPlayer<GameBoard::CellSwapMove>().selectMove(game);
}

std::string CandyCrushHumanPlayer::description() const {
    return HumanPlayer<GameBoard::CellSwapMove>().description();
}


// Selects the move that gives the highest score
GameBoard::CellSwapMove CandyCrushGreedyBot::selectMove(const CandyCrush& game) {
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

std::string CandyCrushGreedyBot::description() const {
    return "Greedy";
}


CandyCrushMonteCarloBot::~CandyCrushMonteCarloBot() {
//    std::cout << "Number of states in monte carlo: " << numberOfGames.size() << std::endl;
    //        for (auto games: numberOfGames) {
    //            std::cout << games.second << " - " << totalScore[games.first] << std::endl;
    //        }
}

void CandyCrushMonteCarloBot::simulate(const CandyCrush& game) const {
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

GameBoard::CellSwapMove CandyCrushMonteCarloBot::selectMove(const CandyCrush& game) {
    
    std::vector<std::pair<GameBoard::CellSwapMove, CandyCrush>> nextStates;
    for (auto move: game.legalMoves()) {
        auto nextState = game.gameForMove(move);
        nextStates.push_back({move, nextState});
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

std::string CandyCrushMonteCarloBot::description() const {
    return "Monte Carlo";
}

