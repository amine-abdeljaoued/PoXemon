CXX = g++
LDLIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system


tilemap.o: tilemap.cpp tilemap.hpp
	$(CXX) -c tilemap.cpp

main.o: main.cpp tilemap.hpp
	$(CXX) -c main.cpp

game: tilemap.o main.o 
	$(CXX) main.o tilemap.o -o game $(LDLIBS)


clean:
	rm -f game
	rm -f *.o