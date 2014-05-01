//Authors: Adrian Gerbaud, Jandra Aranguren, Edwin Onattu
// Puts it all together

#include "background.h"
#include "obstacle.h"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "Global.h"
#include "Timer.h"
#include "player.h"
#include "sprite.h"
#include "scoreCounter.h"
#include "menuScreen.h"
#include "coin.h"
#include <ctime>
#include <cstdlib>
#include<iostream> //used for cout and debugging


int main(int argc, char* args[])
{
  srand (time(NULL));// seed random number generator 
  
  //Initialize SDL. See Global.h for details of initialized elements.
  if(init() == false){

    return 1;
  }

/*-----------------------------AUDIO-----------------------------*/

//Initialize SDL_mixer
if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
	{
		return 1;
	}
	  
//Initialize Music to be played
Mix_Music *titlemusic = NULL;

//Initialize Sound Effects to be played
Mix_Chunk *practicesound = NULL;
Mix_Chunk *crowd = NULL;
Mix_Chunk *crazytrain = NULL;
Mix_Chunk *boom = NULL;
Mix_Chunk *hit = NULL;
Mix_Chunk *coin = NULL;

  //Initializing Quit flags
  bool quit = false;
  bool start = false;

//Loading the music
	titlemusic = Mix_LoadMUS("Title1.wav");
	practicesound = Mix_LoadWAV("practice1.wav");
	crowd = Mix_LoadWAV("crowd1.wav");
	crazytrain = Mix_LoadWAV("crazytrain1.wav");
	boom = Mix_LoadWAV("boom.wav");
	hit = Mix_LoadWAV("hit1.wav");
	coin = Mix_LoadWAV("coin.wav");
	
	//If there was a problem loading the sound effects
	if( ( practicesound == NULL ) || ( crazytrain == NULL )||( crowd == NULL ) || (boom==NULL)|| (hit==NULL) || (coin==NULL)) 
	{ 
	return 1; 
	} 
	
// If there was a problem loading the music
	if (titlemusic == NULL)
	{
		return 1;
	}
	
/* ------------------------Initialize Variables--------------------- */	

vector<Sprite*> obstacles; // This will hold coins and cones. Can easily be expanded to hold other objects (i.e cones, powerups, etc...)

  // Player
  player playerND("ND_Player.bmp", 255, 255, 255, 0, SCREEN_HEIGHT-120);
  player playerUSC("USC_Player.bmp", 255, 255, 255,0 ,0);
  
  //The frame rate regulator(timer)
  Timer fps;
  
  //The background
  Background background("Field.bmp",screen);
  background.show(screen);
  
  //Menu
  MenuScreen menu("Welcome.bmp", 255,255,0);
  
  //ScoreCounter
  scoreCounter scoreCount("ND_Player.bmp",0,255,0);
  int score = 0;
  int soundCounter = 0;
 
  //AI counter
  playerUSC.counter = 1;  
  //Player Tackling and down bools
  bool tackle = false;
  bool fall = false;
 

  /*--------------------Begin Game------------------*/  

    // Start of game
      
  while(quit == false)
    {
		while(start == false)
	  		{
	       //If the user has Xed out the window
	  		 if(event.type == SDL_QUIT)
	     	 {
	     	 //Cleans up surfaces				
			 menu.free();
			 playerND.free();
			 playerUSC.free();
			 scoreCount.free();
			 background.free();
			 //Frees the sound effects and music 
			 Mix_FreeChunk( practicesound ); 
			 Mix_FreeChunk( crowd ); 
			 Mix_FreeChunk( boom ); 
			 Mix_FreeChunk( crazytrain );
			 Mix_FreeChunk( coin );
			 Mix_FreeMusic( titlemusic );
			 Mix_CloseAudio(); 
			 
			 SDL_Quit();
	     	 
			 //Quit the program
		    return 1;
	     	 }
	
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
	   
	   
	   Timer mps; // Caps frame rate
	   mps.start();
	   scoreCount.setTitle(false);
	     
	   while(SDL_PollEvent(&event))
	      {
	  		
			start=menu.handle_event(event);//Checks if space pressed to start actual game
				if(event.type == SDL_KEYDOWN){
			   	switch(event.key.keysym.sym){
			      	case SDLK_s: // Pressing S allows to pause or play
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
	    
	    menu.show(screen,false, false); //show menu
	    SDL_Flip(screen); //update screen
	   
	    // cap frame rate
	    if (mps.get_ticks() < 1000/ FRAMES_PER_SECOND)
	      {      
				SDL_Delay( ( 1000/FRAMES_PER_SECOND) - mps.get_ticks() );
	      }
	    
	    if(score > 0) // if the score is > 0, set it to zero and make players visible.
	      {
				score = 0;		
				playerND.setIsVisible(true);
				playerUSC.setIsVisible(true);
	      }
	    playerND.setStarting(true);
	    playerUSC.setStarting(true);
	    
	  }
	
	// BEGIN GAME
		
	Mix_HaltMusic();

	scoreCount.setTitle(true);
	menu.setHasPlayed(true);
	fps.start();
	
	//If score is '10' ie. game just started 
	  if( score == 0 )
	   { 
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
	  
	playerUSC.counter++; //AI counter used for velocity. It doesn't wait for anybody
	
	//While there's events to handle
   while(SDL_PollEvent(&event))
		  {

	    	playerND.handle_events(event);
			        
			 //If the user has Xed out the window
	  		 if(event.type == SDL_QUIT)
	     	 {
				//Quit the program
				quit = true;
	     	 }
	      
	  }
	  
	  // -------------Cone Spawning---------------
	  
	  if (score==0) 
		
	  	{//Spawns when score==1 to signify start of new game
			if (score==0) score =100;
				for (int j=3; j<=14;j++)
				{		
				 obstacle* cone = new obstacle("cone.bmp",255,255,255, rand()%(SCREEN_WIDTH-400)+200, j*40);//create cone in heap

			   obstacles.push_back(cone); // place it in vector
				}
		}
	  
	  // -------------Coin Spawning---------------
	  
	  	int spawnCoin = rand()%1000 + 1;
		if(spawnCoin < 150) // spawn coins (150/1000 of the time)
			{
				int randX= rand()%900 + 100;
				int randY= rand()%640 + 100;

				Coin* money = new Coin("coins.bmp", 48,120,128, randX, randY);  //create coin in heap
				obstacles.push_back(money);// place it in vector

			}	
		
   // Activate USC Player (AI)
	// AI takes player's offset to decide next move direction.		
	playerUSC.handle_AI(playerND.getOffSetX(),playerND.getOffSetY());
	
	//Forces a tackle
	tackle = playerUSC.collisioncheck(playerND.getOffSetX()+(playerND.getwidth()/2),playerND.getOffSetY()+(playerND.getheight()/2), 90);
	 //Ends current game because player is down
	fall = playerUSC.collisioncheck(playerND.getOffSetX()+(playerND.getwidth()/2), playerND.getOffSetY()+(playerND.getheight()/2),60);
	
	//Moves the players based on their offsets, unless attempting to move outside bounds
	playerND.move(0,0,0);
	playerUSC.move(0,0,0);
				
	// Collisions checks for Players and obstacles (cones and coins) 	
		for(int i=0; i<obstacles.size(); i++)
		{ 
			// collide(player) and collideUSC(AI) variables correspond to closeness to obstacle to have a collision
			int collide = playerND.collisioncheck(obstacles.at(i)->getOffSetX()+(obstacles.at(i)->getwidth())/2, obstacles.at(i)->getOffSetY()+(obstacles.at(i)->getheight())/2, 40);
			int collideUSC = playerUSC.collisioncheck(obstacles.at(i)->getOffSetX()+(obstacles.at(i)->getwidth())/2, obstacles.at(i)->getOffSetY()+(obstacles.at(i)->getheight())/2, 40);
			
			
			if(collide == 1 || collideUSC ==1) // Close enough to collide
			{
				// scoreupND tries to differentiate betweeen type of collision ie. with a coin or with a cone. Return 2 for coin, and 1 for cone collision		
				int scoreupND=0;
				if (collide) scoreupND=obstacles.at(i)->collision(playerND.getOffSetX(),playerND.getOffSetY(),1);
				int scoreupUSC=obstacles.at(i)->collision(playerUSC.getOffSetX(),playerUSC.getOffSetY(),2);
				
				if (scoreupND ==2) // User Player hit coin 
				{
					score = score + 10; //Adds 100 to score
					Mix_PlayChannel(7,coin,0); //Plays coin clink sound
					collide = 0;
				
				}
				else if (scoreupND==1 || scoreupUSC==1) //User or AI hit cone
				{
					// AI's collision based movement function for cones. Attempts movement around.
					if (collideUSC) playerUSC.move(obstacles.at(i)->getOffSetX(),obstacles.at(i)->getOffSetY(),3);
					// User's collision based handling function for cones. Treats cones like walls. 
					else (playerND.move(obstacles.at(i)->getOffSetX(),obstacles.at(i)->getOffSetY(),1));
				}
			}


		}

	    
	score += 0; // Rate of score increasing and setting.
	scoreCount.setScore(score);

	// Call show Functions
	
	background.show(screen);

	playerND.show(screen, false, fall); // nd will never tackle
	playerUSC.show(screen, tackle, false); // usc will never fall
	
	//cone.show(screen, tackle,fall);
	//	playerUSC2.show(screen, tackle, false); // usc will never fall
	
	scoreCount.show(screen, false, false);
	
	// Shows all obstacles
	
	for(int i = 0; i<obstacles.size(); i++)
	{
		obstacles.at(i)->show(screen, false, false);
	}
	
	//Adjusts AI Velocity
	playerUSC.handle_AIadjust();




	//Update the screen
   SDL_Flip(screen);
   
	//Cap the frame rate
     if(fps.get_ticks() < 1000 / FRAMES_PER_SECOND)
	  {
	    SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
	  }
	  
	// free obstacles if they have been collided with
	for(int i =0; i < obstacles.size(); i++)
		{
			if (obstacles.at(i)->getHasCollided())
			{	
				obstacles.at(i)->free();
				delete obstacles.at(i);
				obstacles.erase(obstacles.begin()+i);
				i--;
			}

		}
    
	
	if(fall == true)
	  {
	  
	  // Reset values for replaying game
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
	    playerND.setOffSetY(SCREEN_HEIGHT-(playerND.getheight()));
	    
		 playerUSC.counter = 1;
	    playerUSC.setOffSetX(0);
	    playerUSC.setOffSetY(0);

		    
	    playerUSC.handle_AIadjust();

	    playerND.handle_AIadjust();

			// Clears vector
			for(int j=0; j<obstacles.size(); j++)
				{ //deletes all obstacles
					obstacles.at(j)->free();
					delete obstacles.at(j);
					obstacles.erase(obstacles.begin()+j);
					j--;


				}   
			
	  }

    }
    
    
    return 0;
    
    
}
