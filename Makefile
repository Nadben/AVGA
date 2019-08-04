
#we list all the output objects
objects = RaceGame.o car.o track.o sensor.o mySTL.o
args = -std=c++11 -g -c 


#my application
myRaceGame: $(objects) 
	g++ $(objects) -o myRaceGame -lsfml-graphics -lsfml-window -lsfml-system


#my output files and their depedencies
RaceGame.o: RaceGame.cpp RaceGame.h track.h
	g++ $(args) RaceGame.cpp 

car.o: car.cpp car.h sensor.h
	g++ $(args) car.cpp

track.o: track.cpp track.h car.h mySTL.h
	g++ $(args) track.cpp

sensor.o: sensor.cpp sensor.h
	g++ $(args) sensor.cpp

mySTL.o: mySTL.cpp mySTL.h
	g++ $(args) mySTL.cpp


clean: 
	rm -f $(objects) 





