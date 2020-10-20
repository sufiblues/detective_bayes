#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
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
TTF_Font* gFont = NULL;


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
        gWindow = SDL_CreateWindow( "Detective Bayes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
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
            if(TTF_Init() < 0){
                printf("TTF could not be initialized\n");
            }
        }
    }
    return success;
}
void drawMenu(){
    SDL_SetRenderDrawColor(gRenderer, 132, 132, 5, SDL_ALPHA_OPAQUE);
    SDL_Rect menu = {0,(WINDOW_HEIGHT -(4*46)),WINDOW_WIDTH , (4*46)};
    SDL_RenderFillRect(gRenderer, &menu);
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
    for (int i = 0; i < 16-4; i++){
        for (int j = 0; j < (9); j++){
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
    for(int i =0; i< ((rows+1)-4); i++){
        SDL_RenderDrawLine(gRenderer, 0, (i*46), WINDOW_WIDTH, (i*46));
    }
    
    for(int i =0; i < cols+1; i++){
        //finish the verticle line to make room for menu
        SDL_RenderDrawLine(gRenderer, (i*46), 0, (i*46), (WINDOW_HEIGHT-(4*46)));
    }
    
}
//TODO: Need to create function that only destroys texture when it detects a change
//TODO: Maybe create one giant texture
void drawPMF(RandomVariable rv, TTF_Font* font){
    int zeroed_x = WINDOW_WIDTH-(4*46);
    int zeroed_y = WINDOW_HEIGHT-(4*46);
    int offset = (WINDOW_HEIGHT - zeroed_y)/11;
    char buffer[30] = {0};
    SDL_Color test_c = {1,3,243,SDL_ALPHA_OPAQUE};
    for(int i = 0; i < rv.storage; i++){
        sprintf(buffer, "(Value:%.2f,Probability:%.2f)" , rv.X[i] , rv.P[i]);
        SDL_Surface *surfTemp = TTF_RenderText_Solid(font, buffer, test_c);
        SDL_Texture *text = SDL_CreateTextureFromSurface(gRenderer, surfTemp);
        SDL_FreeSurface(surfTemp);
        surfTemp = NULL;
        SDL_Rect temp = {zeroed_x, zeroed_y+(i*offset), NULL ,NULL};
        SDL_QueryTexture(text, NULL, NULL, &temp.w, &temp.h);
        SDL_RenderCopy(gRenderer, text, NULL, &temp);
        SDL_DestroyTexture(text);
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
    printf("%d\n",rv.storage);
    
    
    int frame_time;
    int frame_start;
    init();
    gFont = TTF_OpenFont("detective_bayes/Roboto-Black.ttf", 12);
    SDL_Color test_c = {1,3,243,SDL_ALPHA_OPAQUE};
    SDL_Surface *surf = TTF_RenderText_Solid(gFont, "Expectation", test_c);
    SDL_Texture* text = SDL_CreateTextureFromSurface(gRenderer, surf);
    SDL_Rect textRect;
    textRect.x = 0;
    textRect.y = WINDOW_HEIGHT - (4*46);
    SDL_FreeSurface(surf);
    
    SDL_QueryTexture(text, NULL, NULL, &textRect.w , &textRect.h);
    
    
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
        drawMenu();
        SDL_RenderCopy(gRenderer, text, NULL, &textRect);
        
        drawPMF(rv, gFont);
        
        SDL_RenderPresent(gRenderer);
        
        frame_time = SDL_GetTicks() - frame_start;
        if(FRAME_DELAY>frame_time){
            SDL_Delay(FRAME_DELAY-frame_time);
        }
    }
    
    
    endDestroy();
    
    SDL_Quit();
     
   
    return 0;
}
