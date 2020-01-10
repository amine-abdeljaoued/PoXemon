CXX = g++
LDLIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system



collision.o: Collision.cpp Collision.h 
	$(CXX) -c -O2 Collision.cpp 

special_attacks_bar.o: Special_attacks_bar.cpp Special_Attacks_bar.h
	$(CXX) -c -O2 Special_attacks_bar.cpp 

pokeball.o: Pokeball.cpp Pokeball.h
	$(CXX) -c -O2 Pokeball.cpp

Pokemon.o: Pokemon.cpp Pokemon.h
	$(CXX) -c -O2 Pokemon.cpp

opponent.o: Opponent.cpp Opponent.h Pokemon.h 
	$(CXX) -c -O2 Opponent.cpp

player.o: Player.cpp Player.h Pokemon.h 
	$(CXX) -c -O2 Player.cpp

pokemon_Button.o: Pokemon_Button.cpp Pokemon_Button.h
	$(CXX) -c -O2 Pokemon_Button.cpp
	
bullet.o: Bullet.cpp Bullet.h 
	$(CXX) -c -O2 Bullet.cpp

fight.o: Fight.cpp Fight.h 
	$(CXX) -c -O2 Fight.cpp

bullet_bar.o: Bullet_bar.cpp Bullet_bar.h
	$(CXX) -c -O2 Bullet_bar.cpp

stateFunctions.o: StateFunctions.cpp StateFunctions.h
	$(CXX) -c -O2 StateFunctions.cpp

health.o: Health.cpp Health.h 
	$(CXX) -c -O2 Health.cpp

artillery.o: Artillery.cpp Artillery.h 
	$(CXX) -c -O2 Artillery.cpp

backpack.o: Backpack.cpp Backpack.h 
	$(CXX) -c -O2 Backpack.cpp

trainer_opponent.o: trainer_opponent.cpp trainer_opponent.hpp
	$(CXX) -c -O2 trainer_opponent.cpp


main.o: main.cpp Pokemon.h Pokeball.h Bullet.h Fight.h Health.h Artillery.h StateFunctions.h Backpack.h Opponent.h Bullet_bar.h Collision.h Special_Attacks_bar.h Pokemon_Button.h
	$(CXX) -c -O2 main.cpp


game:  Opponent.o Pokemon_Button.o Pokeball.o Fight.o main.o StateFunctions.o Pokemon.o Bullet.o Health.o Artillery.o Backpack.o Bullet_bar.o Player.o Collision.o Special_attacks_bar.o
	$(CXX) main.o  Opponent.o Pokemon_Button.o Fight.o Pokeball.o StateFunctions.o Pokemon.o Bullet.o Health.o Artillery.o Backpack.o Bullet_bar.o Player.o Collision.o Special_attacks_bar.o   -o game $(LDLIBS)  

all:  Opponent.o Pokemon_Button.o Pokeball.o Fight.o main.o StateFunctions.o Pokemon.o Bullet.o Health.o Artillery.o Backpack.o Bullet_bar.o Player.o Collision.o Special_attacks_bar.o trainer_opponent.o
	

clean:
	rm -f game
	rm -f *.o