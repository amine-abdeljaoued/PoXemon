CXX = g++
LDLIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

pokeball.o: Pokeball.cpp Pokeball.h
	$(CXX) -c Pokeball.cpp

tilemap.o: Pokemon.cpp Pokemon.h
	$(CXX) -c Pokemon.cpp
	
bullet.o: Bullet.cpp Bullet.h 
	$(CXX) -c Bullet.cpp

health.o: Health.cpp Health.h 
	$(CXX) -c Health.cpp

artillery.o: Artillery.cpp Artillery.h 
	$(CXX) -c Artillery.cpp

backpack.o: Backpack.cpp Backpack.h 
	$(CXX) -c Backpack.cpp

main.o: main.cpp Pokemon.h Pokeball.h Bullet.h Health.h Artillery.h Backpack.h
	$(CXX) -c main.cpp

game:  Pokeball.o main.o Pokemon.o Bullet.o Health.o Artillery.o Backpack.o
	$(CXX) main.o  Pokeball.o Pokemon.o Bullet.o Health.o Artillery.o Backpack.o  -o game $(LDLIBS)  


clean:
	rm -f game
	rm -f *.o