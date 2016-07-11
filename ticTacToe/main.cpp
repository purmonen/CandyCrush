
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "CandyCrush.hpp"
#include "CandyCrushPlayer.hpp"
#include "TicTacToe.hpp"
#include "TicTacToePlayer.hpp"
#include <chrono>

template <typename ValueType>
ValueType selectValueFromArrayUsingStdin(std::string prompt,  std::vector<std::pair<std::string, ValueType>> values) {
    int selectedValueIndex = -1;
    while (true) {
        std::cout << prompt << std::endl;
        for (auto index = 0; index < values.size(); index++) {
            std::cout << "\t" << index+1 << ". " << values[index].first << std::endl;
        }
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin >> selectedValueIndex;
        selectedValueIndex--;
        if (selectedValueIndex >= 0 && selectedValueIndex < values.size()) {
            return values[selectedValueIndex].second;
        } else {
            std::cout << "Illegal input" << std::endl;
        }
    }
    
}

void selectAndRunFunctionUsingStdin(std::string prompt, std::vector<std::pair<std::string, void (*)()>> functions) {
    selectValueFromArrayUsingStdin(prompt, functions)();
}


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

void runCandyCrushYourself() {
    auto humanPlayer = CandyCrushHumanPlayer();
    CandyCrush::run(humanPlayer, true);
}

void runCandyCrushWithBots() {
    auto randomBot = CandyCrushRandomBot();
    auto greedyBot = CandyCrushGreedyBot();
    auto monteCarloBot = CandyCrushMonteCarloBot();
    std::vector<CandyCrushPlayer*> players = {&randomBot, &greedyBot, &monteCarloBot};
    for (auto player: players) {
        std::cout << "\t" << (player->description()) << ": " << CandyCrush::run(*player, 10) << " points" << std::endl;
    }
}

void runCandyCrush() {
    selectAndRunFunctionUsingStdin("How do you wanna play?", {
        {"Play yourself",runCandyCrushYourself},
        {"Let the bots play", runCandyCrushWithBots}
    });
}


void runTicTacToeAndOverview() {
    auto humanPlayer = TicTacToeHumanPlayer();
    auto randomBot = TicTacToeRandomBot();
    auto minimaxBot = MiniMaxBot();
    auto monteCarlo = MonteCarloBot();
    std::vector<std::pair<std::string, TicTacToePlayer*>>  players = {{"You", &humanPlayer}, {"Random", &randomBot}, {"Minimax", &minimaxBot}, {"Monte Carlo", &monteCarlo}};
    
    auto whitePlayer = selectValueFromArrayUsingStdin("Select white player", players);
    auto blackPlayer = selectValueFromArrayUsingStdin("Select black player", players);
        TicTacToe::run(*whitePlayer, *blackPlayer);
}

void runTicTacToeWithBots() {
    auto randomBot = TicTacToeRandomBot();
    auto minimaxBot = MiniMaxBot();
    auto monteCarlo = MonteCarloBot();
    std::vector<TicTacToePlayer*>  bots = {&randomBot, &minimaxBot, &monteCarlo};
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

void runTicTacToe() {
    selectAndRunFunctionUsingStdin("How do you wanna play?", {
        {"Overview a game between two opponents (maybe yourself)",runTicTacToeAndOverview},
        {"Let all bots play against each other", runTicTacToeWithBots}
    });
}

int main(int argc, const char * argv[]) {
    selectAndRunFunctionUsingStdin("Select game", {
        {"Candy Crush",runCandyCrush},
        {"Tic Tac Toe", runTicTacToe}
    });
    return 0;
}


