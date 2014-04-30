#include "SDL/SDL.h"
#include "sprite.h"
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>

#ifndef OBSTACLE_H
#define OBSTACLE_H

class obstacle : public Sprite {
 public:
  obstacle(std::string,int,int,int,int,int);
  virtual void move(int,int,int);
  virtual void show(SDL_Surface *,bool,bool); // Shows obstacle
  virtual void set_clips(); //sets sprite sheet position clips
  virtual int getOffSetX(); //returns x position coordinate
  virtual int getOffSetY(); //returns y position coordinate 
  virtual int collision(int,int,int); //handles collision
  virtual int collisioncheck(int,int,int);
  virtual int getwidth();
  virtual int getheight();
  virtual void free();
  void setOffSetY(int); 
  void setOffSetX(int);
    void setStarting(bool); 
    void setIsVisible(bool); 



 protected:
   bool isVisible; //obstacle shown on screen
     bool isStarting; //very start of game

};

#endif
  
