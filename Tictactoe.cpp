#include "Tictactoe.hpp"

Tictactoe::Tictactoe(SDL_Renderer *renderer){
        this->renderer = renderer;
}

void Tictactoe::renderInit(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, 201, 0, 201, 602);
    SDL_RenderDrawLine(renderer, 402, 0, 402, 602);
    SDL_RenderDrawLine(renderer, 0, 201, 602, 201);
    SDL_RenderDrawLine(renderer, 0, 402, 602, 402);

    SDL_RenderPresent(renderer);
}
