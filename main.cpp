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

#include<iostream>


int main(int argc, char* args[]){


// Music to be played
Mix_Music *titlemusic = NULL;
// Sound Effects to be played
Mix_Chunk *practicesound = NULL;
Mix_Chunk *crowd = NULL;
Mix_Chunk *crazytrain = NULL;
Mix_Chunk *boom = NULL;
Mix_Chunk *hit = NULL;
Mix_Chunk *coin = NULL;


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
	
	

  player playerND("ND_Player.bmp", 255, 255, 255, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
  player playerUSC("USC_Player.bmp", 255, 255, 255,0 ,0);
  //obstacle cone("cone.bmp",255,255,255,(rand()%SCREEN_WIDTH),(rand()%SCREEN_HEIGHT));
  // player playerUSC2("player1.bmp", 255, 255, 255,255 ,0);
  bool tackle = false;
  bool fall = false;
 
  //The frame rate regulator
  Timer fps;
  
  //The background
  Background background("Field.bmp",screen);
  background.show(screen);

  MenuScreen menu("Welcome.bmp", 255,255,0);
    
    playerUSC.counter = 1;
    //     playerUSC2.counter = 1;
    scoreCounter scoreCount("ND_Player.bmp",255,255,255);
    int score = 0;
    int soundCounter = 0;
    
        vector<Sprite*> obstacles; // This will hold coins

    // Start game
      
    while(quit == false)
      {

     
	while(start == false)
	  {
	         //If the user has Xed out the window
	  		 if(event.type == SDL_QUIT)
	     	 {
	     	 //Clean up
			 //Free the sound effects 
			 menu.free();
			 playerND.free();
			 playerUSC.free();
			 scoreCount.free();
			 background.free();
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
		//cone.setIsVisible(true);
		//				playerUSC2.setIsVisible(true);
		
	      }
	    playerND.setStarting(true);
	    playerUSC.setStarting(true);
	    //cone.setStarting(true);
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
	  
	  if (score==1 ) {
			
				for (int j=3; j<=14;j++)
				{

					//for ( int k=2; k<=12;k++)
					//{
						//if (j%5==0 && k%2==0)
						//{
						//cout << "\nJis,Kis:"<<j<<","<<k;
						
						obstacle* cone = new obstacle("cone.bmp",255,255,255, rand()%(SCREEN_WIDTH-400)+200, j*40);

						obstacles.push_back(cone);
						//cout << "\nsize is: "<<obstacles.size();
						//}
					//}
				}

			//cout << "here1asdfasdfasdfasdfasdfasdfasdfasdfasdf\n" << endl;
		}
	  
	  	int spawnCoin = rand()%1000 + 1;
		if(spawnCoin < 150)
			{
				int randX= rand()%1000 + 100;
				int randY= rand()%700 + 100;

				Coin* money = new Coin("coins.bmp", 48,120,128, randX, randY);
				obstacles.push_back(money);


			//cout << "here1asdfasdfasdfasdfasdfasdfasdfasdfasdf\n" << endl;
		}	
		

			






	//	playerUSC2.handle_AIadjust();
	playerUSC.handle_AI(playerND.getOffSetX(),playerND.getOffSetY());
	//	playerUSC2.handle_AI(playerND.getOffSetX(),playerND.getOffSetY());
	tackle = playerUSC.collisioncheck(playerND.getOffSetX()+(playerND.getwidth()/2),playerND.getOffSetY()+(playerND.getheight()/2), 90);
	fall = playerUSC.collisioncheck(playerND.getOffSetX()+(playerND.getwidth()/2), playerND.getOffSetY()+(playerND.getheight()/2),60);
	
	//	tackle = playerUSC2.collisioncheck(playerND.getOffSetX(),playerND.getOffSetY(), 120);
	// fall = playerUSC2.collisioncheck(playerND.getOffSetX(), playerND.getOffSetY(),60);
	
	//   cout << tackle << endl;
	
	
	
	

				playerND.move(0,0,0);
				playerUSC.move(0,0,0);
				
				
		for(int i=0; i<obstacles.size(); i++)
		{ 
		int collide = playerND.collisioncheck(obstacles.at(i)->getOffSetX()+(obstacles.at(i)->getwidth())/2, obstacles.at(i)->getOffSetY()+(obstacles.at(i)->getheight())/2, 40);
		int collideUSC = playerUSC.collisioncheck(obstacles.at(i)->getOffSetX()+(obstacles.at(i)->getwidth())/2, obstacles.at(i)->getOffSetY()+(obstacles.at(i)->getheight())/2, 40);
			if(collide == 1 || collideUSC ==1)

			{
				int scoreupND=obstacles.at(i)->collision(playerND.getOffSetX(),playerND.getOffSetY(),1);
				int scoreupUSC=obstacles.at(i)->collision(playerUSC.getOffSetX(),playerUSC.getOffSetY(),2);
				
				if (scoreupND ==2)
				{
				score = score + 100;
				Mix_PlayChannel(7,coin,0);
				collide = 0;
				
				}
				else if (scoreupND==1 || scoreupUSC==1) 
				{
				//cout << "apples";
				
				if (collideUSC) playerUSC.move(obstacles.at(i)->getOffSetX(),obstacles.at(i)->getOffSetY(),3);
				else (playerND.move(obstacles.at(i)->getOffSetX(),obstacles.at(i)->getOffSetY(),1));
				}
			}


		}
      	//playerUSC2.move(); 
	    
	score += 1;
	scoreCount.setScore(score);

	//scoreCount.show(screen, false, false);
	background.show(screen);

		
	playerND.show(screen, false, fall); // nd will never tackle
	playerUSC.show(screen, tackle, false); // usc will never fall
	//cone.show(screen, tackle,fall);
	//	playerUSC2.show(screen, tackle, false); // usc will never fall
	scoreCount.show(screen, false, false);
		for(int i = 0; i<obstacles.size(); i++)
		{
			obstacles.at(i)->show(screen, false, false);
		}
	playerUSC.handle_AIadjust();




	//Update the screen
   SDL_Flip(screen);
	//SDL_Flip(playerND.sprite);	

	
	//Cap the frame rate
     if(fps.get_ticks() < 1000 / FRAMES_PER_SECOND)
	  {
	    SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
	  }
	// free obstacles
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
					//cout <<"\nsize is after coins removed: "<< obstacles.size();
       
	
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
	    playerND.setOffSetY(SCREEN_HEIGHT-140);
	    //cone.setOffSetX(rand()%SCREEN_WIDTH);
	    //cone.setOffSetY(rand()%SCREEN_HEIGHT);
		 playerUSC.counter = 1;
	    playerUSC.setOffSetX(0);
	    playerUSC.setOffSetY(0);
	    //playerUSC2.setOffSetX(255);
	    //playerUSC2.setOffSetY(0);
		    
	    playerUSC.handle_AIadjust();
	    //    	   playerUSC2.handle_AIadjust();
	    playerND.handle_AIadjust();
			//cout <<"\nsize is after: "<< obstacles.size();
			for(int j=0; j<obstacles.size(); j++)
				{ //deletes all obstacles
					obstacles.at(j)->free();
					delete obstacles.at(j);
					obstacles.erase(obstacles.begin()+j);
					j--;


				}   
			
	          //vector<Sprite*> obstacles; // This will hold coins
	  }



		
    }
    
    
    return 0;
    
    
}
