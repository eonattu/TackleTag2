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

// Music to be played
Mix_Music *titlemusic = NULL;
Mix_Chunk *practicesound = NULL;
Mix_Chunk *crowd = NULL;
Mix_Chunk *crazytrain = NULL;
Mix_Chunk *boom = NULL;
Mix_Chunk *hit = NULL;
// Sound Effects to be played

//Initialize SDL_mixer
if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
	{
		return 1;
	}
  srand (time(NULL));
  		
    //Quit flag
  bool quit = false;
  bool start = false;
  
  //Initialize
  if(init() == false){
    return 1;
  }

//Loading the music
	titlemusic = Mix_LoadMUS("Title1.wav");
	practicesound = Mix_LoadWAV("practice1.wav");
	crowd = Mix_LoadWAV("crowd1.wav");
	crazytrain = Mix_LoadWAV("crazytrain1.wav");
	boom = Mix_LoadWAV("boom.wav");
	hit = Mix_LoadWAV("hit1.wav");
	//If there was a problem loading the sound effects
	if( ( practicesound == NULL ) || ( crazytrain == NULL )||( crowd == NULL ) || (boom==NULL)|| (hit==NULL)) 
	{ 
	return 1; 
	} 
	
// If there was a problem loading the music
	if (titlemusic == NULL)
	{
		return 1;
	}
	 vector<Sprite*> obstacles; // This will hold coins
  player playerND("player1.bmp", 255, 255, 255, SCREEN_HEIGHT/2, SCREEN_WIDTH/2);
  player playerUSC("player1.bmp", 255, 255, 255,0 ,0);
  // player playerUSC2("player1.bmp", 255, 255, 255,255 ,0);
  bool tackle = false;
  bool fall = false;
 
  //The frame rate regulator
  Timer fps;
  
  //The background
    Background background("background.bmp",screen);
    background.show(screen);

    MenuScreen menu("Welcome.bmp", 255,255,0);
    
    playerUSC.counter = 1;
    //     playerUSC2.counter = 1;
    scoreCounter scoreCount("ND_Player.bmp",255,255,255);
    int score = 0;
    int soundCounter = 0;
    // Start game
      
    while(quit == false)
      {
     
	while(start == false)
	  {
	  //If music not playing yet
	  
      if (Mix_PlayingMusic() == 0 && soundCounter==0)
      {
      	//Play music
      	if(Mix_PlayMusic(titlemusic,-1) == -1)
      	{
      		return 1;
      	}
      	
      }
       soundCounter++;
	    Timer mps;
	    mps.start();
	    scoreCount.setTitle(false);
	     
	    while(SDL_PollEvent(&event))
	      {
	    
			start=menu.handle_event(event);
				if(event.type == SDL_KEYDOWN){
			   	switch(event.key.keysym.sym){
			      	case SDLK_s:
			      	{
			      		//If the music is paused
			      		 if( Mix_PausedMusic() == 1 ) 
			      		 { 
			      		 //Resume the music 
			      		 Mix_ResumeMusic(); 
			      		 } 
			      		 //If the music is playing 
			      		 else 
			      		 { 
			      		 //Pause the music 
			      		 Mix_PauseMusic(); 
			      		 }
			      	}
			         break; // break once the 's' has been pressed
			    	}
			 	}
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
		//				playerUSC2.setIsVisible(true);
		
	      }
	    playerND.setStarting(true);
	    playerUSC.setStarting(true);
	    //	    	    playerUSC2.setStarting(true);
	  }
	
	// BEGIN GAME
		
	Mix_HaltMusic();

	scoreCount.setTitle(true);
	menu.setHasPlayed(true);
	fps.start();
	
	//If score is '10' ie. game just started 
	  if( score ==0 ) { 
	  		 Mix_HaltChannel( 4);
	  		//Play the crowd and practice sound effect 
	  		if( Mix_PlayChannel( 1, practicesound, 1 ) == -1 ) 
	  		{ 
	  				return 1; 
	  		} 
	  		if( Mix_PlayChannel( 2, crowd, 1 ) == -1 ) 
	  		{ 
	  				return 1; 
	  		} 
	  			if( Mix_PlayChannel( 3, crazytrain, 1 ) == -1 ) 
	  		{ 
	  				return 1; 
	  		} 
	  }
	  
	//While there's events to handle
        while(SDL_PollEvent(&event))
	  {


	    playerUSC.counter++;
	   //   playerUSC2.counter++;
	    playerND.handle_events(event);

	    	
	    //If the user has Xed out the window
	   if(event.type == SDL_QUIT)
	      {
		//Quit the program
		quit = true;
	      }
	      
	  }
	  



	//	playerUSC2.handle_AIadjust();
	playerUSC.handle_AI(playerND.getOffSetX(),playerND.getOffSetY());
	//	playerUSC2.handle_AI(playerND.getOffSetX(),playerND.getOffSetY());
	tackle = playerUSC.collisioncheck(playerND.getOffSetX(),playerND.getOffSetY(), 120);
	fall = playerUSC.collisioncheck(playerND.getOffSetX(), playerND.getOffSetY(),60);
	
	//	tackle = playerUSC2.collisioncheck(playerND.getOffSetX(),playerND.getOffSetY(), 120);
	// fall = playerUSC2.collisioncheck(playerND.getOffSetX(), playerND.getOffSetY(),60);
	
	//   cout << tackle << endl;
	
	
	
	

	playerND.move();
	playerUSC.move();
      	//playerUSC2.move(); 
	    
	score += 10;
	scoreCount.setScore(score);

	//scoreCount.show(screen, false, false);
	background.show(screen);
	playerND.show(screen, false, fall); // nd will never tackle
	playerUSC.show(screen, tackle, false); // usc will never fall
	//	playerUSC2.show(screen, tackle, false); // usc will never fall
	scoreCount.show(screen, false, false);
		playerUSC.handle_AIadjust();




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
		 Mix_HaltChannel( 1);
		 Mix_HaltChannel(3);
		 if( Mix_PlayChannel( 4, boom, 1 ) == -1 ) 
	  		{ 
	  				return 1; 
	  		} 
	  	 if( Mix_PlayChannel( 5, hit, 0 ) == -1 ) 
	  		{ 
	  				return 1; 
	  		} 
	    start = false;
	    score = 0;
	    tackle = false;
	    fall = false;
	    playerND.setOffSetX(SCREEN_WIDTH/2);
	    playerND.setOffSetY(SCREEN_HEIGHT/2);
			playerUSC.counter = 1;
	    playerUSC.setOffSetX(0);
	    playerUSC.setOffSetY(0);
	    //playerUSC2.setOffSetX(255);
	    //playerUSC2.setOffSetY(0);
		    
	    playerUSC.handle_AIadjust();
	    //    	   playerUSC2.handle_AIadjust();
	    playerND.handle_AIadjust();


	  }



		
    }
    //Clean up
    //Free the sound effects 
    Mix_FreeChunk( practicesound ); 
    Mix_FreeChunk( crowd ); 
    Mix_FreeChunk( boom ); 
    Mix_FreeChunk( crazytrain );
    Mix_FreeMusic( titlemusic );
    Mix_CloseAudio(); 
    
    SDL_Quit();
    
    return 0;
    
    
}
