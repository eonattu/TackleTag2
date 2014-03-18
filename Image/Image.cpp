//Author: Adrian A. Gerbaud H.
//This is the general implementation of an image. It allows for movement using the arrow keys.

#include "Image.h"
#include "Info.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <iostream>
#include <string>

const int velocity = 30;

// Default Constructor

Image::Image()
{

  x = 0;
  y = 0;
  
  xVel = 0;
  yVel = 0;
    
  ImagePtr= NULL;
}

// Deconstructor

Image::~Image()
{
  
  SDL_FreeSurface(ImagePtr);
  
}

void Image::handle_input(SDL_Event event)
{
  
  
  //If a key was pressed
  if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
      switch( event.key.keysym.sym )
        {
	case SDLK_UP: yVel -= velocity; break;
	case SDLK_DOWN: yVel += velocity; break;
	case SDLK_LEFT: xVel -= velocity; break;
	case SDLK_RIGHT: xVel += velocity; break;
        }
    }
  //If a key was released
    else if( event.type == SDL_KEYUP )
      {
        //Adjust the velocity
        switch( event.key.keysym.sym )
	  {
	  case SDLK_UP: yVel += velocity; break;
	  case SDLK_DOWN: yVel -= velocity; break;
	  case SDLK_LEFT: xVel += velocity; break;
	  case SDLK_RIGHT: xVel -= velocity; break;
	  }
      }
}

void Image::move()
{
  x += xVel;
  
  // Check boundary conditions
  if( ( x < 0 ) || ( x > SCREEN_WIDTH ) )
    {
      x -= xVel;
    }  
  
  y += yVel;
  
  // Check boundary conditions
  if( ( y < 0 ) || ( y > SCREEN_HEIGHT ) )
    {
      y -= yVel;
    }
}


void Image::show()
{

 //Holds offsets
  SDL_Rect offset;
  
  //Get offsets
  offset.x = x;
  offset.y = y;
  
  SDL_BlitSurface( ImagePtr, NULL, screen, &offset );
  
}


SDL_Surface* Image::getImage(void)
{
  return ImagePtr;
}


bool Image::setImage(std::string s)
{
  
  SDL_Surface* loadedImage = NULL;
  SDL_Surface* optimizedImage = NULL;
  
  //Load
  loadedImage = IMG_Load( s.c_str() );
  
  if( loadedImage != NULL )
    {
      //Optimize for better performance
        optimizedImage = SDL_DisplayFormat( loadedImage );
    
        SDL_FreeSurface( loadedImage );
	
	if( optimizedImage != NULL )
	  {
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0xFF, 0xFF, 0xFF ) );
	  }
	else return false;
	
    }
  else return false;
  
  // Set ImagePtr the optimized Image
  ImagePtr = optimizedImage;
  //std::cout << "REACHED HERE" << std::endl;
  return true;

}
