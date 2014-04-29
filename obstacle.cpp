#include "sprite.h"
#include "obstacle.h"
#include "SDL/SDL.h"
//#include "Global.h"
#include <vector>
#include <string>
#include <iostream>

obstacle::obstacle(std::string filename, int r, int g, int b,int x, int y):Sprite(1){ //constructor



    //Initialize movement variables
    offSetX = x;
    offSetY = y;
    //offSetY = (rand() % SCREEN_HEIGHT +200);
    //offSetX = (rand() % SCREEN_WIDTH +200);
    velocityX = 0;
    velocityY = 0;
    
    isStarting = true;
    
    //Sprite pointer
    sprite = load_image(filename,r,g,b);

    //Initialize State
    set_clips();
    
    isVisible = true;
}

int obstacle::getOffSetX(){ //returns x position
	return offSetX;
}

void obstacle::setIsVisible(bool vis){isVisible = vis;} 

int obstacle::getOffSetY(){ //returns y position
	return offSetY;
}



void obstacle::move(){} //virtual function from inheritance
void obstacle::setStarting(bool val)
{
  isStarting = val;
}

void obstacle::set_clips()
{ //sets clip positions for cone sprite
    //Clip the sprites
    states[0][0].x = 0; //title
    states[0][0].y = 0;
    states[0][0].w = 50;
    states[0][0].h = 70;

}
void obstacle::setOffSetY(int num)
{
  offSetY = num;
}

void obstacle::setOffSetX(int num)
{
  offSetX=num;
}

int obstacle::collision(){return 0;} //virtual function from inheritance


void obstacle::show(SDL_Surface *screen,bool tackle,bool fall)
{
	if (isVisible)
	  {	
	  apply_surface(sprite, screen, &states[0][0] ); 
	  }

}
