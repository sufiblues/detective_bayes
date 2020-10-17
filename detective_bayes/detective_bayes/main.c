//
//  main.c
//  detective_bayes
//
//  Created by Ali Hamdani on 10/17/20.
//

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

//Screen dimensions
const int WINDOW_WIDTH = 414;
const int WINDOW_HEIGHT = 736;

//initialize sdl window
bool init(void);
//close window
bool window_close(void);
//global window and surface
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

bool init()
{
    //Initialization flag
    bool success = true;
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        SDL_Log( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else{
        //Create window
        gWindow = SDL_CreateWindow( "astroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL ){
            SDL_Log( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else{
            //create renderer
            gRenderer = SDL_CreateRenderer(gWindow,-1,0);
            if(gRenderer == NULL){
                SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            }
        }
    }
    return success;
}


int main(int argc, const char * argv[]) {
  
    init();
    
    return 0;
}
