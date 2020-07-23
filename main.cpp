#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]){

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cerr << "SDL video initialization failure: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow("Tic-Tac-Toe",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          600, 600,
                                          SDL_WINDOW_SHOWN
                                         );

    if(window == NULL){
        std::cerr << "Window creation failed: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
