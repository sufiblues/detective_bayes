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
    int click_frames_held;

}Controller;

char* test;

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
    
    SDL_Rect exp;
    SDL_Rect cond_exp;
    
    SDL_Rect greate;
    SDL_Rect greatne;
    SDL_Rect lesse;
    SDL_Rect lessne;
    
    SDL_Rect cond;
    SDL_Rect val;
    SDL_Rect prob;
    
    char input_fields[4][6];
    int input_fields_size[4];
    int input_field_selected;
    
    int relation;
}Game;

Game game;


//need to handle input in an intuitive way
//TODO: Check input is only numerical
void inputs( bool* a, struct Controller* xbone){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        switch (event.type) {
            case SDL_QUIT:
                *a = true;
            case SDL_KEYDOWN:
                //Handle backspace
                if( event.key.keysym.sym == SDLK_BACKSPACE && game.input_fields_size[game.input_field_selected] >= 0 )
                {
                    //lop off character
                    if(game.input_fields_size[game.input_field_selected] != 0){
                        printf("Backspace\n");
                        game.input_fields_size[game.input_field_selected]-=1;
                    }
                    game.input_fields[game.input_field_selected][game.input_fields_size[game.input_field_selected]] = 0;
                    
                }
                //Handle copy
                else if( event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
                {
                    //figure out cliboard cut
                    //SDL_SetClipboardText( inputText.c_str() );
                    
                }
                //Handle paste
                else if( event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
                {
                    test = SDL_GetClipboardText();
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
                xbone->click_frames_held = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                xbone->mouse_x = -1;
                xbone->mouse_y = -1;
                xbone->click_frames_held = 0;
                break;
            case SDL_TEXTINPUT:
                if (game.input_fields_size[game.input_field_selected] >= 4){
                    printf("Too many character in input\n");
                }
                else{
                    game.input_fields[game.input_field_selected][game.input_fields_size[game.input_field_selected]] = event.text.text[0];
                    (game.input_fields_size[game.input_field_selected])++;
                    printf("tsize%d",game.input_fields_size[game.input_field_selected]);
                }
                break;
        }
    }
    if(xbone->click_frames_held >= 1){
        xbone->click_frames_held++;
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
    
    game.val.x = (game.screen_width - (46*2));
    game.val.y = (game.screen_height - (46));
    game.val.w = 46;
    game.val.h = 46;
    
    game.prob.x = (game.screen_width - (46));
    game.prob.y = (game.screen_height - (46));
    game.prob.w = 46;
    game.prob.h = 46;
    
    game.subtractPMF.x = (game.screen_width - (46*3));
    game.subtractPMF.y = game.screen_height - 46;
    game.subtractPMF.w = 46;
    game.subtractPMF.h = 46;
    
    game.change = false;
    
    game.control.click_frames_held = 0;
    
    game.cond.x = 0;
    game.cond.y = game.screen_height - (46*(2.5));
    game.cond.h = (46/2);
    game.cond.w = (46*3);
    
//    TODO: This can be done in a for loop, create an array for these rects
    game.greate.x = 0;
    game.greatne.x = 46;
    game.lesse.x = (46*2);
    game.lessne.x = (46*3);
    game.greate.y = (game.screen_height - (46*2));
    game.greatne.y = (game.screen_height - (46*2));
    game.lesse.y = (game.screen_height - (46*2));
    game.lessne.y = (game.screen_height - (46*2));
    game.greate.w = 46;
    game.greatne.w = 46;
    game.lesse.w = 46;
    game.lessne.w = 46;
    game.greate.h = 46;
    game.greatne.h = 46;
    game.lesse.h = 46;
    game.lessne.h = 46;

    game.exp.x = 0;
    game.exp.y = game.screen_height - (46*4);
    
    game.cond_exp.x = 0;
    game.cond_exp.y = game.screen_height - (46*3);
    
    game.input_fields_size[3] = 0;
    
    
        
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
    if((button.x <= click.x) &&
        (click.x <= (button.x + button.w)) &&
       (button.y <= click.y) &&
        (click.y<=(button.y + button.h))){
        return true;
    }
    return false;
}
//check to see if the user clicked the add or minus box
//on the first frame of a click but stops repeat presses
void updateBoard(){
    if ((game.control.mouse_x > 0) && (game.control.mouse_y > 0) && (game.control.click_frames_held <= 2)){
        SDL_Point tile = whichTile(game.control.mouse_x, game.control.mouse_y);
        //printf("(col:%d,row:%d)\n" , tile.x , tile.y);
        //if the player clicks under the gameboard it won't update the selected tile
        if(game.control.mouse_y <(game.screen_height - (46*4))){
            game.selected_tilex = tile.x;
            game.selected_tiley = tile.y;
        }
        else{
            SDL_Point click = {game.control.mouse_x , game.control.mouse_y};
            if(clickedRect(click, game.addPMF)){
                addRandomVariable(&game.tiles[game.selected_tiley][game.selected_tilex], atof(game.input_fields[1]), atof(game.input_fields[2]));
                game.change = true;
            }
            else if(clickedRect(click, game.subtractPMF)){
                subtractRandomVariable(&game.tiles[game.selected_tiley][game.selected_tilex]);
                game.change = true;
            }
            else if(clickedRect(click, game.cond)){
                printf("Cond\n");
                game.input_field_selected = 0;
            }
            else if(clickedRect(click, game.val)){
                printf("val\n");
                game.input_field_selected = 1;
            }
            else if(clickedRect(click, game.prob)){
                printf("prob\n");
                game.input_field_selected = 2;
            }
            else if(clickedRect(click, game.greate))
            {
                printf("Clicked > relation\n");
                game.relation = GREATER_EQ;
            }
            else if (clickedRect(click, game.greatne)){
                printf("Clicked >= relation\n");
                game.relation = GREATER_NEQ;
            }
            else if (clickedRect(click, game.lesse)){
                printf("Clicked < relation\n");
                game.relation = LESS_EQ;
            }
            else if (clickedRect(click, game.lessne)){
                printf("Clicked <= relation\n");
                game.relation = LESS_NEQ;
            }
        }
        //game.board[tile.y][tile.x] = 1;
    }
}

#endif /* game_h */
