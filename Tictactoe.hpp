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

    /**
     * checks line specified by 1st argument in            |X|X|X|
     * array `Cell *board`,                                | | | |
     * returns true, if it's filled by cells               | | | |
     * specified by second argument,
     * otherwise returns false
     */
    bool checkRow(int, Cell);

    /**
     * checks column specified by 1st argument in          |X| | |
     * array `Cell *board`,                                |X| | |
     * returns true, if it's filled by cells               |X| | |
     * specified by second argument,
     * otherwise returns false
     */
    bool checkColumn(int, Cell);

    /**
     * checks both diagonals of array `Cell *board`,       |X| | |
     * returns true if any of them is filled by cells      | |X| |
     * of type specified by argument,                      | | |X|
     * otherwise returns false
     */
    bool checkDiagonals(Cell);

    /**
     * first, it checks all rows and columns,
     * then diagonals of array `Cell *board`,
     * if any of them is filled by cells of same type
     * as argument, returns true,
     * otherwise returns false,
     * uses functions checkColumn(), checkRow() and
     * checkDiagonals()
     */
    bool checkPlayerWon(Cell);

    /**
     * returns true if all cells are filled
     * but neither player won,
     * otherwise returns false
     */
    bool checkDraw();

    /**
     * restarts game: renders empty board,
     * resets all cells to Cell::no_player,
     * sets gameEnded to false,
     * sets currentPlayer to Cell::player_x
     */
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
