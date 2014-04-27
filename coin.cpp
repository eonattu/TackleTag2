#include "sprite.h"
#include "coin.h"
#include "SDL/SDL.h"
#include <vector>
#include <string>
#include <iostream>

Coin::Coin(std::string filename, int r, int g, int b,int randX, int randY):Sprite(2), SPIN(0), SCORE(1){

    hasCollided = false;
  
    //Initialize movement variables
    offSetY = randY;
    offSetX = randX;
    velocityX = 0;
    velocityY = 0;

    //Initialize animation variables
    frame = 0;
    status = SPIN;

    //Sprite pointer
    sprite = load_image(filename,r,g,b);
    
    //Initialize States
    set_clips();
}

int Coin::getOffSetX(){ //returns x position
	return offSetX;
}

int Coin::getOffSetY(){ //returns y position
	return offSetY;
}

void Coin::set_clips(){ //sets clip location for sprite sheets // ADD HERE
    //Clip the sprites
   
    states[0][0].x = 153; //SPIN
    states[0][0].y = 7;
    states[0][0].w = 14;
    states[0][0].h = 8;

    states[1][1].x = 0; //SCORE
    states[1][1].y = 0;
    states[1][1].w = 0;
    states[1][1].h = 0;

}

int Coin::collision(){ //if a collision has happened with a coin
	status = SCORE; //switch to show score sprites instead of coin
	hasCollided = true; //set collided to true
	return 2; //collision was with a coin
}


void Coin::move(){}

void Coin::show(SDL_Surface *screen)
{
  if (status == SCORE)
    {
      frame=0;
      apply_surface(sprite, screen, &states[1][frame]); //display score sprite
    }
  
  if (status == SPIN)
    {
      apply_surface(sprite, screen, &states[0][frame]); //display sprite
    }
}
