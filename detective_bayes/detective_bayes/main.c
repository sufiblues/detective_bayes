#include <SDL2/SDL.h>
#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include "game.h"

//Screen dimensions
const int WINDOW_WIDTH = 414;
const int WINDOW_HEIGHT = 736;
const int NO_COLS = 9;
const int NO_ROWS = 16;
const double FRAME_RATE = 15.0;
const double FRAME_DELAY = 1000/FRAME_RATE;



//initialize sdl window
bool init(void);
//close window
bool window_close(void);
//global window and surface
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

//initializes window,rendrer,and surface
bool init()
{
    //Initialization flag
    bool success = true;
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else{
        //Create window
        gWindow = SDL_CreateWindow( "astroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL ){
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else{
            //create renderer
            gRenderer = SDL_CreateRenderer(gWindow,-1,0);
            if(gRenderer == NULL){
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            }
        }
    }
    return success;
}

//destroys renderer and window
void endDestroy()
{
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
}


void drawRect(SDL_Rect rect,int col1,int col2, int col3){
    SDL_SetRenderDrawColor(gRenderer, col1, col2, col3, SDL_ALPHA_TRANSPARENT);
    SDL_RenderFillRect(gRenderer, &rect);
}

//TODO: Replace 46 with generic tilesize
void drawBoard(){
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 245, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 9; j++){
            if (game.board[i][j] > 0){
                SDL_Rect temp = {j*46,i*46,46,46};
                SDL_RenderFillRect(gRenderer, &temp);
            }
        }
    }
}

//TODO: Change 46 to generic tilesize
void drawGrid(int rows, int cols){
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for(int i =0; i< rows+1; i++){
        SDL_RenderDrawLine(gRenderer, 0, (i*46), WINDOW_WIDTH, (i*46));
    }
    for(int i =0; i < cols+1; i++){
        SDL_RenderDrawLine(gRenderer, (i*46), 0, (i*46), WINDOW_HEIGHT);
    }
}

int main()
{
    RandomVariable rv;
    initRandomVariable(&rv);
    printRandomVariable(rv);
    addRandomVariable(&rv, 1.0f, 0.01f);
    addRandomVariable(&rv, 2.0f, 0.01f);
    addRandomVariable(&rv, 3.0f, 0.01f);
    addRandomVariable(&rv, 4.0f, 0.01f);
    addRandomVariable(&rv, 5.0f, 0.01f);
    addRandomVariable(&rv, 6.0f, 0.01f);
    addRandomVariable(&rv, 7.0f, 0.01f);
    addRandomVariable(&rv, 8.0f, 0.01f);
    addRandomVariable(&rv, 9.0f, 0.01f);

    float pr = probabilityCondition(rv,2,GREATER_NEQ);
    float ex = expectation(rv);
    printf("Testing probability %f", ex);
    /*
    int frame_time;
    int frame_start;
    init();
    bool done = false;
    while (!done) {
        
        frame_start = SDL_GetTicks();
        
        inputs(&done, &game.control);
        updateBoard();
        
        //draw background
        if(game.control.mouse_x>0 && game.control.mouse_y > 0){
            SDL_Point tile = whichTile(game.control.mouse_x, game.control.mouse_y);
            printf("Clicked (%d,%d)\n" , tile.x, tile.y);
        }
        
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        
        drawGrid(NO_ROWS, NO_COLS);
        drawBoard();
    
        SDL_RenderPresent(gRenderer);
        
        
        frame_time = SDL_GetTicks() - frame_start;
        if(FRAME_DELAY>frame_time){
            SDL_Delay(FRAME_DELAY-frame_time);
        }
    }
    
    
    endDestroy();
    
    SDL_Quit();
     */
   
    return 0;
}
