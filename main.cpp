#include "background.h"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "Global.h"
#include "Timer.h"
#include "player.h"
#include "sprite.h"
#include "scoreCounter.h"
#include "menuScreen.h"
#include <ctime>
#include <cstdlib>

#include<iostream>

int main(int argc, char* args[]){

  srand (time(NULL));
  		
    //Quit flag
  bool quit = false;
  bool start = false;
  
  //Initialize
  if(init() == false){
    return 1;
  }

  
  player playerND("player1.bmp", 255, 255, 255, SCREEN_HEIGHT/2, SCREEN_WIDTH/2);
  player playerUSC("player1.bmp", 255, 255, 255,0 ,0);
  bool tackle = false;
  bool fall = false;
 
  //The frame rate regulator
  Timer fps;
  
  //The background
    Background background("background.bmp",screen);
    background.show(screen);

    MenuScreen menu("Welcome.bmp", 255,255,0);
    
    playerUSC.counter = 1;
   
    scoreCounter scoreCount("numbers.bmp",255,255,255);
    int score = 0;
    
    // Start game
    
    while(quit == false)
      {
	while(start == false)
	  {
	    Timer mps;
	    mps.start();
	    scoreCount.setTitle(false);
	     
	    while(SDL_PollEvent(&event))
	      {
		start=menu.handle_event(event);
		 
	      }
	    
	    menu.show(screen,false, false);
	    SDL_Flip(screen);
	   
	    
	    if (mps.get_ticks() < 1000/ FRAMES_PER_SECOND)
	      {
		SDL_Delay( ( 1000/FRAMES_PER_SECOND) - mps.get_ticks() );
	      }
	    
	    if(score > 0)
	      {
		score = 0;
		
		playerND.setIsVisible(true);
		playerUSC.setIsVisible(true);
		
	      }
	    playerND.setStarting(true);
	    playerUSC.setStarting(true);
	  }
	
	// BEGIN GAME
		

	scoreCount.setTitle(true);
	menu.setHasPlayed(true);
	fps.start();

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


	playerUSC.handle_AIadjust();
	playerUSC.handle_AI(playerND.getOffSetX(),playerND.getOffSetY());
	
	tackle = playerUSC.collisioncheck(playerND.getOffSetX(),playerND.getOffSetY(), 120);
	fall = playerUSC.collisioncheck(playerND.getOffSetX(), playerND.getOffSetY(),60);
	
	//   cout << tackle << endl;
	
	
	
	

	playerND.move();
	playerUSC.move();
       
	    
	score += 10;
	scoreCount.setScore(score);

	//scoreCount.show(screen, false, false);
	background.show(screen);
	playerND.show(screen, false, fall); // nd will never tackle
	playerUSC.show(screen, tackle, false); // usc will never fall
	scoreCount.show(screen, false, false);





	//Update the screen
        SDL_Flip(screen);
	//SDL_Flip(playerND.sprite);	

	
	//Cap the frame rate
        if(fps.get_ticks() < 1000 / FRAMES_PER_SECOND)
	  {
	    SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
	  }
       

	if(fall == true)
	  {
	    start = false;
	    score = 0;
	    tackle = false;
	    fall = false;
	    playerND.setOffSetX(SCREEN_WIDTH/2);
	    playerND.setOffSetY(SCREEN_HEIGHT/2);

	    playerUSC.setOffSetX(0);
	    playerUSC.setOffSetY(0);
		    
	    playerUSC.handle_AIadjust();
	    playerND.handle_AIadjust();


	  }



		
      }
    //Clean up
    SDL_Quit();
    
    return 0;
}
