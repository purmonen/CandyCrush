//#include "CandyCrushPlayer.hpp"
//#include "CandyCrush.hpp"
//
//GameBoard::CellSwapMove CandyCrushRandomBot::selectMove(const CandyCrush& game) {
//    return RandomBot<GameBoard::CellSwapMove>().selectMove(game);
//}
//
//std::string CandyCrushRandomBot::description() const {
//    return RandomBot<GameBoard::CellSwapMove>().description();
//}
//
//
//GameBoard::CellSwapMove CandyCrushHumanPlayer::selectMove(const CandyCrush& game) {
//    return HumanPlayer<GameBoard::CellSwapMove>().selectMove(game);
//}
//
//std::string CandyCrushHumanPlayer::description() const {
//    return HumanPlayer<GameBoard::CellSwapMove>().description();
//}
//
//
//// Selects the move that gives the highest score
//GameBoard::CellSwapMove CandyCrushGreedyBot::selectMove(const CandyCrush& game) {
//    auto legalMoves = game.legalMoves();
//    GameBoard::CellSwapMove bestMove = legalMoves[0];
//    auto bestMoveScore = -1;
//    for (auto move: legalMoves) {
//        auto score = game.gameForMove(move).getScore();
//        if (score > bestMoveScore) {
//            bestMoveScore = score;
//            bestMove = move;
//        }
//    }
//    return bestMove;
//}
//
//std::string CandyCrushGreedyBot::description() const {
//    return "Greedy";
//}
//
//CandyCrushMonteCarloBot::~CandyCrushMonteCarloBot() {}
//
//void CandyCrushMonteCarloBot::simulate(const CandyCrush& game) const {
//    std::unordered_set<CandyCrush> visitedStates;
//    visitedStates.insert(game);
//    
//    CandyCrush nextState = game;
//    
//    while (!nextState.gameOver()) {
//        auto legalMoves = nextState.legalMoves();
//        auto bestNextState = nextState.gameForMove(legalMoves[0]);
//        auto bestNextStateValue = std::numeric_limits<int>::min();
//        for (auto move: legalMoves) {
//            auto possibleNextState = nextState.gameForMove(move);
//            
//            // Expand nodes if there are unexplored ones
//            if (numberOfGames.find(possibleNextState) == numberOfGames.end()) {
//                bestNextState = possibleNextState;
//                break;
//            }
//            
//            // Otherwise select the one with best upper confidence bound
//            auto c = 1;
//            auto value = totalScore[possibleNextState] / ((double)numberOfGames[possibleNextState]) + c * sqrt((log((double)numberOfGames[nextState]) / ((double)numberOfGames[possibleNextState])));
//            if (value > bestNextStateValue) {
//                bestNextStateValue = value;
//                bestNextState = possibleNextState;
//            }
//        }
//        
//        nextState = bestNextState;
//        visitedStates.insert(nextState);
//    }
//    
//    for (auto state: visitedStates) {
//        numberOfGames[state]++;
//        totalScore[state] += state.getScore();
//    }
//    
//}
//
//GameBoard::CellSwapMove CandyCrushMonteCarloBot::selectMove(const CandyCrush& game) {
//    
//    std::vector<std::pair<GameBoard::CellSwapMove, CandyCrush>> nextStates;
//    for (auto move: game.legalMoves()) {
//        auto nextState = game.gameForMove(move);
//        nextStates.push_back({move, nextState});
//    }
//    
//    for (auto i = 0; i < 2; i++) {
//        for (auto nextState: nextStates) {
//            simulate(nextState.second);
//        }
//    }
//    
//    auto bestWinPercentage = -1;
//    auto bestMove = nextStates[0].first;
//    for (auto nextStateAndMove: nextStates) {
//        auto nextState = nextStateAndMove.second;
//        if (numberOfGames.find(nextState) != numberOfGames.end()) {
//            auto winPercentage = (double)totalScore[nextState]/(double)numberOfGames[nextState];
//            if (winPercentage > bestWinPercentage) {
//                bestWinPercentage = winPercentage;
//                bestMove = nextStateAndMove.first;
//            }
//        }
//    }
//    
//    if (game.gameOver()) {
//        numberOfGames.clear();
//        totalScore.clear();
//    }
//    return bestMove;
//}
//
//
//std::string CandyCrushMonteCarloBot::description() const {
//    return "Monte Carlo";
//}
//
