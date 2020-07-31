#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cstdlib>

enum class Cell {    // Owners of a cell
    no_player,       // Marks an empty cell on board
    player_x,
    player_o
};

class Tictactoe{
private:
    SDL_Renderer *renderer;
    int boardWidth, boardHeight;
    int size;
    int cell_width;
    SDL_Color crossColor, circleColor;
    Cell currentPlayer;
    Cell *board;
    bool runningState;

    void drawCross(int, int);
    void drawCircle(int, int);
    void switchPlayer();
    bool checkRow(int, Cell);
    bool checkColumn(int, Cell);
    bool checkDiagonals(Cell);
public:
    Tictactoe(SDL_Renderer*, int, int);
    void renderInit();
    void click_on_cell(int, int);
    int getSize();
    int get_cell_width();
    bool getRunningState();
    void end();
};
