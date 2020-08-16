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

    /**
     * Default colors of cross, circle and draw state
     */
    SDL_Color crossColor, circleColor, drawColor;

    /**
     * Saves current player (player on move)
     */
    Cell currentPlayer;

    Cell *board;
    bool runningState, gameEnded;

    /**
     * Draws cross at given cell coordinates
     * filled by given color.
     */
    void drawCross(int, int, SDL_Color);

    /**
     * Draws circle at given cell coordinates
     * filled by given color.
     */
    void drawCircle(int, int, SDL_Color);

    /**
     * Draws cross at given cell coordinates
     * filled by color saved in 'SDL_Color crossColor'.
     */
    void drawCross(int, int);

    /**
     * Draws circle at given cell coordinates
     * filled by color saved in 'SDL_Color circleColor'.
     */
    void drawCircle(int, int);

    /**
     * switches current player saved
     * in 'Cell currentPlayer'
     */
    void switchPlayer();

    bool checkRow(int, Cell);
    bool checkColumn(int, Cell);
    bool checkDiagonals(Cell);
    bool checkPlayerWon(Cell);
    bool checkDraw();
    void restart();
    void renderWinState(Cell);
public:
    Tictactoe(SDL_Renderer*, int, int, int);
    void renderInit();
    void click_on_cell(int, int);
    int getSize();
    int get_cell_width();
    bool getRunningState();
    void quit();
};
