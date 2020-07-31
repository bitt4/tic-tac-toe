#include "Tictactoe.hpp"

Tictactoe::Tictactoe(SDL_Renderer *renderer, int w, int h)
    :size(3),
     crossColor({.r = 0, .g = 0, .b = 255}),
     circleColor({.r = 255, .g = 0, .b = 0}),
     currentPlayer(Cell::player_x),
     runningState(true)
{
    this->renderer = renderer;
    this->boardWidth = w;
    this->boardHeight = h;
    this->cell_width = this->boardWidth / this->size;
    this->board = (Cell*) calloc( this->size * this->size, sizeof(Cell) );

    // TODO: Resize window based on size of cell and
    //       number of cells instead of changing size
    //       of cell, ( main.cpp )
}

int Tictactoe::getSize(){
    return this->size;
}

int Tictactoe::get_cell_width(){
    return this->cell_width;
}

bool Tictactoe::getRunningState(){
    return this->runningState;
}

void Tictactoe::end(){
    this->runningState = false;
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

        // The "+ i" in "this->cell_width * i + i", etc., is used to ensure
        // that each cell is the same size, besause each line takes 1 pixel
        // also used in Tictactoe::click_on_cell
    }

    SDL_RenderPresent(renderer);
}

void Tictactoe::switchPlayer(){

    this->currentPlayer = (this->currentPlayer == Cell::player_x
                           ? Cell::player_o
                           : Cell::player_x);

    // The code block above is equivalent to the code block below

    // if(this->currentPlayer == Cell::player_x){
    //     this->currentPlayer = Cell::player_o;
    // }
    // else {
    //     this->currentPlayer = Cell::player_x;
    // }
}

bool Tictactoe::checkRow(int row, Cell player){
    int rowCount = 0;
    for(int i = 0; i < this->size; i++){
        if(this->board[row * this->size + i] == player){
            rowCount++;
        }
    }
    return rowCount == this->size;
}

bool Tictactoe::checkColumn(int column, Cell player){
    int columnCount = 0;
    for(int i = 0; i < this->size; i++){
        if(this->board[i * this->size + column] == player){
            columnCount++;
        }
    }
    return columnCount == this->size;
}

void Tictactoe::click_on_cell(int x, int y){

    if(this->board[y * size + x] == Cell::no_player){
        if(this->currentPlayer == Cell::player_x){
            drawCross(x * cell_width + cell_width * 0.5 + x,
                      y * cell_width + cell_width * 0.5 + y);
            this->board[y * size + x] = Cell::player_x;
        }
        else {
            drawCircle(x * cell_width + cell_width * 0.5 + x,
                       y * cell_width + cell_width * 0.5 + y);
            this->board[y * size + x] = Cell::player_o;
        }
        switchPlayer();
        SDL_RenderPresent(renderer);
    }
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
