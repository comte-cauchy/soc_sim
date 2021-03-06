#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "SDL2/SDL.h"
#include "screen_dimensions.hpp"
#include "model.hpp"
#include "agent.hpp"
#include "vect2d.hpp"

using namespace std;

SDL_Surface* model::screen_=NULL;
SDL_Window* model::window_=NULL;
SDL_Renderer* model::renderer_=NULL;
const Uint8* model::keystates_=NULL;

model::model(uint popsize):
people_(popsize)
{	
	//srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	//screen_=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32,SCREEN_MODE);
	//SDL2
	window_ = SDL_CreateWindow("soc_sim",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,SCREEN_HEIGHT,
		SCREEN_MODE);
	screen_ = SDL_GetWindowSurface(window_);
	//renderer_ = SDL_CreateRenderer(window_,-1,SDL_RENDERER_ACCELERATED);
	renderer_ = SDL_CreateRenderer(window_,-1,SDL_RENDERER_SOFTWARE);
	generate_n(people_.begin(),popsize,agent());
	keystates_ = SDL_GetKeyboardState( NULL );
	agent::setShape("dot.bmp");
}

model::~model()
{
	SDL_Quit();
}

void model::timestep(uint n)
{
	for(uint i=0;i<n;++i)
		tick_();
	show_();
}

void model::tick_()
{

	float dt=0.00001;//0.00001 is FUCKING small. set for slowing down the whole thing! TODO: real time adjustment
	
	update_forces_();
	
	for (vector<agent>::iterator i=people_.begin();i!=people_.end();++i)
	{
		i->setSpeed(i->speed()+i->getForce()*dt);
		i->move(i->where()+i->speed()*dt);
	};
};

void model::show_()
{	
	//Fill background white
	SDL_FillRect( screen_,
			&screen_->clip_rect,
			SDL_MapRGB( screen_->format, 0xFF, 0xFF, 0xFF ));
	//blit dots
	for(vector<agent>::iterator dots=people_.begin();dots!=people_.end();++dots)
	{
		dots->paste(screen_);
	}
	
	//print entire Picture
	SDL_RenderPresent(renderer_);
}

void model::update_forces_()
{
	for(vector<agent>::iterator i=people_.begin();i!=people_.end();++i)
	{
		vect2d zero;
		i->setForce(zero);
		for(vector<agent>::iterator j=people_.begin();j!=people_.end();++j)
		{
			i->setForce(i->getForce()+(*i).socialforce(*j));
		}
		i->setForce(i->getForce()+i->externalForces());
	}

}

bool model::quit()
{
	//TODO: find solution, s.t. keypresses are queued and not only evaluated upon call of quit() (this way keypresses might be missed!)
	SDL_PumpEvents();
	if(keystates_[SDL_SCANCODE_Q]||keystates_[SDL_SCANCODE_ESCAPE])
		return true;
	
	SDL_Event event;
	while (SDL_PollEvent(&event))
		if(event.type==SDL_QUIT)
			return true;
	return false;
}
