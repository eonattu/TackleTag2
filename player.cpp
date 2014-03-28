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
  /*
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
*/
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


int player::getOffSetX(){ //returns x position coordinate
	return offSetX;
}

int player::getOffSetY(){ //returns y position coordinate
	return offSetY;
}

void player::setOffSetY(int num){ //sets y position coordinate
	offSetY = num;
}

void player::setStarting(bool val){ //sets variable tracking start of game
	isStarting = val;
}

int player::collision(){return 0;} //processes collision

void player::setIsVisible(bool vis){isVisible = vis;} //sets variable tracking whether player is visible on screen

bool player::check_collision(Sprite *obstacle){
  /*

 //checks for collision with an obstacle
	    if(isDead) return false; //otter has died. no need to check collisions
            if(obstacle->getHasCollided()){return false;} //if the obstacle has already been collided with, do not process
            //get x and y coodinates of obstacle
	    int x = obstacle->getOffSetX();
            int y = obstacle->getOffSetY();
	    //The sides of the collision rectangles
	    int leftOtter, leftObstacle;
	    int rightOtter, rightObstacle;
	    int topOtter, topObstacle;
	    int bottomOtter, bottomObstacle;

	    //set edges of obstacle's collision rectangle	  
	    leftObstacle = x;
	    rightObstacle = x+24;
	    topObstacle = y;
	    bottomObstacle = y+10;

		//sets edges of otter's collision rectangle based on otter's state
		if ((status == SPRITE_UP) || (frame == 0)){ //swim0
		  leftOtter = offSetX;
	    	  rightOtter = offSetX+32;
		  topOtter = offSetY+7;
	    	  bottomOtter = offSetY+31;
		}
		
		if ((status == SPRITE_UP) || (frame == 1)){ //swim1
		  leftOtter = offSetX;
	    	  rightOtter = offSetX+32;
		  topOtter = offSetY+3;
	    	  bottomOtter = offSetY+31;
		}
		
		if (status == SPRITE_DOWN){ //fall0
		  leftOtter = offSetX;
	    	  rightOtter = offSetX+32;
		  topOtter = offSetY+1;
	    	  bottomOtter = offSetY+31;
		}
		
		if (status == SPRITE_WALK){ //walk
		  leftOtter = offSetX;
	    	  rightOtter = offSetX+31;
		  topOtter = offSetY+13;
	    	  bottomOtter = offSetY+31;
		}


		if (status == ROLL && ((frame==0)||(frame==2)) ){ //roll0 and roll2
		  leftOtter = offSetX;
		  rightOtter = offSetX+33;
		  topOtter = offSetY+6;
		  bottomOtter = offSetY+32;
		}

		if (status == ROLL && ((frame==1)||(frame==3)) ){ //roll1 and roll3
		  leftOtter = offSetX;
		  rightOtter = offSetX+26;
		  topOtter = offSetY;
		  bottomOtter = offSetY+32;
		}

	    //if obstacle and otter rectangles are not overlapping on any side
	    if( bottomOtter <= topObstacle ){ //obstacle is under otter
		return false;
	    }

	    if( topOtter >= bottomObstacle ){ //obstacle is above otter
	        return false;
	    }

	    if( rightOtter <= leftObstacle ){ //obstacle has not reached otter yet
	        return false;
	    }

	    if( leftOtter >= rightObstacle ){ //obstacle has passed the otter
	        return false;
	    }

	    //if obstacle and otter rectangles are overlapping
	    return true;

  */
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

/*

void player::handle_events(SDL_Event &event){ //checks for input events such as spacebar press
    // if a key is currently pressed
    if(event.type == SDL_KEYDOWN){
        switch(event.key.keysym.sym){ //check if key pressed was spacebar
			case SDLK_SPACE: velocityY = -1*(width / 2); //set otter to move up is spacebar pressed
            break; // break once the velocity has been pressed
        }
    }
    // if the spacebar is currently unpressed
    if(event.type == SDL_KEYUP){
        //Set the velocity
        switch(event.key.keysym.sym){
            case SDLK_SPACE: velocityY = (width / 2);
            break; // break once the velocity is set
        }
    }
}




void player::move(){ //moves otter up and down on screen based on velocity
  if(isStarting) //if very start of the game
  {
	offSetY += (width/2); //move otter into water
	if(isStarting && offSetY>20){isStarting = false;} //if the otter is in the water
  }else{
    // increase the offSet based on the value of the velocity (up or down)
    offSetY += velocityY;

    // stop the sprite from going out of bounds
    	if(((offSetY < 20) || ( offSetY + height > SCREEN_HEIGHT)) && !isStarting){
        	offSetY -= velocityY; // balance addition of velocity so the offset will no longer change is going out of bounds
    	}
  }
}


*/
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
		
