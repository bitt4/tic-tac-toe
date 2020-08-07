#include "Tictactoe.hpp"

Tictactoe::Tictactoe(SDL_Renderer *renderer, int w, int h)
    :size(3),
     crossColor({.r = 0, .g = 0, .b = 255}),
     circleColor({.r = 255, .g = 0, .b = 0}),
     drawColor({.r = 24, .g = 24, .b = 24}),
     currentPlayer(Cell::player_x),
     runningState(true),
     gameEnded(false)
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

void Tictactoe::quit(){
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

void Tictactoe::restart(){
    renderInit();
    for(int i = 0; i < this->size * this->size; i++){
        this->board[i] = Cell::no_player;
    }
    this->gameEnded = false;
    this->currentPlayer = Cell::player_x;
    SDL_RenderPresent(renderer);
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

bool Tictactoe::checkDiagonals(Cell player){
    int diagonalCount = 0;

    // First diagonal
    for(int i = 0; i < this->size; i++){
        if(this->board[ i * this->size + i ] == player){
            diagonalCount++;
        }
    }

    if(diagonalCount == this->size)
        return true;

    diagonalCount = 0;

    // Second diagonal
    for(int i = 0; i < this->size; i++){
        if(this->board[ (this->size - i - 1) * this->size + i ] == player){
            diagonalCount++;
        }
    }

    return diagonalCount == this->size;
}

bool Tictactoe::checkPlayerWon(Cell player){
    for(int i = 0; i < this->size; i++){
        if(checkRow(i, player) || checkColumn(i, player))
            return true;
    }

    return checkDiagonals(player);
}

bool Tictactoe::checkDraw(){
    int emptyCells = 0;
    for(int i = 0; i < this->size * this->size; i++){
        if(this->board[i] == Cell::no_player)
            emptyCells++;
    }
    return emptyCells == 0;
}

void Tictactoe::click_on_cell(int x, int y){

    if(gameEnded){
        restart();
    }

    else if(this->board[y * size + x] == Cell::no_player){
        if(this->currentPlayer == Cell::player_x){
            drawCross(x, y);
            this->board[y * size + x] = Cell::player_x;
        }
        else {
            drawCircle(x, y);
            this->board[y * size + x] = Cell::player_o;
        }

        // Check if current player won

        if(checkPlayerWon(this->currentPlayer)) {
            renderWinState(this->currentPlayer);
            this->gameEnded = true;
        }

        else if(checkDraw()){
            renderWinState(Cell::no_player);
            this->gameEnded = true;
        }

        switchPlayer();
        SDL_RenderPresent(renderer);
    }
}

// TODO: void renderWinState(Cell player) function

void Tictactoe::renderWinState(Cell player){
    renderInit();

    SDL_Color winColor = (player == Cell::player_x ? this->crossColor : (
                             player == Cell::player_o ? this->circleColor :
                                 this->drawColor
                             )
                         );

    for(int y = 0; y < this->size; y++){
        for(int x = 0; x < this->size; x++){
            if(this->board[y * this->size + x] == Cell::player_x){
                drawCross(x, y,
                          winColor);
            }
            else if(this->board[y * this->size + x] == Cell::player_o){
                drawCircle(x, y,
                           winColor);
            }
        }
    }
}

void Tictactoe::drawCross(int x, int y, SDL_Color color){
    thickLineRGBA(renderer,
                  (x * cell_width + cell_width * 0.5 + x) - cell_width * 0.3,
                  (y * cell_width + cell_width * 0.5 + y) + cell_width * 0.3,
                  (x * cell_width + cell_width * 0.5 + x) + cell_width * 0.3,
                  (y * cell_width + cell_width * 0.5 + y) - cell_width * 0.3,
                  10,
                  color.r,
                  color.g,
                  color.b,
                  255);

    thickLineRGBA(renderer,
                  (x * cell_width + cell_width * 0.5 + x) - cell_width * 0.3,
                  (y * cell_width + cell_width * 0.5 + y) - cell_width * 0.3,
                  (x * cell_width + cell_width * 0.5 + x) + cell_width * 0.3,
                  (y * cell_width + cell_width * 0.5 + y) + cell_width * 0.3,
                  10,
                  color.r,
                  color.g,
                  color.b,
                  255);
}

void Tictactoe::drawCircle(int x, int y, SDL_Color color){
    filledCircleRGBA(renderer,
                     x * cell_width + cell_width * 0.5 + x,
                     y * cell_width + cell_width * 0.5 + y,
                     cell_width * 0.4,
                     color.r,
                     color.g,
                     color.b,
                     255);

    filledCircleRGBA(renderer,
                     x * cell_width + cell_width * 0.5 + x,
                     y * cell_width + cell_width * 0.5 + y,
                     cell_width * 0.35,
                     0,
                     0,
                     0,
                     255);
}

void Tictactoe::drawCross(int x, int y){
    drawCross(x, y, this->crossColor);
}

void Tictactoe::drawCircle(int x, int y){
    drawCircle(x, y, this->circleColor);
}
