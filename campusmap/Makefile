CXX = g++
LDLIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

trainer.o: trainer.cpp trainer.hpp
	$(CXX) -c  trainer.cpp

npc.o: npc.cpp npc.hpp
	$(CXX) -c  npc.cpp

tilemap.o: tilemap.cpp tilemap.hpp
	$(CXX) -c  tilemap.cpp
	
map.o: map.cpp map.hpp tilemap.hpp npc.hpp trainer.hpp const.hpp
	$(CXX) -c  map.cpp

intro.o: intro.cpp intro.hpp
	$(CXX) -c  intro.cpp

Backpack_content.o: Backpack_content.cpp Backpack_content.h
	$(CXX) -c  Backpack_content.cpp

Button.o: Button.cpp Button.h
	$(CXX) -c  Button.cpp

test.o: test.cpp test.h
	$(CXX) -c  test.cpp

openbackpack.o: openbackpack.cpp openbackpack.hpp
	$(CXX) -c  openbackpack.cpp

Background.o: Background.cpp Background.h
	$(CXX) -c  Background.cpp

shop.o: shop.cpp shop.hpp
	$(CXX) -c  shop.cpp

main.o: main.cpp tilemap.hpp npc.hpp map.hpp trainer.hpp const.hpp intro.hpp Backpack_content.h Button.h test.h openbackpack.hpp Background.h shop.hpp
	$(CXX) -c  main.cpp
	

game: main.o map.o tilemap.o trainer.o npc.o test.o Button.o Backpack_content.o intro.o openbackpack.o Background.o shop.o
	$(CXX) main.o map.o trainer.o tilemap.o npc.o test.o Button.o Backpack_content.o intro.o openbackpack.o Background.o shop.o -o game $(LDLIBS)  


clean:
	rm -f game
	rm -f *.o