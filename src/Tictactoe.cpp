#include "../include/Tictactoe.hpp"

Tictactoe::Tictactoe(SDL_Renderer *renderer, const int w, const int h, const int s, const int win)
    :m_renderer { renderer },
     m_board_width { w },
     m_board_height { h },
     m_size { s },
     m_cell_width { w / s },
     m_win_condition { win },
     m_board { std::vector<Cell>(m_size * m_size, Cell::no_player) }
{
}

int Tictactoe::get_size() const {
    return m_size;
}

int Tictactoe::get_cell_width() const {
    return m_cell_width;
}

bool Tictactoe::get_running_state() const {
    return m_running_state;
}

void Tictactoe::quit(){
    m_running_state = false;
}

void Tictactoe::render_init() const {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
    SDL_RenderClear(m_renderer);

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

    // Draw lines between cells
    for(int i = 1; i < m_size; ++i){
        SDL_RenderDrawLine(m_renderer,
                           m_cell_width * i + i,
                           0,
                           m_cell_width * i + i,
                           m_cell_width * m_size + m_size);

        SDL_RenderDrawLine(m_renderer,
                           0,
                           m_cell_width * i + i,
                           m_cell_width * m_size + m_size,
                           m_cell_width * i + i);

        // The "+ i" in "m_cell_width * i + i", etc., is used to ensure
        // that each cell is the same size, besause each line takes 1 pixel
        // also used in Tictactoe::click_on_cell
    }
}

void Tictactoe::switch_player(){
    m_current_player = (m_current_player == Cell::player_x
                                          ? Cell::player_o
                                          : Cell::player_x);
}

void Tictactoe::restart(){
    render_init();

    std::fill(m_board.begin(), m_board.end(), Cell::no_player);

    m_game_ended = false;
    m_current_player = Cell::player_x;
    SDL_RenderPresent(m_renderer);
}

bool Tictactoe::check_row(const int row, const Cell player) const {
    int row_count = 0;
    for(int i = 0; i < m_size; ++i){
        if(m_board[row * m_size + i] == player){
            row_count++;
        } else {
            row_count = 0;
        }
        if(row_count == m_win_condition){
            return true;
        }
    }
    return false;
}

bool Tictactoe::check_column(const int column, const Cell player) const {
    int column_count = 0;
    for(int i = 0; i < m_size; ++i){
        if(m_board[i * m_size + column] == player){
            column_count++;
        } else {
            column_count = 0;
        }
        if(column_count == m_win_condition){
            return true;
        }
    }
    return false;
}

bool Tictactoe::check_diagonals_dsc(const Cell player) const {

    auto check_down = [&](int n){
        int count = 0;
        for(int i = 0; i < m_size - n; ++i){
            if(m_board[ (i + n) * m_size + i ] == player){
                count++;
            } else {
                count = 0;
            }
            if(count == m_win_condition){
                return true;
            }
        }
        return false;
    };


    for(int i = 0; i < m_size - m_win_condition + 1; ++i){
        if(check_down(i)){
            return true;
        }
    }

    auto check_right = [&](int n){
        int count = 0;
        for(int i = 0; i < m_size - n; ++i){
            if(m_board[ i * m_size + i + n ] == player){
                count++;
            } else {
                count = 0;
            }
            if(count == m_win_condition){
                return true;
            }
        }
        return false;
    };

    for(int i = 1; i < m_size - m_win_condition + 1; ++i){
        if(check_right(i)){
            return true;
        }
    }
    return false;
}

bool Tictactoe::check_diagonals_asc(const Cell player) const {

    auto check_up = [&](int n){
        int count = 0;
        for(int i = 0; i < m_size - n; ++i){
            if(m_board[ (m_size - n - i - 1) * m_size + i ] == player){
                count++;
            } else {
                count = 0;
            }
            if(count == m_win_condition){
                return true;
            }
        }
        return false;
    };

    for(int i = 1; i < m_size - m_win_condition + 1; ++i){
        if(check_up(i)){
            return true;
        }
    }

    auto check_right = [&](int n){
        int count = 0;
        for(int i = 0; i < m_size - n; ++i){
            if(m_board[ (m_size - i - 1) * m_size + i + n ] == player){
                count++;
            } else {
                count = 0;
            }
            if(count == m_win_condition){
                return true;
            }
        }
        return false;
    };

    for(int i = 0; i < m_size - m_win_condition + 1; ++i){
        if(check_right(i)){
            return true;
        }
    }

    return false;
}

bool Tictactoe::check_diagonals(const Cell player) const {
    return ( check_diagonals_dsc(player) || check_diagonals_asc(player) );
}

bool Tictactoe::check_player_won(const Cell player) const {
    for(int i = 0; i < m_size; ++i){
        if(check_row(i, player) || check_column(i, player)){
            return true;
        }
    }

    return check_diagonals(player);
}

bool Tictactoe::check_draw() const {
    int empty_cells = 0;
    for(const auto& cell : m_board){
        if(cell == Cell::no_player){
            empty_cells++;
        }
    }
    return empty_cells == 0;
}

void Tictactoe::click_on_cell(const int x, const int y){
    const int current_position = y * m_size + x;
    if(m_game_ended){
        restart();
    } else if(m_board[current_position] == Cell::no_player){
        if(m_current_player == Cell::player_x){
            draw_cross(x, y);
        } else {
            draw_circle(x, y);
        }
        m_board[current_position] = m_current_player;

        // Check if current player won
        if(check_player_won(m_current_player)) {
            render_win_state(m_current_player);
            m_game_ended = true;
        } else if(check_draw()){
            render_win_state(Cell::no_player);
            m_game_ended = true;
        }

        switch_player();
        SDL_RenderPresent(m_renderer);
    }
}

void Tictactoe::render_win_state(const Cell player) const {

    SDL_Color win_color = [&](){
        if(player == Cell::player_x){
            return m_cross_color;
        } else if(player == Cell::player_o){
            return m_circle_color;
        } else {
            return m_draw_color;
        }
    }();

    for(int y = 0; y < m_size; ++y){
        for(int x = 0; x < m_size; ++x){
            const int current_position = y * m_size + x;
            if(m_board[current_position] == Cell::player_x){
                draw_cross(x, y, win_color);
            } else if(m_board[current_position] == Cell::player_o){
                draw_circle(x, y, win_color);
            }
        }
    }
}

void Tictactoe::draw_cross(const int x, const int y, const SDL_Color &color) const {
    thickLineRGBA(m_renderer,
                  (x + 0.2) * m_cell_width + x,    // simplified '(x * m_cell_width + m_cell_width * 0.5 + x) - m_cell_width * 0.3'
                  (y + 0.8) * m_cell_width + y,
                  (x + 0.8) * m_cell_width + x,
                  (y + 0.2) * m_cell_width + y,
                  30 / m_size,
                  color.r,
                  color.g,
                  color.b,
                  255);

    thickLineRGBA(m_renderer,
                  (x + 0.2) * m_cell_width + x,
                  (y + 0.2) * m_cell_width + y,
                  (x + 0.8) * m_cell_width + x,
                  (y + 0.8) * m_cell_width + y,
                  30 / m_size,
                  color.r,
                  color.g,
                  color.b,
                  255);
}

void Tictactoe::draw_circle(const int x, const int y, const SDL_Color &color) const {
    filledCircleRGBA(m_renderer,
                     (x + 0.5) * m_cell_width + x,
                     (y + 0.5) * m_cell_width + y,
                     m_cell_width * 0.4,
                     color.r,
                     color.g,
                     color.b,
                     255);

    filledCircleRGBA(m_renderer,
                     (x + 0.5) * m_cell_width + x,
                     (y + 0.5) * m_cell_width + y,
                     m_cell_width * 0.35,
                     0,
                     0,
                     0,
                     255);
}

void Tictactoe::draw_cross(const int x, const int y) const {
    draw_cross(x, y, m_cross_color);
}

void Tictactoe::draw_circle(const int x, const int y) const {
    draw_circle(x, y, m_circle_color);
}
