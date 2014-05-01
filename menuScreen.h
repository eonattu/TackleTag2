// Authors: Jandra Aranguren, Adrian Gerbaud, Edwin Onattu
// This is the header file for our MenuScreen class which will display start and replay screen. Inherits from Sprite.

#include "SDL/SDL.h"
#include "sprite.h"
#include <vector>
#include <string>

#ifndef MENU_H
#define MENU_H

class MenuScreen : public Sprite{
 public:
 	MenuScreen(std::string,int,int,int);  //constructor
  	virtual void move(int,int,int); //virtual function from inheritance
  	virtual void show(SDL_Surface *, bool, bool); //shows either start up screen or replay screen
  	virtual void set_clips(); //sets sprite sheet clip positions
  	virtual int getOffSetX(); //returns x pos
  	virtual int getOffSetY(); //returns y pos
	virtual int collision(int,int,int); //virtual function from inheritance
	virtual int collisioncheck(int,int,int);  // virtual function from inheritance. Will not be needed
	virtual int getwidth();//virtual function from inheritance
  	virtual int getheight();//virtual function from inheritance
  	virtual void free(); //Frees sprite surface
  	
	bool handle_event(SDL_Event &); //detects spacebar press
	void setHasPlayed(bool); //sets hasPlayed variable
	bool getHasPlayed(); //returns hasPlayed variable
 private:
 	bool hasPlayed; //whether game has been started once
	
	//States
	const int TITLE;
	const int REPLAY;
};

#endif
