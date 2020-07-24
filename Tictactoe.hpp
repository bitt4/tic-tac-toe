#include <SDL2/SDL.h>

class Tictactoe{
private:
    SDL_Renderer *renderer;
public:
    Tictactoe(SDL_Renderer*);
    void renderInit();
};
