
This document is a review of the prototype of detective  bayes. Things that I want to improve in the next iteration and problems with the current version. 



"main.c"
This file is the entry point for the game, it handles other aspects as well such as SDL_initializing and graphics. It also has the game loop. 
Things i want to change. 
The constants in this file need to be generalizable , in line 11 we have "const int WINDOW_WIDTH = 414", this should be written as "const in WINDOW_WIDTH = device.screen width", I want this game to run on multiple mobile devices with different resolitions. This same comment also addresses the height. 
I also want to seperate the "NO_COLS and NO_ROWS" variables into something else. I used this as a crutch for the aspect ratio. Landscape and potrait modes is something i want to address way later. 

This file Initializes the SDL_Components which is something I want in a different file. Normally it wouldnt be an issue but if i want to be cross platform with different aspect ratio/resolutions i should be abble to do this in a different file. 

Another split i want to make is with rendering. This file handles the graphics/textures of the game which is not something i want. That should be done by a different handle all together. 

The last split is with the central game loop. I think the main file is good place to store central game loops. 

"game.h"

This is where most of the event handling and game logic goes. This file is the messiest out of all of them and I definately want to refactor this into more sensible components. The first are the components that make up the game board. There are a lot of SDL_Rects that are used as buttons in the actual game. I feel this means I can create a new entity called "Button", the reason why i want to add that entity is because I access the button rects the same way, I take input from the mouse -> if collision with rect then i assign the "selected_tile" var to that rectangles ID. Having a cohesive ui generation system will be nice but i havent thought it through yet. This game has some submenus to its various systems. There is the gameboard->board and RV_description. RV_description->several textboxes and statements. I need to find a more elegant solution to this problem that also works with different resolutions. 

The controller is a very hard things to get working, I thought it would be easy but when you have text input and C doesnt have any strings, this becomes a difficult task to manage. I am not satisfied with the solution I have but I want to modularize this feature in the next iteration. The controller should have information like which button is held down for how long, mouse clicks and location, history of inputs 60 frames, most importantly it should have an ability to handle text from user. 

The update logic is not terrible, for now the update and controller seem to coupled together for my taste. I want to seperate them and I think adding more complexity will be easier. 

"rv.h"

I am happy with this file for its purpose, later I want to add more functions such as joint probability and joint conditional probability. 


For the future I want a code base that is more modular. I definately need to break up game.h into more components to add further complexity. Here is how i want to break up the code base during the next iterations
