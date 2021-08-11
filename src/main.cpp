#include <cstdlib>
#include <SDL2/SDL.h>
#include <getopt.h>

#include "../include/Tictactoe.hpp"

void display_help();
void display_length_error();
int parse_option(const char* value, int l, int r);

int main(int argc, char *argv[]){

    int board_size = 3;
    int win = 3;

    static struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"size", required_argument, NULL, 's'},
        {"win", required_argument, NULL, 'w'},
        {NULL, 0, NULL, 0}
    };

    int c;

    while((c = getopt_long(argc, argv, "hs:w:", long_options, NULL)) != -1){
        switch(c){
        case 's':
            board_size = parse_option(optarg, 3, 10);
            if(board_size == -1){
                board_size = 3;
                display_length_error();
            }
            break;
        case 'w':
            win = parse_option(optarg, 3, 100);
            if(win == -1){
                win = 3;
                fprintf(stderr, "Invalid win condition, setting to 3...\n");
            }
            break;
        case 'h':
            display_help();
            return EXIT_SUCCESS;
        case '?':
            display_help();
            return EXIT_FAILURE;
        default: {}
        }
    }

    if(win > board_size){
        fprintf(stderr, "Win condition cannot be bigger than board size.\n");
        return EXIT_FAILURE;
    }

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "SDL video initialization failure: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Create window
    SDL_Window *window = SDL_CreateWindow("Tic-Tac-Toe",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          600 + board_size - 1,
                                          600 + board_size - 1,
                                          SDL_WINDOW_SHOWN
                                         );

    if(window == nullptr){
        fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Set icon */
    SDL_Surface *icon = SDL_LoadBMP("icon.bmp");
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);

    // Create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window,
                                                -1,
                                                SDL_RENDERER_SOFTWARE); // SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC

    if(renderer == nullptr){
        SDL_DestroyWindow(window);
        fprintf(stderr, "Renderer creation failed: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    Tictactoe tictactoe(renderer, 600, 600, board_size, win);

    tictactoe.render_init();
    SDL_RenderPresent(renderer);

    SDL_Event e;

    while(tictactoe.get_running_state()){
        if(SDL_WaitEvent(&e)){
            switch(e.type){
            case SDL_QUIT:
                tictactoe.quit();
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(e.button.button == SDL_BUTTON_LEFT){
                    tictactoe.click_on_cell(e.button.x / tictactoe.get_cell_width(), e.button.y / tictactoe.get_cell_width());
                }
                break;
            default: {}
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void display_help(){
    fprintf(stdout, "Usage: ./tictactoe ...[OPTIONS]\n"
                    "Tic-Tac-Toe clone for 2 players.\n"
                    "\n"
                    "  -h,          --help           display this message\n"
                    "  -s NUM, --size NUM  set size of board (how many cells are in one row)\n"
                    "  -w NUM, --win  NUM  set win condition (how many filled cells does it take to win)\n");
}

void display_length_error(){
    fprintf(stderr, "Invalid size, must be between 3 and 10, setting to 3...\n");
}

int parse_option(const char* value, int l, int r){
    char* end;
    long int output = strtol(value, &end, 10);

    if(value == end){
        fprintf(stderr, "Invalid value '%s'\n", value);
        exit(1);
    }

    if(l <= output && output <= r){
        return output;
    } else {
        return -1;
    }
}
