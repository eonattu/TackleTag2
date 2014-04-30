#include "sprite.h"
#include "menuScreen.h"
#include "SDL/SDL.h"
#include <vector>
#include <string>
#include <iostream>


MenuScreen::MenuScreen(std::string filename, int r, int g, int b):Sprite(2),TITLE(0),REPLAY(1){ //constructor

    hasCollided = false;
    hasPlayed = false;

    //Initialize movement variables
    offSetY = 0;
    offSetX = 0;
    velocityX = 0;
    velocityY = 0;

    //Initialize animation variables
    frame = 0;
    status = TITLE;

    //Sprite pointer
    sprite = load_image(filename,r,g,b);

    //Initialize States
    set_clips();
}

int MenuScreen::getOffSetX(){ //returns x position
	return offSetX;
}

int MenuScreen::getOffSetY(){ //returns y position
	return offSetY;
}
int MenuScreen::getwidth(){return 1;}
int MenuScreen::getheight(){return 1;}

bool MenuScreen::getHasPlayed(){return hasPlayed;} 

void MenuScreen::setHasPlayed(bool p){hasPlayed = p;}

void MenuScreen::set_clips()
{ //sets clip positions for menu sprite
    //Clip the sprites
    states[0][0].x = 0; //title
    states[0][0].y = 0;
    states[0][0].w = 1100;
    states[0][0].h = 840;

    states[0][1].x = 1130; //replay
    states[0][1].y = 0;
    states[0][1].w = 1100;
    states[0][1].h = 840;

}

bool MenuScreen::handle_event(SDL_Event &event)
{ //watches for spacebar press to start game
	    // if the space bar is currently pressed
	    if(event.type == SDL_KEYDOWN){
	        switch(event.key.keysym.sym){
	            case SDLK_SPACE: return true;
	            break; // break once the spacebar has been pressed
	        }
	    }
	return false;
}

int MenuScreen::collision(int x, int y, int z){} //virtual function from inheritance

int MenuScreen::collisioncheck(int,int,int){}

void MenuScreen::move(int,int,int){} //virtual function from inheritance

void MenuScreen::show(SDL_Surface *screen, bool, bool)
{
	if (!hasPlayed)
	  {	
		frame = 0; //beginning screen
	  }

	else
	  {
		frame=1; //endgame screen with ability to replay
	  }

	apply_surface(sprite, screen, &states[0][frame]);
}
void MenuScreen::free()
{

	  freesurface(sprite); 

}
