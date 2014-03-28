//Authors: Adrian A. Gerbaud H., Edwin Onattu, Alejandra Aranguren
// This is the header file for the Background class, which handles our field background.

#include "SDL/SDL.h"
using namespace std;

class Background
{
  
 public: 
  Background(const char *, SDL_Surface *); //takes name of background image
  void show(SDL_Surface *);
 private:
  
  SDL_Surface *picture;
};
