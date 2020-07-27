#include "Tictactoe.hpp"

Tictactoe::Tictactoe(SDL_Renderer *renderer, int w, int h)
    :size(3),
     crossColor({.r = 0, .g = 0, .b = 255}),
     circleColor({.r = 255, .g = 0, .b = 0})
{
        this->renderer = renderer;
        this->boardWidth = w;
        this->boardHeight = h;
        this->cell_width = this->boardWidth / this->size;
}

int Tictactoe::getSize(){
    return this->size;
}

int Tictactoe::get_cell_width(){
    return this->cell_width;
}

void Tictactoe::renderInit(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for(int i = 1; i < this->size; i++){
        SDL_RenderDrawLine(renderer,
                           this->cell_width * i + i,
                           0,
                           this->cell_width * i + i,
                           this->cell_width * this->size + this->size);

        SDL_RenderDrawLine(renderer,
                           0,
                           this->cell_width * i + i,
                           this->cell_width * this->size + this->size,
                           this->cell_width * i + i);
    }

    SDL_RenderPresent(renderer);
}

void Tictactoe::click_on_cell(int x, int y){
    drawCross(x * cell_width + cell_width * 0.5 + x,
              y * cell_width + cell_width * 0.5 + y);

    /*
    drawCircle(x * cell_width + cell_width * 0.5,
               y * cell_width + cell_width * 0.5);
    */

    SDL_RenderPresent(renderer);
}

void Tictactoe::drawCross(int x, int y){
    thickLineRGBA(renderer,
                  x - cell_width * 0.3,
                  y + cell_width * 0.3,
                  x + cell_width * 0.3,
                  y - cell_width * 0.3,
                  10,
                  0,
                  0,
                  255,
                  255);

    thickLineRGBA(renderer,
                  x - cell_width * 0.3,
                  y - cell_width * 0.3,
                  x + cell_width * 0.3,
                  y + cell_width * 0.3,
                  10,
                  crossColor.r,
                  crossColor.g,
                  crossColor.b,
                  255);
}

void Tictactoe::drawCircle(int x, int y){
    filledCircleRGBA(renderer,
                     x,
                     y,
                     cell_width * 0.4,
                     circleColor.r,
                     circleColor.g,
                     circleColor.b,
                     255);

    filledCircleRGBA(renderer,
                     x,
                     y,
                     cell_width * 0.35,
                     0,
                     0,
                     0,
                     255);
}
