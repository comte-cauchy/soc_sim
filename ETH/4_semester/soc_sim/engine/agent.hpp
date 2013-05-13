#ifndef AGENT_
#define AGENT_
#include <string>
#include "SDL/SDL.h"
#include "vect2d.hpp"
using namespace std;

class agent
{
public:
	
	//set agent's dynamics:
	void move(const double& x, const double& y);
	void move(const vect2d& to){move(to.x,to.y);};

	void setSpeed(const double& vx,const double& vy);
	void setSpeed(const vect2d& vel){setSpeed(vel.x,vel.y);};

	void setForce(const double& fx,const double& fy);
	void setForce(const vect2d& f){setForce(f.x,f.y);};

	//getter functions
	const vect2d& where() const;
	const vect2d& speed() const;
	const vect2d& getForce() const;

	//model-specific forces
	vect2d socialforce(const agent&);
	vect2d externalForces();
	agent operator()(); //defines initial position&speed of agents

	//graphics
	void paste(SDL_Surface* screen);
	static void setShape(string filename);

private:
	vect2d pos_;
	vect2d vel_;
	vect2d force_;
	static SDL_Surface* shape_;					
};

#endif //AGENT_
