// Author: Adrian A. Gerbaud H.
// Main/driver program that will put everything together


//The frame rate
const int FRAMES_PER_SECOND = 20;

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Image.h"
#include "Timer.h"
#include"Info.h"

// Global Function
bool init()
{
  //Initialize all SDL subsystems
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
      return false;
    }
  
  
  //If there was an error in setting up the screen
  if( screen == NULL )
    {
      return false;
    }
  
   SDL_WM_SetCaption( "Motion", NULL );
  
  return true;
}





int main( int argc, char* args[] )
{

    bool quit = false;
    Image myImage;
    Timer fps;
    SDL_Event event;


    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( myImage.setImage("semrich.png") == false )
    {
        return 1;
    }

    //While the user hasn't quit
    while( quit == false )
      {
        //Start the frame timer
        fps.start();
	
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
	  {
            //Handle events for the dot
	    myImage.handle_input(event);
	    
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
	      {
                //Quit the program
                quit = true;
	      }
	  }
	
	
        //Move the dot
        myImage.move();
	

        //Fill the screen 
	//background.show();
        SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB( screen->format, 100, 240, 80 ) );
	
        //Show the dot on the screen
	
	// Problem Seems to be beginning here  . Either it is not blitting or it is no updating because of the static screen;      
	myImage.show();
	
        //Update the screen
        if( SDL_Flip(screen ) == -1 )
	  {
            return 1;
	  }
	
        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
	  {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
	  }
      }
    
    //Clean up
    SDL_Quit();
    return 0;
    // Deconstructor is called here for myImage
}
