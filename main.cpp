#include "background.h"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "Global.h"
#include "Timer.h"
#include "player.h"
#include "sprite.h"
#include <ctime>
#include <cstdlib>

#include<iostream>

int main(int argc, char* args[]){

  srand (time(NULL));
  		
    //Quit flag
  bool quit = false;
  
  //Initialize
  if(init() == false){
    return 1;
  }

  
  player playerND("player1.bmp", 255, 255, 255, SCREEN_HEIGHT/2, SCREEN_WIDTH/2);
  player playerUSC("player1.bmp", 255, 255, 255,0 ,0);
  
  //The frame rate regulator
  Timer fps;
  
  //The background
    Background background("background.bmp",screen);
    
    playerUSC.counter = 1;
    
    // Start game
    
    while(quit == false)
      {

	fps.start();
	playerND.setIsVisible(true);
	//While there's events to handle
        while(SDL_PollEvent(&event))
	  {
	    	playerUSC.counter++;
	    playerND.handle_events(event);
	    
	    
	    //If the user has Xed out the window
	    if(event.type == SDL_QUIT)
	      {
		//Quit the program
		quit = true;
	      }
	  }
	playerUSC.handle_AI(playerND.getOffSetX(),playerND.getOffSetY());
	
	playerND.move();
	playerUSC.move();
	background.show(screen);
	playerND.show(screen);
	playerUSC.show(screen);
	
	
		    playerUSC.handle_AIadjust();
		    
	if (playerND.collisioncheck(playerUSC.getOffSetX(),playerUSC.getOffSety() ) )
	{
		
		quit = true;
	}
		    
		    
	//Update the screen
        SDL_Flip(screen);
	//SDL_Flip(playerND.sprite);	

	
	//Cap the frame rate
        if(fps.get_ticks() < 1000 / FRAMES_PER_SECOND)
	  {
	    SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
	  }
		
      }
    //Clean up
    SDL_Quit();
    
    return 0;
}
