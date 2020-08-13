#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <string.h>

#include "Tictactoe.hpp"

void displayHelp();
void displayLengthError();

int main(int argc, char *argv[]){

    int boardSize = 3;

    // Parse arguments

    if(argc > 1){
        for(int i = 1; i < argc; i++){
            if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0){
                displayHelp();
            }

            if(strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--size") == 0){
                if(i + 1 <= argc - 1){
                    boardSize = atoi(argv[i+1]);
                    if(boardSize < 3 || boardSize > 10)
                        boardSize = 3;
                    else {
                        displayLengthError();
                    }

                    // TODO: Check errors when parsing arguments

                }
                else{
                    displayHelp();
                    return EXIT_FAILURE;
                }
            }
        }
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

    // Create renderer

    SDL_Renderer *renderer = SDL_CreateRenderer(window,
                                                -1,
                                                SDL_RENDERER_SOFTWARE); // SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC

    if(renderer == NULL){
        SDL_DestroyWindow(window);
        std::cerr << "Renderer creation failed: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }

    Tictactoe tictactoe(renderer, 600, 600, boardSize);

    tictactoe.renderInit();
    SDL_RenderPresent(renderer);

    SDL_Event e;

    while(tictactoe.getRunningState()){
        while(SDL_PollEvent(&e)){
            switch(e.type){
            case SDL_QUIT:
                tictactoe.quit();
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(e.button.button == SDL_BUTTON_LEFT)
                    tictactoe.click_on_cell(e.button.x / tictactoe.get_cell_width(), e.button.y / tictactoe.get_cell_width());
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
    // Not implemented
    std::cout << "Sample help\n";
}

void displayLengthError(){
    std::cout << "Size must be between 3 and 10.\n";
}
