#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include "SDL2/SDL.h"
#include "screen_dimensions.hpp"
#include "agent.hpp"
#include "vect2d.hpp"
using namespace std;


//the shape is initialized with the model
	SDL_Surface* agent::shape_=NULL;

//set agent's dynamics:

	void agent::move(const double& x, const double& y )
	{
		pos_.x=x;
		pos_.y=y;
	}

	void agent::setSpeed(const double& vx, const double& vy)
	{
		vel_.x=vx;
		vel_.y=vy;
	}

	void agent::setForce(const double& fx, const double& fy)
	{
		force_.x=fx;
		force_.y=fy;
	};

//getter functions

	const vect2d& agent::where() const
	{
		return pos_;
	}

	const vect2d& agent::speed() const
	{
		return vel_;
	}

	const vect2d& agent::getForce() const
	{
		return force_;
	};

//model-specific forces: TODO find better implementation in model-header

	vect2d agent::socialforce(const agent& other)
	{

		if(other.pos_==pos_)
		{
			vect2d zero;
			return zero;
		}else{
			vect2d ab=other.pos_-pos_;
			double r=sqrt(pow(ab.x,2)+pow(ab.y,2));
			ab=ab*(1/r)*(50*(r-200));
			return ab;
		}
	}

	vect2d agent::externalForces()
	{

		double pi=2*acos(0);
		vect2d redpos;
		redpos.x=pos_.x/SCREEN_WIDTH;
		redpos.y=pos_.y/SCREEN_HEIGHT;
		vect2d force;
		force.x=(8*pi*cos(pi*redpos.x))/((3*sin(pi*redpos.x))-(sin(3*pi*redpos.x)));
		force.y=(8*pi*cos(pi*redpos.y))/((3*sin(pi*redpos.y))-(sin(3*pi*redpos.y)));
		//vect2d zero;
		return force;
	}

	agent agent::operator()()
	{
		vect2d zero;
		move(rand()%SCREEN_WIDTH,rand()%SCREEN_HEIGHT);
		setSpeed(zero/*(rand()%11-5)*100,(rand()%11-5)*100*/);
		setForce(zero);
		return *this;
	}

//graphics

	void agent::paste(SDL_Surface* screen)
	{
		SDL_Rect sdlpos;
		sdlpos.x=pos_.x-(shape_->w/2);
		sdlpos.y=pos_.y-(shape_->h/2);
		SDL_BlitSurface(shape_,NULL,screen,&sdlpos);
	}

	void agent::setShape(string filename)
	{
		shape_ = SDL_LoadBMP(filename.c_str());
		//shape_ = SDL_DisplayFormat(shape_);
		SDL_SetColorKey(shape_,
				true,
				SDL_MapRGB(shape_->format, 0xFF, 0xFF, 0xFF)
				);
	}
