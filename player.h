//Authors: Jandra Aranguren, Edwin Onattu, Adrian Gerbaud
// THis is the header file for player class. Inherits from Sprite.

#include "SDL/SDL.h"
#include "sprite.h"
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>

#ifndef PLAYER_H
#define PLAYER_H

class player : public Sprite {
 public:
  player(std::string,int,int,int, int, int); // Constructor. Last two are x and y pos
  virtual void move(int,int,int);// will move the player around the screen depending on arrow keys
  virtual void show(SDL_Surface *, bool, bool); // Put it up to display
  virtual void set_clips(); //sets sprite sheet position clips
  virtual int getOffSetX(); //returns x pos
  virtual int getOffSetY(); //returns y pos
  virtual int collision(int,int,int); //handles collisions
  virtual int collisioncheck(int,int,int); //checks for collision between player and an obstacle
  virtual int getwidth(); //gets player width
  virtual int getheight();// gets player  height
  virtual void free(); //frees sprite surface
  
  void handle_events(SDL_Event &); //handles the arrow keys
  void handle_AI(int,int); //artificial intelligence movement function
  void handle_AIadjust(); //AI velocity adjust "Like user lifting key up"
  
  int counter;
  
  // Useful set and get function to manipulate the private data members
  void setIsVisible(bool); 
  int getStatus();
  void setOffSetY(int); 
  void setOffSetX(int);
  void setStarting(bool); 

  void setStatus(int);
  void setFrame(int);
  


protected:
  bool isVisible; //Player shown on screen
  bool isStarting; //very start of game
  bool isDead; 
  
  //states
  const int SPRITE_DOWN;
  const int SPRITE_UP;
  const int SPRITE_RIGHT;
  const int SPRITE_LEFT;

  const int TDown;
  const int TUp;
  const int TLeft;
  const int TRight;


  
};

#endif
  
