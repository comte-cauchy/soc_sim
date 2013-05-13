#ifndef MODEL_
#define MODEL_
#include <vector>
#include <string>
#include "SDL/SDL.h"
#include "screen_dimensions.hpp"
#include "agent.hpp"


class model
{
public:
	model(uint popsize=100);
	~model();

	void timestep(uint n=1);
	static bool quit();//true, if user wants to quit (esc, q pressed, or (x) clicked)

private:
	vector<agent> people_;
	static SDL_Surface* screen_;
	static Uint8* keystates_;

	void show_();
	void tick_();
	void update_forces_();
};


#endif //MODEL_
