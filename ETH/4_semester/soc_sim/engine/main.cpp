#include <iostream>
#include <SDL/SDL.h>
#include "model.hpp"
using namespace std;

int main()
{
	model test(300);//never try a population size beyond 300!  (TODO) ATM, Algorithm is O(n^2) each timestep!
	do
	{
		test.timestep(50);
	}while(!test.quit());

	return 0;
}
