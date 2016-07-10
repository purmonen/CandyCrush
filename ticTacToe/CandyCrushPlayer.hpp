//#ifndef CandyCrushPlayer_hpp
//#define CandyCrushPlayer_hpp
//
//
//#include "CandyCrush.hpp"
//
//class CandyCrushPlayer {
//public:
//    virtual GameBoardMove selectMove(const CandyCrush&)= 0;
//    virtual std::string description() const = 0;
//};
//
//class CandyCrushRandomBot: public CandyCrushPlayer {
//public:
//    GameBoardMove selectMove(const CandyCrush& game) {
//        return RandomBot<GameBoardMove>().selectMove(game);
//    }
//    
//    std::string description() const {
//        return RandomBot<GameBoardMove>().description();
//    }
//};
//
//
//class CandyCrushHumanPlayer: public CandyCrushPlayer {
//public:
//    GameBoardMove selectMove(const CandyCrush& game) {
//        return HumanPlayer<GameBoardMove>().selectMove(game);
//    }
//    
//    std::string description() const {
//        return HumanPlayer<GameBoardMove>().description();
//    }
//};
//
//
//// Selects the move that gives the highest score
//class CandyCrushGreedyBot: public CandyCrushPlayer {
//public:
//    GameBoardMove selectMove(const CandyCrush& game) {
//        auto legalMoves = game.legalMoves();
//        GameBoardMove bestMove = legalMoves[0];
//        auto bestMoveScore = -1;
//        for (auto move: legalMoves) {
//            auto score = game.gameForMove(move).getScore();
//            if (score > bestMoveScore) {
//                bestMoveScore = score;
//                bestMove = move;
//            }
//        }
//        return bestMove;
//    }
//    
//    std::string description() const {
//        return "Greedy bot - selects the next move that maximises immediate score";
//    }
//};
//
//class CandyCrushMonteCarloBot: public CandyCrushPlayer {
//public:
//    
//    mutable std::unordered_map<CandyCrush, int> totalScore;
//    mutable std::unordered_map<CandyCrush, int> numberOfGames;
//    
//    ~CandyCrushMonteCarloBot() {
//        std::cout << "Number of states in monte carlo: " << numberOfGames.size() << std::endl;
//        //        for (auto games: numberOfGames) {
//        //            std::cout << games.second << " - " << totalScore[games.first] << std::endl;
//        //        }
//    }
//    
//    void simulate(const CandyCrush& game) const {
//        std::unordered_set<CandyCrush> visitedStates;
//        visitedStates.insert(game);
//        
//        CandyCrush nextState = game;
//        
//        while (!nextState.gameOver()) {
//            auto legalMoves = nextState.legalMoves();
//            nextState = nextState.gameForMove(legalMoves[rand() % legalMoves.size()]);
//            visitedStates.insert(nextState);
//        }
//        
//        for (auto state: visitedStates) {
//            numberOfGames[state]++;
//            totalScore[state] += state.getScore();
//        }
//        
//    }
//    
//    GameBoardMove selectMove(const CandyCrush& game) {
//        
//        std::vector<std::pair<GameBoardMove, CandyCrush>> nextStates;
//        for (auto move: game.legalMoves()) {
//            auto nextState = game.gameForMove(move);
//            nextStates.push_back(std::pair<GameBoardMove, CandyCrush>(move, nextState));
//        }
//        
//        for (auto i = 0; i < 3; i++) {
//            for (auto nextState: nextStates) {
//                simulate(nextState.second);
//            }
//        }
//        
//        auto bestWinPercentage = -1;
//        
//        auto bestMove = nextStates[0].first;
//        for (auto nextStateAndMove: nextStates) {
//            auto nextState = nextStateAndMove.second;
//            if (numberOfGames.find(nextState) != numberOfGames.end()) {
//                //std::cout << "Hm:" << " - " << numberOfGames[nextState] << " - " << totalScore[nextStateAndMove.second] << std::endl;
//                
//                auto winPercentage = totalScore[nextState] / (double)numberOfGames[nextState];
//                if (winPercentage > bestWinPercentage) {
//                    bestWinPercentage = winPercentage;
//                    bestMove = nextStateAndMove.first;
//                }
//            }
//        }
//        
//        if (game.gameOver()) {
//            numberOfGames.clear();
//            totalScore.clear();
//        }
//        return bestMove;
//    }
//    
//    std::string description() const {
//        return "Monte Carlo";
//    }
//};
//
//#endif /* CandyCrushPlayer_hpp */
