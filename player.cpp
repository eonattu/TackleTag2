#include "sprite.h"
#include "player.h"
#include "SDL/SDL.h"
#include <vector>
#include <string>

player::player(std::string filename, int r, int g, int b):Sprite(4), SPRITE_DOWN(0), SPRITE_UP(1), SPRITE_RIGHT(2), SPRITE_LEFT(3){ //constructor
    //Initialize sprite dimensions
    height = 175;
    width = 175;

    //Initialize movement variables
    offSetY = 10;
    offSetX = 10;
    velocityX = 0;
    velocityY = 0;
	
    isStarting = true;

    //Initialize animation variables
    frame = 0;
    status = SPRITE_LEFT;

    //Sprite pointer
    sprite = load_image(filename,r,g,b);

    //Initialize States
    set_clips();
    
    isVisible = true;
    isDead = false;
}

void player::setDead(bool dead)
{
	if(dead) isDead = true;
	else isDead = false;
}

void player::set_clips(){ //sets sprite sheet clip positions
    
  //Clip the sprites
  
  //down
  
    states[0][0].x = 0; 
    states[0][0].y = 350;
    states[0][0].w = width;
    states[0][0].h = height;

    states[0][1].x = 175;
    states[0][1].y = 350;
    states[0][1].w = width;
    states[0][1].h = height;

    states[0][2].x = 350; 
    states[0][2].y = 350;
    states[0][2].w = width;
    states[0][2].h = height;

    states[0][3].x = 525;
    states[0][3].y = 350;
    states[0][3].w = width;
    states[0][3].h = height;
    
    
    // up
    
    // SPRITE TO BE FINISHED SOON
    
    // right

    states[2][0].x = 0; 
    states[2][0].y = 175;
    states[2][0].w = width;
    states[2][0].h = height;

    states[2][1].x = 175;
    states[2][1].y = 175;
    states[2][1].w = width;
    states[2][1].h = height;

    states[2][2].x = 350; 
    states[2][2].y = 175;
    states[2][2].w = width;
    states[2][2].h = height;

    states[2][3].x = 525;
    states[2][3].y = 175;
    states[2][3].w = width;
    states[2][3].h = height;

    states[2][4].x = 700; 
    states[2][4].y = 175;
    states[2][4].w = width;
    states[2][4].h = height;

    states[2][5].x = 875; 
    states[2][5].y = 175;
    states[2][5].w = width;
    states[2][5].h = height;

    //left
    states[3][0].x = 0; 
    states[3][0].y = 0;
    states[3][0].w = width;
    states[3][0].h = height;

    states[3][1].x = 175;
    states[3][1].y = 0;
    states[3][1].w = width;
    states[3][1].h = height;

    states[3][2].x = 350; 
    states[3][2].y = 0;
    states[3][2].w = width;
    states[3][2].h = height;

    states[3][3].x = 525;
    states[3][3].y = 0;
    states[3][3].w = width;
    states[3][3].h = height;

    states[3][4].x = 700; 
    states[3][4].y = 0;
    states[3][4].w = width;
    states[3][4].h = height;

    states[3][5].x = 875; 
    states[3][5].y = 0;
    states[3][5].w = width;
    states[3][5].h = height;
    
}


int player::getOffSetX()
{
  return offSetX;
}

int player::getOffSetY()
{
  return offSetY;
}

void player::setOffSetY(int num)
{
  offSetY = num;
}

void player::setStarting(bool val)
{
  isStarting = val;
}

int player::collision(){return 0;} 

void player::setIsVisible(bool vis){isVisible = vis;} 

bool player::check_collision(Sprite *obstacle)
{
  // to be instatiated later
}



void player::handle_events(SDL_Event &event)
{
  int velocity = 20;
  
  //If a key was pressed
  if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
      switch( event.key.keysym.sym )
        {
	case SDLK_UP: velocityY -= velocity; break;
	case SDLK_DOWN: velocityY += velocity; break;
	case SDLK_LEFT: velocityX -= velocity; break;
	case SDLK_RIGHT:velocityX  += velocity; break;
        }
    }
  
  //If a key was released
    else if( event.type == SDL_KEYUP )
      {
        //Adjust the velocity
        switch( event.key.keysym.sym )
	  {
	  case SDLK_UP: velocityY += velocity; break;
	  case SDLK_DOWN: velocityY -= velocity; break;
	  case SDLK_LEFT: velocityX += velocity; break;
	  case SDLK_RIGHT: velocityX -= velocity; break;
	  }
      }
}

void player::move()
{
  offSetX += velocityX;
  
  // Check boundary conditions
  if( ( offSetX < 0 ) || ( offSetX > SCREEN_WIDTH ) )
    {
      offSetX -= velocityX;
    }  
  
  offSetY += velocityY;
  
  // Check boundary conditions
  if( ( offSetY < 0 ) || ( offSetY > SCREEN_HEIGHT ) )
    {
      offSetY -= velocityY;
    }
}


void player::show(SDL_Surface *screen)
{ //shows correct sprite of otter for each frame based upon state
  if(isVisible)
    {
      if(velocityY > 0)
	{
	  status = SPRITE_DOWN; // set animation status to down
	  
	  
	  //Move to the next frame in the animation
	  frame++;
	}
      
      //If Sprite is moving up
      else if(velocityY < 0 )
	{
	  status = SPRITE_UP;
	  frame++; //Move to the next frame in the animation
	}
      
      else if(velocityX > 0)
	{
	  status = SPRITE_RIGHT;
	  frame++;
	}
      
      else if(velocityX < 0)
	{
	  status = SPRITE_LEFT;
	  frame++;
	}
      
      
      
      if( status == SPRITE_DOWN )
	{

	  apply_surface(sprite, screen, &states[0][frame] ); 
	}
      
      else if( status == SPRITE_UP )
	{ 
	  apply_surface(sprite, screen, &states[1][frame] ); 
	}
      
      else if( status == SPRITE_RIGHT )
	{
	  apply_surface(sprite, screen, &states[2][frame] );
	}
      
      else if( status == SPRITE_LEFT)
	{ 
	  apply_surface(sprite, screen, &states[3][frame] );
	}
      
      if(frame<6)
	{ 
	  frame=0;
	}
    }
} 


int player::getStatus() //returns state that otter is currently in
{
  return status;
}

