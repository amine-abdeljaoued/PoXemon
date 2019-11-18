CXX = g++
LDLIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

trainer.o: trainer.cpp trainer.hpp
	$(CXX) -c trainer.cpp

tilemap.o: tilemap.cpp tilemap.hpp
	$(CXX) -c tilemap.cpp
	
main.o: main.cpp tilemap.hpp trainer.hpp const.hpp
	$(CXX) -c main.cpp

game:  tilemap.o main.o trainer.o 
	$(CXX) main.o  trainer.o tilemap.o  -o game $(LDLIBS)  


clean:
	rm -f game
	rm -f *.o