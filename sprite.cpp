//Author: Adrian A. Gerbaud H., Alejandra Aranguren, Edwin Onattu
//This is the implemenation file for the Sprite class which is the abstract base class upon which most other classes are inherited

#include "sprite.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

Sprite::Sprite(int count):states(count,vector<SDL_Rect>(15)), SCREEN_WIDTH(960),SCREEN_HEIGHT(576), SCREEN_BPP(32), FRAMES_PER_SECOND(10), SPRITE_DOWN(0), SPRITE_UP(1), SPRITE_RIGHT(2), SPRITE_LEFT(3){} //constructor

bool Sprite::getHasCollided(){return hasCollided;} //returns variable tracking whether object has collided

void Sprite::apply_surface(SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip){ //applies new surface
    //Holds offsets
    SDL_Rect shift;

    //Get offsets
    shift.x = offSetX;
    shift.y = offSetY;

    //Blit
    SDL_BlitSurface(source, NULL, destination, &shift);

}

SDL_Surface * Sprite::load_image(std::string filename, int r, int g, int b)
{
  SDL_Surface* loadedImage = NULL;
  SDL_Surface* optimizedImage = NULL;
  
  //Load
  loadedImage = SDL_LoadBMP( filename.c_str() );
  
    if( loadedImage != NULL )
      {
	//Optimize for better performance
        //optimizedImage = SDL_DisplayFormat( loadedImage );
	
	//SDL_FreeSurface( loadedImage );
	
	//if( optimizedImage != NULL )
	  //{
	// SDL_SetColorKey( loadedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, r, g, b ) );
	    // }
	
	
      }
    //return optimizedImage;
    return loadedImage;
}

  /*
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = SDL_LoadBMP(filename.c_str());
    
    //If the image loaded
   if(loadedImage != NULL){
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat(loadedImage);

        //Free the old surface
        SDL_FreeSurface(loadedImage);
	
        //If the surface was optimized
	if(optimizedImage != NULL)
	  {
            //Color key surface
	    int colorkey = SDL_MapRGB(optimizedImage->format, r, g, b);
	    SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	  }
	
   }
*/
    //Return the optimized surface
  // return optimizedImage;
    

