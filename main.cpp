#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL/SDL.h>
#include "model.hpp"
using namespace std;

int main(int argc, char* argv[]) {
	srand(time(0));
	int n;
	if(argc==1)
		n=100;
	else
		n=atoi(argv[1]);
		
	model test(n); //never try a population size beyond 300!  (TODO) ATM, Algorithm is O(n^2) each timestep!
	do
	{
		test.timestep(50);
	}while(!test.quit());

	return 0;
}
