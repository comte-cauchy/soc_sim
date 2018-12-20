COMPILER=c++
FLAGS=-O0 -ggdb

EXE=test

OBJS=globals.o\
	screen_dimensions.o\
	vect2d.o\
	agent.o\
	model.o\
	main.o

all: testrun

testrun: $(OBJS) 
	$(COMPILER) $(FLAGS) -o $(EXE) $(OBJS) -lSDL2
main.o: main.cpp globals.o
	$(COMPILER) $(FLAGS) -c main.cpp -lSDL2
screen_dimensions.o: screen_dimensions.cpp screen_dimensions.hpp
	$(COMPILER) $(FLAGS) -c screen_dimensions.cpp
vect2d.o: vect2d.cpp vect2d.hpp
	$(COMPILER) $(FLAGS) -c vect2d.cpp
agent.o: agent.cpp agent.hpp
	$(COMPILER) $(FLAGS) -c agent.cpp -lSDL2
model.o: model.cpp model.hpp
	$(COMPILER) $(FLAGS) -c model.cpp -lSDL2
globals.o: globals.cpp
	$(COMPILER) $(FLAGS) -c globals.cpp

clean:
	rm -rf *.o *~ $(EXE)



