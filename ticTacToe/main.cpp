
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "CandyCrush.hpp"
#include "TicTacToe.hpp"
#include <chrono>

void testGameHashing() {
    std::unordered_map<CandyCrush, int> counts;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    /*
     * multiple iterations of the code you want to benchmark -
     * make sure the optimizer doesn't eliminate the whole code
     */
    
    
    
    for (auto i = 0; i < 2000; i++) {
        CandyCrush game;
        while (!game.gameOver()) {
            counts[game]++;
            auto legalMoves = game.legalMoves();
            auto move = legalMoves[0];
            game.play(move);
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    
    std::cout << "Execution time (us): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    
    std::cout << "Hashed games: " << counts.size() << std::endl;
    
    
}

int main(int argc, const char * argv[]) {
    
//    testGameHashing();
//    return 0;
    
    // Program:
    // 1. Select game
    // 2. Select who will play the game
    
    while (true) {
        int selectedGameIndex = -1;
        while (selectedGameIndex > 2 || selectedGameIndex < 1) {
            std::cout << "Select game: " << std::endl;
            std::cout << "1. Candy Crush" << std::endl;
            std::cout << "2. Tic Tac Toe" << std::endl;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cin >> selectedGameIndex;
        }
        
        if (selectedGameIndex == 1) {
            
            // Player<Game<GameBoardMove>>
            
            auto randomBot = CandyCrushRandomBot();
            auto humanPlayer = CandyCrushHumanPlayer();
            auto greedyBot = CandyCrushGreedyBot();
            auto monteCarloBot = CandyCrushMonteCarloBot();
            std::vector<CandyCrushPlayer*> players = {&randomBot, &humanPlayer, &greedyBot, &monteCarloBot};
            //std::vector<Player<Game<GameBoardMove>>* > players;
            int selectedPlayerIndex = -1;
            
            while (selectedPlayerIndex < 0 || selectedPlayerIndex > players.size()) {
                std::cout << "Select player:" << std::endl;
                for (auto index = 0; index < players.size(); index++) {
                    std::cout << index+1 << ". " << players[index]->description() << std::endl;
                }
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                std::cin >> selectedPlayerIndex;
                selectedPlayerIndex--;
                
            }
            if (selectedPlayerIndex >= 0 && selectedPlayerIndex < players.size()) {
                CandyCrush::run(*players[selectedPlayerIndex], 20);
            }
        } else if (selectedGameIndex == 2) {
            auto randomBot = TicTacToeRandomBot();
            auto humanPlayer = TicTacToeHumanPlayer();
            auto minimaxBot = MiniMaxBot();
            auto monteCarlo = MonteCarloBot();
            std::vector<TicTacToePlayer*>  players = {&randomBot, &humanPlayer, &minimaxBot, &monteCarlo};
            
            int firstPlayerIndex = -1;
            
            while (firstPlayerIndex < 0 || firstPlayerIndex > players.size()) {
                std::cout << "Select first player:" << std::endl;
                for (auto index = 0; index < players.size(); index++) {
                    std::cout << index+1 << ". " << players[index]->description() << std::endl;
                }
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                std::cin >> firstPlayerIndex;
                firstPlayerIndex--;
            }
            
            int secondPlayerIndex = -1;
            while (secondPlayerIndex < 0 || secondPlayerIndex > players.size()) {
                
                std::cout << "Select second player:" << std::endl;
                for (auto index = 0; index < players.size(); index++) {
                    std::cout << index+1 << ". " << players[index]->description() << std::endl;
                }
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                std::cin >> secondPlayerIndex;
                secondPlayerIndex--;
            }
            
            if (firstPlayerIndex >= 0 && firstPlayerIndex < players.size() && secondPlayerIndex >= 0 && secondPlayerIndex < players.size()) {
                TicTacToe::run(*players[firstPlayerIndex], *players[secondPlayerIndex]);
            }
        }
    }
    
    
    
    return 0;
}




class A {};
class B: public A {};


template<typename T>
class C {};

template<typename T>
class D: public C<T> {};

void a() {
    std::vector<A*> x;
    x.push_back(new B());
    x.push_back(new A());
    
    
    auto d1 = D<int>();
    auto c1 = C<int>();
    std::vector<C<int>*> y = {&d1, &c1};
}


