
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "CandyCrush.hpp"
#include "CandyCrushPlayer.hpp"
#include "TicTacToe.hpp"
#include "TicTacToePlayer.hpp"
#include <chrono>

void testGameHashing() {
    std::unordered_map<CandyCrush, int> counts;
    
    auto start = std::chrono::high_resolution_clock::now();
    
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

void runCandyCrush() {
    int selectedPlayStyleIndex = -1;
    int playYourselfIndex = 1;
    int letBotsPlayIndex = 2;
    
    while (selectedPlayStyleIndex != playYourselfIndex && selectedPlayStyleIndex != letBotsPlayIndex) {
        std::cout << "How do you wanna play?" << std::endl;
        std::cout << "\t" << playYourselfIndex << ". Play yourself" << std::endl;
        std::cout << "\t" << letBotsPlayIndex << ". Let the bots play" << std::endl;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin >> selectedPlayStyleIndex;
    }
    
    if (selectedPlayStyleIndex == playYourselfIndex) {
        auto humanPlayer = CandyCrushHumanPlayer();
        CandyCrush::run(humanPlayer, true);
    } else if (selectedPlayStyleIndex == letBotsPlayIndex) {
        auto randomBot = CandyCrushRandomBot();
        auto greedyBot = CandyCrushGreedyBot();
        auto monteCarloBot = CandyCrushMonteCarloBot();
        std::vector<CandyCrushPlayer*> players = {&randomBot, &greedyBot, &monteCarloBot};
        for (auto player: players) {
            std::cout << "\t" << (player->description()) << ": " << CandyCrush::run(*player, 10) << " points" << std::endl;
        }
    }
}

void runTicTacToe() {
    int selectedPlayStyleIndex = -1;
    int playYourselfIndex = 1;
    int letBotsPlayIndex = 2;
    
    while (selectedPlayStyleIndex != playYourselfIndex && selectedPlayStyleIndex != letBotsPlayIndex) {
        std::cout << "How do you wanna play?" << std::endl;
        std::cout << "\t" << playYourselfIndex << ". Overview a game between two opponents (maybe yourself)" << std::endl;
        std::cout << "\t" << letBotsPlayIndex << ". Let all bots play against each other" << std::endl;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin >> selectedPlayStyleIndex;
    }
    
    
    auto humanPlayer = TicTacToeHumanPlayer();
    auto randomBot = TicTacToeRandomBot();
    auto minimaxBot = MiniMaxBot();
    auto monteCarlo = MonteCarloBot();
    
    std::vector<TicTacToePlayer*>  players = {&humanPlayer, &randomBot, &minimaxBot, &monteCarlo};
    std::vector<TicTacToePlayer*>  bots = {&randomBot, &minimaxBot, &monteCarlo};
    
    if (selectedPlayStyleIndex == playYourselfIndex) {
        int firstPlayerIndex = -1;
        while (firstPlayerIndex < 0 || firstPlayerIndex > players.size()) {
            std::cout << "Select first player:" << std::endl;
            for (auto index = 0; index < players.size(); index++) {
                std::cout << "\t" << index+1 << ". " << players[index]->description() << std::endl;
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
                std::cout << "\t" << index+1 << ". " << players[index]->description() << std::endl;
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
    } else if (selectedPlayStyleIndex == letBotsPlayIndex) {
        for (auto i = 0; i < bots.size(); i++) {
            for (auto j = 0; j < bots.size(); j++) {
                auto whitePlayer = bots[i];
                auto blackPlayer = bots[j];
                TicTacToe::TestResult testResult = TicTacToe::runMany(*whitePlayer, *blackPlayer, 10);
                std::cout << "\t" << (whitePlayer->description()) << " VS " << (blackPlayer->description()) << ": ";
                std::cout << testResult.wins/(double)testResult.numberOfGames()*100 << " wins, " << testResult.draws/(double)testResult.numberOfGames()*100 << " draws, " << testResult.losses/(double)testResult.numberOfGames()*100 << " losses" << std::endl;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    const int candyCrushIndex = 1;
    const int ticTacToeIndex = 2;
    
    while (true) {
        int selectedGameIndex = -1;
        while (selectedGameIndex != candyCrushIndex && selectedGameIndex != ticTacToeIndex) {
            std::cout << "Select game: " << std::endl;
            std::cout << "\t" << candyCrushIndex << ". Candy Crush" << std::endl;
            std::cout << "\t" << ticTacToeIndex << ". Tic Tac Toe" << std::endl;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cin >> selectedGameIndex;
        }
        
        if (selectedGameIndex == candyCrushIndex) {
            runCandyCrush();
        } else if (selectedGameIndex == ticTacToeIndex) {
            runTicTacToe();
        }
        std::cout << std::endl;
    }
    
    
    
    return 0;
}


