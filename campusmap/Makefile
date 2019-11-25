CXX = g++
LDLIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

trainer.o: trainer.cpp trainer.hpp
	$(CXX) -c trainer.cpp

npc.o: npc.cpp npc.hpp
	$(CXX) -c npc.cpp

tilemap.o: tilemap.cpp tilemap.hpp
	$(CXX) -c tilemap.cpp
	
map.o: map.cpp map.hpp tilemap.hpp npc.hpp trainer.hpp const.hpp
	$(CXX) -c map.cpp

main.o: main.cpp tilemap.hpp npc.hpp map.hpp trainer.hpp const.hpp
	$(CXX) -c main.cpp
	

game: main.o map.o tilemap.o trainer.o npc.o
	$(CXX) main.o map.o trainer.o tilemap.o npc.o  -o game $(LDLIBS)  


clean:
	rm -f game
	rm -f *.o