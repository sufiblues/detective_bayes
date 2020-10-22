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

//TODO: Change selected tile to SDL_Point
typedef struct Game{
    int board[16][9];
    RandomVariable tiles[16][9];
    int screen_width;
    int screen_height;
    Controller control;
    int selected_tilex;
    int selected_tiley;
    SDL_Rect addPMF;
    SDL_Rect subtractPMF;
    bool change;
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
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 9; j++){
            initRandomVariable(&game.tiles[i][j]);
        }
    }
    game.addPMF.x = (game.screen_width-(46*4));
    game.addPMF.y = (game.screen_height-(46));
    game.addPMF.w = 46;
    game.addPMF.h = 46;
    game.change = false;
}

void updateAddProbability(float value, float probability){
    if (game.tiles[game.selected_tiley][game.selected_tilex].P[0] < probability){
        printf("Could not add probability\n");
    }
}
//TODO: Change 46 to a generalized tilesize variable
SDL_Point whichTile(int x, int y){
    SDL_Point point = {x/46,y/46};
    return point;
}

//button
bool clickedRect(SDL_Point click , SDL_Rect button){
    if(button.x <= click.x <= (button.x + button.w) && (button.y <= click.y <=(button.y + button.h))){
        return true;
    }
    return false;
}
//check to see if the user clicked the add or minus box
void updateBoard(){
    if ((game.control.mouse_x > 0) && (game.control.mouse_y > 0)){
        SDL_Point tile = whichTile(game.control.mouse_x, game.control.mouse_y);
        printf("(col:%d,row:%d)\n" , tile.x , tile.y);
        //if the player clicks under the gameboard it won't update the selected tile
        if(game.control.mouse_y <(game.screen_height - (46*4))){
            game.selected_tilex = tile.x;
            game.selected_tiley = tile.y;
        }
        else{
            SDL_Point click = {game.control.mouse_x , game.control.mouse_y};
            if(clickedRect(click, game.addPMF)){
                addRandomVariable(&game.tiles[game.selected_tiley][game.selected_tilex], 3, .03);
                game.change = true;
                
            }
            
        }
        //game.board[tile.y][tile.x] = 1;
    }
}



#endif /* game_h */
