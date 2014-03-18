//Author: Adrian A. Gerbaud H.
//This is a image test class that will hold the information for an image to around the screen.

#include<string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class Image
{

 public:
  
  Image();
  ~Image();  // Deconstructor is necessary to avoid memory leaks
  
  void handle_input(SDL_Event);
  
  
  void move();
  
  void show();
    
  bool setImage(std::string s); // Will make the surface point point to the image
  
  SDL_Surface* getImage(void);
    
 private:
  
  int x, y; // Position
  
  int xVel, yVel; // Velocity

  SDL_Surface* ImagePtr; // Pointer to the image 

  
};    
