// Author: Adrian A. Gerbaud H.


#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

//This header will include information pertaining to the the screen

const int SCREEN_WIDTH = 1000;//450; // 640
const int SCREEN_HEIGHT = 1000;// 800; //480
const int SCREEN_BPP = 32;
static SDL_Surface *screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
//static SDL_Surface *flappy = IMG_Load("flappybackground.png");

