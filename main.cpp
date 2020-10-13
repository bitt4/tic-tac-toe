#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <string.h>

#include "Tictactoe.hpp"

void displayHelp();
void displayLengthError();

int main(int argc, char *argv[]){

    int boardSize = 3;
    int win = 3;

    // Parse arguments

    if(argc > 1){
        for(int i = 1; i < argc; i++){
            if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0){
                displayHelp();
                return EXIT_SUCCESS;
            }

            if(strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--size") == 0){
                if(i + 1 <= argc - 1){
                    if(strlen(argv[i+1]) > 2){ /* Prevent overflow */
                        displayLengthError();
                        boardSize = 3;
                    }
                    else {
                        boardSize = atoi(argv[i+1]);
                        if(boardSize < 3 || boardSize > 10){
                            boardSize = 3;
                            displayLengthError();
                        }
                    }
                }
                else{
                    displayHelp();
                    return EXIT_FAILURE;
                }
            }

            if(strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--win") == 0){
                if(i + 1 <= argc - 1){
                    if(strlen(argv[i+1]) > 2){ /* Prevent overflow */
                        std::cerr << "Invalid win condition, setting to 3...\n";
                        win = 3;
                    }
                    else {
                        win = atoi(argv[i+1]);
                        if(win < 3){
                            win = 3;
                            std::cerr << "Win condition is too small, must be at least 3, setting to 3...\n";
                        }
                    }
                }
                else{
                    displayHelp();
                    return EXIT_FAILURE;
                }
            }
        }
    }

    if(win > boardSize){
        std::cerr << "Win condition cannot be bigger than board size.\n";
        return EXIT_FAILURE;
    }

    // Initialize SDL

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cerr << "SDL video initialization failure: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }

    // Create window

    SDL_Window *window = SDL_CreateWindow("Tic-Tac-Toe",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          600 + boardSize - 1,
                                          600 + boardSize - 1,
                                          SDL_WINDOW_SHOWN
                                         );

    if(window == NULL){
        std::cerr << "Window creation failed: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }

    /* Set icon */
    SDL_Surface *icon = SDL_LoadBMP("icon.bmp");
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);

    // Create renderer

    SDL_Renderer *renderer = SDL_CreateRenderer(window,
                                                -1,
                                                SDL_RENDERER_SOFTWARE); // SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC

    if(renderer == NULL){
        SDL_DestroyWindow(window);
        std::cerr << "Renderer creation failed: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }

    Tictactoe tictactoe(renderer, 600, 600, boardSize, win);

    tictactoe.renderInit();
    SDL_RenderPresent(renderer);

    SDL_Event e;

    while(tictactoe.getRunningState()){
        if(SDL_WaitEvent(&e)){
            switch(e.type){
            case SDL_QUIT:
                tictactoe.quit();
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(e.button.button == SDL_BUTTON_LEFT)
                    tictactoe.clickOnCell(e.button.x / tictactoe.getCellWidth(), e.button.y / tictactoe.getCellWidth());
                break;
            default: {}
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void displayHelp(){
    std::cout << "Usage: ./tictactoe [OPTION]\n";
    std::cout << "Tic-Tac-Toe clone for 2 players.\n\n";
    std::cout << "  -h,          --help           display this message\n";
    std::cout << "  -s <number>, --size <number>  set size of board (how many cells are in one row)\n";
    std::cout << "  -w <number>, --win  <number>  set win condition (how many filled cells does it take to win)\n";
}

void displayLengthError(){
    std::cout << "Invalid size, must be between 3 and 10, setting to 3...\n";
}
