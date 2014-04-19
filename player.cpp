#include "sprite.h"
#include "player.h"
#include "SDL/SDL.h"
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>

player::player(std::string filename, int r, int g, int b, int x, int y):Sprite(4), SPRITE_DOWN(0), SPRITE_UP(1), SPRITE_RIGHT(2), SPRITE_LEFT(3){ //constructor
    //Initialize sprite dimensions
    height = 120;
    width = 120;

    //Initialize movement variables
    offSetY = x;
    offSetX = y;
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
  states[0][0].y = 0;
  states[0][0].w = width;
  states[0][0].h = height;
  
  states[0][1].x = 120;
  states[0][1].y = 0;
  states[0][1].w = width;
  states[0][1].h = height;
  
  states[0][2].x = 240; 
  states[0][2].y = 0;
  states[0][2].w = width;
  states[0][2].h = height;
  
  states[0][3].x = 360;
  states[0][3].y = 0;
  states[0][3].w = width;
  states[0][3].h = height;
  
  states[0][4].x = 480; 
  states[0][4].y = 0;
  states[0][4].w = width;
  states[0][4].h = height;
  
  states[0][5].x = 600; 
  states[0][5].y = 0;
  states[0][5].w = width;
  states[0][5].h = height;
    
    
    // up
    
    states[1][0].x = 0; 
    states[1][0].y = 120;
    states[1][0].w = width;
    states[1][0].h = height;

    states[1][1].x = 120;
    states[1][1].y = 120;
    states[1][1].w = width;
    states[1][1].h = height;

    states[1][2].x = 240; 
    states[1][2].y = 120;
    states[1][2].w = width;
    states[1][2].h = height;

    states[1][3].x = 360;
    states[1][3].y = 120;
    states[1][3].w = width;
    states[1][3].h = height;

    states[1][4].x = 480; 
    states[1][4].y = 120;
    states[1][4].w = width;
    states[1][4].h = height;

    states[1][5].x = 600; 
    states[1][5].y = 120;
    states[1][5].w = width;
    states[1][5].h = height;
    
    // right

    states[2][0].x = 0; 
    states[2][0].y = 240;
    states[2][0].w = width;
    states[2][0].h = height;

    states[2][1].x = 120;
    states[2][1].y = 240;
    states[2][1].w = width;
    states[2][1].h = height;

    states[2][2].x = 240; 
    states[2][2].y = 240;
    states[2][2].w = width;
    states[2][2].h = height;

    states[2][3].x = 360;
    states[2][3].y = 240;
    states[2][3].w = width;
    states[2][3].h = height;

    states[2][4].x = 480; 
    states[2][4].y = 240;
    states[2][4].w = width;
    states[2][4].h = height;

    states[2][5].x = 600; 
    states[2][5].y = 240;
    states[2][5].w = width;
    states[2][5].h = height;

    //left

    states[3][0].x = 0; 
    states[3][0].y = 360;
    states[3][0].w = width;
    states[3][0].h = height;

    states[3][1].x = 120;
    states[3][1].y = 360;
    states[3][1].w = width;
    states[3][1].h = height;

    states[3][2].x = 240; 
    states[3][2].y = 360;
    states[3][2].w = width;
    states[3][2].h = height;

    states[3][3].x = 360;
    states[3][3].y = 360;
    states[3][3].w = width;
    states[3][3].h = height;

    states[3][4].x = 480; 
    states[3][4].y = 360;
    states[3][4].w = width;
    states[3][4].h = height;

    states[3][5].x = 600; 
    states[3][5].y = 360;
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

int player::collisioncheck(int computerX, int computerY)
{
    double xdiff = (double)computerX - (double)offSetX;
    double ydiff =  (double)computerY - (double)offSetY;
    double distance = sqrt(pow(xdiff,2) + pow(ydiff,2));

    if (distance <= width/2) return 1;
    else return 0;

}

void player::handle_AI(int userx, int usery)
{
double xdiff = (double)userx - (double)offSetX;
double ydiff = (double)usery - (double)offSetY;

double distance = sqrt(pow(xdiff,2) + pow(ydiff,2));
double velocity = 25;

double distright = sqrt(pow((xdiff+velocity),2) + pow(ydiff,2));
double distleft = sqrt(pow((xdiff-velocity),2) + pow(ydiff,2));
double distdown = sqrt(pow(xdiff,2)+pow((ydiff+velocity),2));
double distup = sqrt(pow(xdiff,2)+pow((ydiff-velocity),2));

double dist2oclock = sqrt(pow((xdiff+velocity),2)+pow((ydiff+velocity),2));
double dist5oclock = sqrt(pow((xdiff+velocity),2)+pow((ydiff-velocity),2));
double dist8oclock =sqrt(pow((xdiff-velocity),2)+pow((ydiff+velocity),2));
double dist11oclock = sqrt(pow((xdiff-velocity),2)+pow((ydiff-velocity),2));
int direction;

 if ((counter % 20) ==1) 
   {	
     direction = (rand() % 4 +1); // does random move
   }
 else
   {
     if ((distright >= distance) && (distright>=distleft) && (distright >=distdown) && (distright >=distup))
       {
	 direction = 4;
       }
     else if ((distleft >= distance) && (distleft>=distright) && (distleft >=distdown) && (distleft >=distup))
	{
	  direction = 3;
	}
     else if((distdown >= distance) && (distdown>=distleft) && (distdown >=distright) && (distdown >=distup))
       {
	 direction = 2;
       }
     else if ((distup >= distance) && (distup>=distleft) && (distup >=distdown) && (distup >=distright))
       {
	 direction = 1;
	}
   }
 
 switch(direction)
   {
   case 1: velocityY -= velocity; break;
   case 2: velocityY  += velocity; break;
   case 3: velocityX -= velocity; break;
   case 4: velocityX  += velocity; break;
	  
   }
 
}

void player::handle_events(SDL_Event &event)
{
  int velocity = 25;
  
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
  
  //If a key was released, spot
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
void player::handle_AIadjust()
{
	velocityX=0;
	velocityY=0;
}

void player::move()
{
  offSetX += velocityX;
  
  // Check boundary conditions
  if( (offSetX < 0) || ( offSetX + width > SCREEN_WIDTH ) )
    {
      offSetX -= velocityX;
    }  
  
  offSetY += velocityY;
  
  // Check boundary conditions
  if( ( offSetY < 0 ) || ( offSetY + height > SCREEN_HEIGHT ) )
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
      

      if(frame>5)
	{ 
	  frame=0;
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
      

    }
} 


int player::getStatus() //returns state that otter is currently in
{
  return status;
}

