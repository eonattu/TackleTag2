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
  player(std::string,int,int,int, int, int); // last two are x and y pos
  virtual void move();
  virtual void show(SDL_Surface *); // CHANGE HERE
  virtual void set_clips(); //sets sprite sheet position clips
  virtual int getOffSetX(); //returns x position coordinate
  virtual int getOffSetY(); //returns y position coordinate 
  virtual int collision(); //handles collision
  void handle_events(SDL_Event &);
  void handle_AI(int,int);
  void handle_AIadjust();
	int counter;
  int collisioncheck(int,int); //checks for collision between player and an obstacle
  void setIsVisible(bool); 
  int getStatus();
  void setOffSetY(int); 
  void setStarting(bool); 
  void setDead(bool); 

protected:
  bool isVisible; //otter shown on screen
  bool isStarting; //very start of game
  bool isDead; //whether otter has died
  
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
  
