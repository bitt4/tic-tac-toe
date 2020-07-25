#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

class Tictactoe{
private:
    SDL_Renderer *renderer;
    int boardWidth;
    int boardHeight;
    int cells;
    int cell_width;
    SDL_Color crossColor;

    void drawCross(int, int);
public:
    Tictactoe(SDL_Renderer*, int, int);
    void renderInit();
    void click_on_cell(int, int);
};
