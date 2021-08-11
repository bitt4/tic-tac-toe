#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cstdlib>
#include <vector>

enum class Cell : uint8_t {    // Owners of a cell
    no_player,       // Marks an empty cell on board
    player_x,
    player_o
};

class Tictactoe{
private:
    SDL_Renderer *m_renderer;
    const int m_board_width, m_board_height; // TODO: WTF UNUSED
    const int m_size;
    const int m_cell_width;
    const int m_win_condition;
    bool m_running_state = true;
    bool m_game_ended = false;
    /**
     * Default colors of cross, circle and draw state
     */
    const SDL_Color m_cross_color  { 0  , 0  , 255, 255 };
    const SDL_Color m_circle_color { 255, 0  , 0  , 255 };
    const SDL_Color m_draw_color   { 24 , 24 , 24 , 255 }; // draw like tie

    Cell m_current_player = Cell::player_x;
    std::vector<Cell> m_board;

    void draw_cross(const int x, const int y, const SDL_Color &color) const;
    void draw_circle(const int x, const int y, const SDL_Color &color) const;
    void draw_cross(const int x, const int y) const;
    void draw_circle(const int x, const int y) const;

    void switch_player();

    bool check_row(const int y, const Cell player) const;
    bool check_column(const int x, const Cell player) const;
    bool check_diagonals_asc(const Cell player) const;
    bool check_diagonals_dsc(const Cell player) const;
    bool check_diagonals(const Cell player) const;

    bool check_player_won(const Cell player) const;
    bool check_draw() const;

    void restart();
    void render_win_state(const Cell player) const;
public:
    explicit Tictactoe(SDL_Renderer* renderer, const int width, const int height, const int size, const int win_condition);

    void render_init() const;

    void click_on_cell(const int x, const int y);

    int get_size() const;
    int get_cell_width() const;
    bool get_running_state() const;

    void quit();
};

#endif // TICTACTOE_HPP
