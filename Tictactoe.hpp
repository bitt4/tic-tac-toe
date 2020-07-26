#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

class Tictactoe{
private:
    SDL_Renderer *renderer;
    int boardWidth, boardHeight;
    int size;
    int cell_width;
    SDL_Color crossColor, circleColor;

    void drawCross(int, int);
    void drawCircle(int, int);
public:
    Tictactoe(SDL_Renderer*, int, int);
    void renderInit();
    void click_on_cell(int, int);
    int getSize();
    int get_cell_width();
};
