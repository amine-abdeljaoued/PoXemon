CXX = g++
LDLIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system



pokeball.o: Pokeball.cpp Pokeball.h
	$(CXX) -c -O2 Pokeball.cpp

Pokemon.o: Pokemon.cpp Pokemon.h
	$(CXX) -c -O2 Pokemon.cpp

opponent.o: Opponent.cpp Opponent.h Pokemon.h 
	$(CXX) -c -02 Opponent.cpp
	
bullet.o: Bullet.cpp Bullet.h 
	$(CXX) -c -O2 Bullet.cpp

bullet_bar.o: Bullet_bar.cpp Bullet_bar.h
	$(CXX) -c -O2 Bullet_bar.cpp

health.o: Health.cpp Health.h 
	$(CXX) -c -O2 Health.cpp

artillery.o: Artillery.cpp Artillery.h 
	$(CXX) -c -O2 Artillery.cpp

backpack.o: Backpack.cpp Backpack.h 
	$(CXX) -c -O2 Backpack.cpp

main.o: main.cpp Pokemon.h Pokeball.h Bullet.h Health.h Artillery.h Backpack.h Opponent.h Bullet_bar.h
	$(CXX) -c -O2 main.cpp


game:  Opponent.o Pokeball.o main.o Pokemon.o Bullet.o Health.o Artillery.o Backpack.o Bullet_bar.o
	$(CXX) main.o  Opponent.o Pokeball.o Pokemon.o Bullet.o Health.o Artillery.o Backpack.o Bullet_bar.o  -o game $(LDLIBS)  


clean:
	rm -f game
	rm -f *.o