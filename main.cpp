#include "background.h"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "Global.h"
#include "Timer.h"
#include "player.h"
#include "sprite.h"

int main(int argc, char* args[]){

  player playerND("player.bmp", 255, 255, 255);
  
    //Quit flag
    bool quit = false;

    //Initialize
    if(init() == false){
        return 1;
    }

    //The frame rate regulator
    Timer fps;

    //The background
    Background background("background.bmp",screen);
    
    // Start game
    
    while(quit == false)
      {
	
	fps.start();
	playerND.setIsVisible(true);
	//While there's events to handle
        while(SDL_PollEvent(&event))
	  {
	    
	    playerND.handle_events(event);
	    
	    //If the user has Xed out the window
	    if(event.type == SDL_QUIT){
	      //Quit the program
	      quit = true;
	    }
	  }
       
	playerND.move();
	//Update the screen
        SDL_Flip(screen);
	SDL_Flip(playerND.sprite);	

	
	//Cap the frame rate
        if(fps.get_ticks() < 1000 / FRAMES_PER_SECOND){
	  SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
	}
	

      }
    //Clean up
    SDL_Quit();
    
    return 0;
}
