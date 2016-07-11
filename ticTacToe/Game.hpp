#ifndef Game_hpp
#define Game_hpp


template <typename MoveType>
class Game {
public:
    virtual std::vector<MoveType> legalMoves() const = 0;
    virtual bool play(MoveType move) = 0;
    virtual bool gameOver() const = 0;
//    virtual Game gameForMove(MoveType) = 0;
};

template <typename MoveType>
class Player {
public:
    virtual MoveType selectMove(const Game<MoveType>&) = 0;
    virtual std::string description() const = 0;
};

template <typename MoveType>
class RandomBot: public Player<MoveType> {
public:
    MoveType selectMove(const Game<MoveType>& game) {
        auto legalMoves = game.legalMoves();
        return legalMoves[rand()%legalMoves.size()];
    }
    
    std::string description() const {
        return "Random";
    }
};

template <typename MoveType>
class HumanPlayer: public Player<MoveType> {
public:
    MoveType selectMove(const Game<MoveType>& game) {
        auto legalMoves = game.legalMoves();
        int moveIndex;
        
        std::cout << legalMoves.size() << " legal moves" << std::endl;
        for (auto i = 0; i < legalMoves.size(); i++) {
            auto legalMove = legalMoves[i];
            std::cout << i << ". " << legalMove << std::endl;
        }
        
        std::cout << "Select move: ";
        std::cin >> moveIndex;
        
        if (moveIndex >= 0 && moveIndex < legalMoves.size()) {
            return legalMoves[moveIndex];
        } else {
            std::cout << "Illegal move" << std::endl;
            return selectMove(game);
        }
    }
    
    std::string description() const {
        return "You";
    }
};


#endif /* Game_hpp */

