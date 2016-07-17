
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "CandyCrush.hpp"
#include "CandyCrushPlayer.hpp"
#include "TicTacToe.hpp"
#include "TicTacToePlayer.hpp"
#include <chrono>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>


//template <typename ValueType>
//ValueType selectValueFromArrayUsingStdin(std::string prompt,  std::vector<std::pair<std::string, ValueType>> values) {
//    int selectedValueIndex = -1;
//    while (true) {
//        std::cout << prompt << std::endl;
//        for (auto index = 0; index < values.size(); index++) {
//            std::cout << "\t" << index+1 << ". " << values[index].first << std::endl;
//        }
//        if (std::cin.fail()) {
//            std::cin.clear();
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//        }
//        std::cin >> selectedValueIndex;
//        selectedValueIndex--;
//        if (selectedValueIndex >= 0 && selectedValueIndex < values.size()) {
//            return values[selectedValueIndex].second;
//        } else {
//            std::cout << "Illegal input" << std::endl;
//        }
//    }
//}
//
//void selectAndRunFunctionUsingStdin(std::string prompt, std::vector<std::pair<std::string, void (*)()>> functions) {
//    selectValueFromArrayUsingStdin(prompt, functions)();
//}
//
//void testGameHashing() {
//    std::unordered_map<CandyCrush, int> counts;
//
//    auto start = std::chrono::high_resolution_clock::now();
//
//    for (auto i = 0; i < 2000; i++) {
//        CandyCrush game;
//        while (!game.gameOver()) {
//            counts[game]++;
//            auto legalMoves = game.legalMoves();
//            auto move = legalMoves[0];
//            game.play(move);
//        }
//    }
//
//    auto end = std::chrono::high_resolution_clock::now();
//
//    std::cout << "Execution time (us): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
//
//    std::cout << "Hashed games: " << counts.size() << std::endl;
//}
//
//void runCandyCrushYourself() {
//    auto humanPlayer = CandyCrushHumanPlayer();
//    CandyCrush::run(humanPlayer, true);
//}
//
//void runCandyCrushWithBots() {
//    auto randomBot = CandyCrushRandomBot();
//    auto greedyBot = CandyCrushGreedyBot();
//    auto monteCarloBot = CandyCrushMonteCarloBot();
//    std::vector<CandyCrushPlayer*> players = {&randomBot, &greedyBot, &monteCarloBot};
//
//    auto numberOfGames = 20;
//    std::cout << "Average score for " << numberOfGames << " games" << std::endl;
//    for (auto player: players) {
//        std::cout << "\t" << (player->description()) << ": " << CandyCrush::run(*player, numberOfGames) << " points" << std::endl;
//    }
//}
//
//void runCandyCrush() {
//    selectAndRunFunctionUsingStdin("How do you wanna play?", {
//        {"Play yourself",runCandyCrushYourself},
//        {"Let the bots play", runCandyCrushWithBots}
//    });
//}
//
//void runTicTacToeAndOverview() {
//    auto humanPlayer = TicTacToeHumanPlayer();
//    auto randomBot = TicTacToeRandomBot();
//    auto minimaxBot = MiniMaxBot();
//    auto monteCarlo = MonteCarloBot();
//    std::vector<std::pair<std::string, TicTacToePlayer*>>  players = {{"You", &humanPlayer}, {"Random", &randomBot}, {"Minimax", &minimaxBot}, {"Monte Carlo", &monteCarlo}};
//
//    auto whitePlayer = selectValueFromArrayUsingStdin("Select white player", players);
//    auto blackPlayer = selectValueFromArrayUsingStdin("Select black player", players);
//    TicTacToe::run(*whitePlayer, *blackPlayer);
//}
//
//void runTicTacToeWithBots() {
//    auto randomBot = TicTacToeRandomBot();
//    auto minimaxBot = MiniMaxBot();
//    auto monteCarlo = MonteCarloBot();
//    std::vector<TicTacToePlayer*>  bots = {&randomBot, &minimaxBot, &monteCarlo};
//    auto numberOfGames = 50;
//    std::cout << "Results for " << numberOfGames << " games" << std::endl;
//    for (auto i = 0; i < bots.size(); i++) {
//        for (auto j = 0; j < bots.size(); j++) {
//            auto whitePlayer = bots[i];
//            auto blackPlayer = bots[j];
//            TicTacToe::TestResult testResult = TicTacToe::runMany(*whitePlayer, *blackPlayer, numberOfGames);
//            std::cout << "\t" << (whitePlayer->description()) << " VS " << (blackPlayer->description()) << ": ";
//            std::cout << testResult.wins/(double)testResult.numberOfGames()*100 << "% wins, " << testResult.draws/(double)testResult.numberOfGames()*100 << "% draws, " << testResult.losses/(double)testResult.numberOfGames()*100 << "% losses" << std::endl;
//        }
//    }
//}
//
//void runTicTacToe() {
//    selectAndRunFunctionUsingStdin("How do you wanna play?", {
//        {"Overview a game between two opponents (maybe yourself)",runTicTacToeAndOverview},
//        {"Let all bots play against each other", runTicTacToeWithBots}
//    });
//}
//
//
////The window we'll be rendering to
//SDL_Window* gWindow = NULL;
//
////The surface contained by the window
//SDL_Surface* gScreenSurface = NULL;
//
////The image we will load and show on the screen
//SDL_Surface* gHelloWorld = NULL;
//
//bool loadMedia()
//{
//    //Loading success flag
//    bool success = true;
//
//    //Load splash image
//
//    const auto filePath = "assets/BackGround.jpg";
//
//    gHelloWorld = IMG_Load(filePath);
//
//    if( gHelloWorld == NULL )
//    {
//        printf( "Unable to load image %s! SDL Error: %s\n", filePath, SDL_GetError() );
//        success = false;
//    }
//
//    return success;
//}
//
//const int windowWidth = 640;
//const int windowHeight = 480;
//
//
//
//
//bool init()
//{
//    //Initialization flag
//    bool success = true;
//
//    //Initialize SDL
//    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
//    {
//        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
//        success = false;
//    }
//    else
//    {
//        //Create window
//        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN );
//        if( gWindow == NULL )
//        {
//            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
//            success = false;
//        }
//        else
//        {
//            //Get window surface
//            gScreenSurface = SDL_GetWindowSurface( gWindow );
//        }
//    }
//
//    return success;
//}
//
//void close()
//{
//    //Deallocate surface
//    SDL_FreeSurface( gHelloWorld );
//    gHelloWorld = NULL;
//
//    //Destroy window
//    SDL_DestroyWindow( gWindow );
//    gWindow = NULL;
//
//    //Quit SDL subsystems
//    SDL_Quit();
//}
//
//void runGui() {
//    //Start up SDL and create window
//    if( !init() )
//    {
//        printf( "Failed to initialize!\n" );
//    }
//    else
//    {
//        //Load media
//        if( !loadMedia() )
//        {
//            printf( "Failed to load media!\n" );
//        }
//        else
//        {
//            //Apply the image
//
//
//            auto rect = SDL_Rect{10, 10, 10, 10};
//            SDL_BlitSurface( gHelloWorld, &rect, gScreenSurface, &rect );
//            SDL_UpdateWindowSurface( gWindow );
//
//
//
//        }
//    }
//}
//
//int main(int argc, const char * argv[]) {
//
//
//    runGui();
//
//    int a;
//    std::cin >> a;
//    return 0;
//    SDL_assert_always(1==1);
//
//    while (true) {
//    selectAndRunFunctionUsingStdin("Select game", {
//        {"Candy Crush",runCandyCrush},
//        {"Tic Tac Toe", runTicTacToe}
//    });
//    }
//    return 0;
//}



//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>


//SDL_Surface* loadImage(const std::string imagePath)
//{
//    return IMG_Load( "assets/BackGround.jpg" );
//}




struct GameEngine {
    
    std::unordered_map<CandyCrush::Cell, SDL_Surface*> cellImages;
    SDL_Surface* backgroundImage = nullptr;
    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;
    
    
    CandyCrush game;
    const int numberOfRows = (int)game.getGameBoard().rows;
    const int numberOfColumns = (int)game.getGameBoard().columns;
    const SDL_Rect drawArea = SDL_Rect{340,110,320,320};
    const int cellHeight = drawArea.h / numberOfRows;
    
    TTF_Font* Sans;
    const int cellWidth = drawArea.w / numberOfColumns;
    
    
    int lastX = -1;
    int lastY = -1;
    
    //Screen dimension constants
    const int windowWidth = 755;
    const int windowHeight = 600;
    
    
    SDL_Surface* surfaceForText(std::string text) {
        //this opens a font style and sets a size
        SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text.c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
        if (surfaceMessage == nullptr) {
            std::cout << "SDL_Surface Error: " << SDL_GetError() << std::endl;
        }
        return surfaceMessage;
    }
    
    GameEngine() {
        
        if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
            printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
            throw;
        }
        
        if (TTF_Init() < 0) {
            printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
            throw;
        }
        
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
        if( window == nullptr) {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            throw;
        }
        Sans = TTF_OpenFont("/Library/Fonts/Arial.ttf", 54);
        screenSurface = SDL_GetWindowSurface( window );
        
        // Load assets
        cellImages = {
            {CandyCrush::Blue, IMG_Load("assets/Blue.png")},
            {CandyCrush::Green, IMG_Load("assets/Green.png")},
            {CandyCrush::Red, IMG_Load("assets/Red.png")},
            {CandyCrush::Purple, IMG_Load("assets/Purple.png")},
            {CandyCrush::Yellow, IMG_Load("assets/Yellow.png")},
        };
        backgroundImage = IMG_Load("assets/BackGround.jpg");
    }
    
    ~GameEngine() {
        for (auto cellImage: cellImages) {
            SDL_FreeSurface(cellImage.second);
        }
        SDL_FreeSurface(backgroundImage);
        if (timeLeftLabel != nullptr) {
            SDL_FreeSurface(timeLeftLabel);
        }
        if (scoreLabel != nullptr) {
            SDL_FreeSurface(scoreLabel);
        }
    }
    
    SDL_Surface* timeLeftLabel = nullptr;
    SDL_Surface* scoreLabel = nullptr;
    void render(SDL_Surface* screenSurface, const CandyCrush& game, SDL_Rect drawArea, size_t numberOfSecondsLeft) {
        //SDL_FillRect(screenSurface, NULL, 0x000000);
        SDL_BlitSurface(backgroundImage, NULL, screenSurface, NULL );
        
        for (auto row = 0; row < game.getGameBoard().rows; row++) {
            for (auto column = 0; column < game.getGameBoard().columns; column++) {
                auto cell = game.getGameBoard()[row][column];
                auto image = cellImages[cell];
                
                auto destination = SDL_Rect{cellWidth*column+cellWidth/2-image->w/2 + drawArea.x, cellHeight*row+cellHeight/2-image->h/2+drawArea.y, cellWidth, cellHeight};
                
                if (lastX != -1 && GameBoard::CellPosition(row, column) == cellPositionFromCoordinates(lastX, lastY)) {
                    auto destination = SDL_Rect{cellWidth*column + drawArea.x, cellHeight*row + drawArea.y, cellWidth, cellHeight};
                    SDL_FillRect(screenSurface, &destination, 0b111);
                }
                SDL_BlitSurface( image, NULL, screenSurface, &destination );
            }
        }
        if (scoreLabel != nullptr) {
            SDL_FreeSurface(scoreLabel);
        }
        scoreLabel = surfaceForText("Score: " + std::to_string(game.getScore()));
        auto scoreLabelRect = SDL_Rect{0,0,100,100};
        
        
        SDL_BlitSurface(scoreLabel, NULL, screenSurface, &scoreLabelRect);
        
        if (timeLeftLabel != nullptr) {
            SDL_FreeSurface(timeLeftLabel);
        }
        timeLeftLabel = surfaceForText(std::to_string(numberOfSecondsLeft));
        auto timeLeftLabelRect = SDL_Rect{80,430,100,100};
        SDL_BlitSurface(timeLeftLabel, NULL, screenSurface, &timeLeftLabelRect);
        SDL_UpdateWindowSurface(window);
    }
    
    SDL_Rect rectForCellPosition(GameBoard::CellPosition cellPosition) {
        
        auto image = cellImages[game.getGameBoard()[cellPosition]];
        return SDL_Rect{cellWidth*(int)cellPosition.column+cellWidth/2-image->w/2 + drawArea.x, cellHeight*(int)cellPosition.row+cellHeight/2-image->h/2+drawArea.y, cellWidth, cellHeight};
    }
    
    SDL_Rect rectForCellPosition(int row, int column, const SDL_Surface * image) {
        return SDL_Rect{cellWidth*column+cellWidth/2-image->w/2 + drawArea.x, cellHeight*row+cellHeight/2-image->h/2+drawArea.y, cellWidth, cellHeight};
    }
    
    void render2(const CandyCrush& game, size_t numberOfSecondsLeft, CandyCrushGameBoardChange gameBoardChange, double percentage, bool fakeReverse) {
        //SDL_FillRect(screenSurface, NULL, 0x000000);
        SDL_BlitSurface(backgroundImage, NULL, screenSurface, NULL );
        
        for (auto row = 0; row < game.getGameBoard().rows; row++) {
            for (auto column = 0; column < game.getGameBoard().columns; column++) {
                auto cell = game.getGameBoard()[row][column];
                
                auto from = GameBoard::CellPosition(row, column);
                auto to = gameBoardChange.cellPositions[from];
                auto image = cellImages[cell];
                auto fromDestination = rectForCellPosition(from);
                auto toDestination = rectForCellPosition(to);

                
                if (gameBoardChange.removedCells.find(from) != gameBoardChange.removedCells.end()) {
//                    SDL_FillRect(screenSurface, &fromDestination, 0b111);
                } else {
                    fromDestination.x += (toDestination.x-fromDestination.x)*percentage;
                    fromDestination.y += (toDestination.y-fromDestination.y)*percentage;
                    SDL_BlitSurface( image, NULL, screenSurface, &fromDestination );
                }
            }
        }
        
        for (auto newCell: gameBoardChange.newCells) {
            GameBoard::CellPosition cellPosition = std::get<0>(newCell);
            CandyCrush::Cell cell = std::get<1>(newCell);
            int numberOfRows = std::get<2>(newCell);
            auto image = cellImages[cell];
            
            
            auto fromDestination = rectForCellPosition((int)cellPosition.row-numberOfRows, (int)cellPosition.column, image);
            
            
            std::cout << "LOL? " << (int)cellPosition.row-numberOfRows << "," << (int)cellPosition.column << std::endl;
            
            auto toDestination = rectForCellPosition((int)cellPosition.row, (int)cellPosition.column, image);
            
            fromDestination.x += (toDestination.x-fromDestination.x)*percentage;
            fromDestination.y += (toDestination.y-fromDestination.y)*percentage;
            
//            if (fromDestination.y > drawArea.y) {
                SDL_BlitSurface( image, NULL, screenSurface, &fromDestination );
//            }
        }
        
        if (scoreLabel != nullptr) {
            SDL_FreeSurface(scoreLabel);
        }
        scoreLabel = surfaceForText("Score: " + std::to_string(game.getScore()));
        auto scoreLabelRect = SDL_Rect{0,0,100,100};
        
        
        SDL_BlitSurface(scoreLabel, NULL, screenSurface, &scoreLabelRect);
        
        if (timeLeftLabel != nullptr) {
            SDL_FreeSurface(timeLeftLabel);
        }
        timeLeftLabel = surfaceForText(std::to_string(numberOfSecondsLeft));
        auto timeLeftLabelRect = SDL_Rect{80,430,100,100};
        SDL_BlitSurface(timeLeftLabel, NULL, screenSurface, &timeLeftLabelRect);
        SDL_UpdateWindowSurface(window);
    }
    
    void updateBoard(CandyCrushGameBoardChange gameBoardChange) {
        auto animationTimeInMilliseconds = 1000;
        auto iterations = 100;
        for (auto i = 0; i < iterations; i++) {
            render2(gameBoardChange.game, 60, gameBoardChange, i/(double)(iterations-1), false);
            SDL_Delay(animationTimeInMilliseconds/iterations);
        }
        //SDL_Delay(3000);
    }
    
//    void animateMove(const CandyCrush& game, size_t numberOfSecondsLeft, GameBoard::CellSwapMove move, bool fakeReverse) {
//        auto animationTimeInMilliseconds = 150;
//        auto iterations = 100;
//        for (auto i = 0; i < iterations; i++) {
//            render2(game, numberOfSecondsLeft, move, i/(double)(iterations-1), fakeReverse);
//            SDL_Delay(animationTimeInMilliseconds/iterations);
//        }
//    }
    
    GameBoard::CellPosition cellPositionFromCoordinates(int x, int y) const {
        return GameBoard::CellPosition((y-drawArea.y)/cellHeight, (x-drawArea.x)/cellWidth);
    }
    
    void run() {
        bool quit = false;
        SDL_Event e;
        
        bool isMouseDown = false;
        
        auto start = std::chrono::high_resolution_clock::now();
        auto numberOfSeconds = 60;
        render(screenSurface, game, drawArea, numberOfSeconds);
        while( !quit ) {
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
            auto numberOfSecondsLeft = numberOfSeconds-duration;
            while( SDL_PollEvent( &e ) != 0 ) {
                
                if( e.type == SDL_QUIT ) {
                    quit = true;
                }
                
                if (e.type == SDL_MOUSEBUTTONDOWN){
                    isMouseDown = true;
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    
                    auto move = GameBoard::CellSwapMove(cellPositionFromCoordinates(x, y), cellPositionFromCoordinates(lastX, lastY));
                    std::cout << move << std::endl;
                    CandyCrush oldGame = game;
                    

                    auto adjacentCells = game.getGameBoard().adjacentCells(move.from);
                    if (lastX != -1 && std::find(adjacentCells.begin(), adjacentCells.end(), move.to) != adjacentCells.end()) {
//                        animateMove(oldGame, numberOfSecondsLeft, move, false);
//                        if (!oldGame.isLegalMove(move)) {
//                            animateMove(oldGame, numberOfSecondsLeft, move, true);
//                        }
                    }
                    
                    
//                    std::function<void(std::unordered_map<GameBoard::CellPosition, GameBoard::CellPosition> cellPositions, GameBoard::GameBoard<6, 6, CandyCrush::Cell>)> a = static_cast<void(std::unordered_map<GameBoard::CellPosition, GameBoard::CellPosition> cellPositions, GameBoard::GameBoard<6, 6, CandyCrush::Cell>)>(&GameBoard::updateBoard);
                    
                    
                    auto lamm = [&](CandyCrushGameBoardChange gameBoardChange) {
                        updateBoard(gameBoardChange);
                    };
                    
//                    std::function<void(std::unordered_map<GameBoard::CellPosition, GameBoard::CellPosition>, GameBoard::GameBoard<6, 6, CandyCrush::Cell>)> callback = &updateBoard;
                    
                    if (game.play(move, lamm) || game.getGameBoard().areCellsAdjacent(move.from, move.to)) {
                        std::cout << "Score: " << game.getScore() << std::endl;
                        lastX = -1;
                        lastY = -1;
                    } else {
                        std::cout << "Could not make the move" << std::endl;
                        lastX = x;
                        lastY = y;
                    }
                }
                
                if (e.type == SDL_MOUSEBUTTONUP && lastX != -1) {
                    isMouseDown = false;
                }
                
//                if (e.type == SDL_MOUSEMOTION && isMouseDown && lastX != -1) {
//                    int x, y;
//                    SDL_GetMouseState(&x, &y);
//                    auto move = GameBoard::CellSwapMove(cellPositionFromCoordinates(x, y), cellPositionFromCoordinates(lastX, lastY));
//                    if (!(move.to == move.from) && game.getGameBoard().isCellValid(cellPositionFromCoordinates(x, y)) && game.getGameBoard().isCellValid(cellPositionFromCoordinates(lastX, lastY))) {
//                            if (lastX != -1 && game.getGameBoard().areCellsAdjacent(move.from, move.to)) {
////                                animateMove(game, numberOfSecondsLeft, move, false);
////                                if (!game.isLegalMove(move)) {
////                                    animateMove(game, numberOfSecondsLeft, move, true);
////                                }
//                            }
//                        if (!game.play(move)) {
//                            lastX = -1;
//                            lastY = -1;
//                        }
//                    }
//                }
            }
            
            //std::cout << "Execution time (us): " << numberOfSecondsLeft << std::endl;
//            render(screenSurface, game, drawArea, numberOfSecondsLeft);
        }
    }
};


int main( int argc, char* args[] )
{
    GameEngine gameEngine;
    gameEngine.run();
    return 0;
}


