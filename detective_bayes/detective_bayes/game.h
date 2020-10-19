//
//  game.h
//  astroid
//
//  Created by Ali Hamdani on 10/11/20.
//

#ifndef game_h
#define game_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include "rv.h"


typedef struct Controller{
    int edit;
    int mouse_x;
    int mouse_y;

}Controller;

typedef struct Game{
    int board[16][9];
    int screen_width;
    int screen_height;
    Controller control;
}Game;

Game game;


//need to handle input in an intuitive way
void inputs( bool* a, struct Controller* xbone){
    SDL_Event event;
    
    while (SDL_PollEvent(&event)){
        switch (event.type) {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_e:
                        xbone->edit = 1;
                        break;
                }
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {

                    case SDLK_e:
                        xbone->edit = 0;
                        break;

                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&xbone->mouse_x, &xbone->mouse_y);
                

                break;
            case SDL_MOUSEBUTTONUP:
                xbone->mouse_x = -1;
                xbone->mouse_y = -1;
                break;
            case SDL_QUIT:
                *a = true;
        }
    }
}

void boardInit(){
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 9; j++){
            game.board[i][j] = -1;
        }
    }
}
void gameInit(int width, int height){
    boardInit();
    game.screen_width = width;
    game.screen_height = height;
}

//TODO: Change 46 to a generalized tilesize variable
SDL_Point whichTile(int x, int y){
    SDL_Point point = {x/46,y/46};
    return point;
}

void updateBoard(){
    if ((game.control.mouse_x > 0) && (game.control.mouse_y > 0)){
        SDL_Point tile = whichTile(game.control.mouse_x, game.control.mouse_y);
        printf("(col:%d,row:%d)\n" , tile.x , tile.y);
        game.board[tile.y][tile.x] = 1;
    }
}

#endif /* game_h */
