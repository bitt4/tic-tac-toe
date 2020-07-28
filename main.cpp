#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>

#include "Tictactoe.hpp"

int main(int argc, char *argv[]){

    // Initialize SDL

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cerr << "SDL video initialization failure: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }

    // Create window

    SDL_Window *window = SDL_CreateWindow("Tic-Tac-Toe",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          602, 602,
                                          SDL_WINDOW_SHOWN
                                         );

    if(window == NULL){
        std::cerr << "Window creation failed: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }

    // Create renderer

    SDL_Renderer *renderer = SDL_CreateRenderer(window,
                                                -1,
                                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(renderer == NULL){
        SDL_DestroyWindow(window);
        std::cerr << "Renderer creation failed: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }

    Tictactoe tictactoe(renderer, 600, 600);

    SDL_SetWindowSize(window,
                      tictactoe.getSize() * tictactoe.get_cell_width() + tictactoe.getSize(),
                      tictactoe.getSize() * tictactoe.get_cell_width() + tictactoe.getSize());

    tictactoe.renderInit();

    SDL_Event e;

    bool quit = false;
    while(!quit){
        while(SDL_PollEvent(&e)){
            switch(e.type){
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
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
