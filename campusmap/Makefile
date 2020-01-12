CXX = g++
LDLIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
ALLh = fights/Pokemon.h Pokeball.h Bullet.h Fight.h Health.h Artillery.h StateFunctions.h Backpack.h Opponent.h Bullet_bar.h Collision.h Special_Attacks_bar.h Pokemon_Button.h

trainer.o: trainer.cpp trainer.hpp
	$(CXX) -c  trainer.cpp

npc.o: npc.cpp npc.hpp
	$(CXX) -c  npc.cpp

tilemap.o: tilemap.cpp tilemap.hpp
	$(CXX) -c  tilemap.cpp
	
interior.o: interior.cpp interior.hpp
	$(CXX) -c  interior.cpp
	
map.o: map.cpp map.hpp tilemap.hpp npc.hpp trainer.hpp const.hpp interior.hpp
	$(CXX) -c  map.cpp 

intro.o: intro.cpp intro.hpp
	$(CXX) -c  intro.cpp


shop.o: shop.cpp shop.hpp
	$(CXX) -c  shop.cpp

box.o: box.cpp box.hpp
	$(CXX) -c  box.cpp
	
Backpack_map.o: Backpack_map.cpp Backpack_map.hpp
	$(CXX) -c  Backpack_map.cpp
	
center.o: center.cpp center.hpp
	$(CXX) -c  center.cpp

HEADERS_FIGHTS := $(wildcard fights/*.h)
SOURCES_FIGHTS_TMP := $(wildcard fights/*.cpp)
SOURCES_FIGHTS := $(filter-out fights/main.cpp, $(SOURCES_FIGHTS_TMP))
OBJECTS_FIGHTS := $(patsubst %.cpp,%.o,$(SOURCES_FIGHTS))
fights: $(OBJECTS_FIGHTS)
	make -C fights



main.o: main.cpp tilemap.hpp npc.hpp map.hpp trainer.hpp const.hpp intro.hpp shop.hpp interior.hpp center.hpp box.hpp Backpack_map.hpp $(HEADERS_FIGHTS)
	$(CXX) -c  main.cpp
	

game: fights main.o map.o tilemap.o trainer.o npc.o  intro.o  shop.o interior.o center.o Backpack_map.o box.o
	echo $(SOURCES_FIGHTS)
	$(CXX) main.o map.o trainer.o tilemap.o npc.o  intro.o shop.o interior.o center.o Backpack_map.o box.o $(OBJECTS_FIGHTS) -o game $(LDLIBS)  


clean:
	rm -f game
	rm -f *.o
