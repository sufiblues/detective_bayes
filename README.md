# Detective Bayes
A puzzle game where the player solves mysteries using primitive discrete probability. This repo is a prototype for how i would want the game to play out. It is written completely in C. 
## Build Instructions 
I have only tested this in xcode other builds will require a makefile.
## Adding Dependencies on Mac
This game requires the SDL2 library. On mac this library is a pain to use but here are some instructions on how to use it in xcode
First download the following:
https://www.libsdl.org/download-2.0.php
Download "SDL2-2.0.12.dmg"
Double click the file, there should be a "SDL2.frameworks" folder
copy that folder to /Library/Frameworks/
NOTE: This is root/Library/Frameworks NOT System/Library <- hopefully this saves you some trouble
## Linking Libraries in Xcode
Now that we have SDL2 in our frameworks we can link it to our project
if you have the .xcodeproj file this should be done for you. 

