#include "SDL/SDL.h"
#include "sprite.h"
#include <vector>
#include <string>

#ifndef PLAYER_H
#define PLAYER_H

class player : public Sprite {
 public:
  player(std::string,int,int,int);
  virtual void move();
  virtual void show(SDL_Surface *);
  virtual void set_clips(); //sets sprite sheet position clips
  virtual int getOffSetX(); //returns x position coordinate
  virtual int getOffSetY(); //returns y position coordinate 
  virtual int collision(); //handles collision
  void handle_events(SDL_Event &);
  bool check_collision(Sprite *); //checks for collision between otter and an obstacle
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
  
};

#endif
  
