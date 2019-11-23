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

main.o: main.cpp Pokemon.h Pokeball.h Bullet.h Health.h
	$(CXX) -c main.cpp

game:  Pokeball.o main.o Pokemon.o Bullet.o Health.o
	$(CXX) main.o  Pokeball.o Pokemon.o Bullet.o Health.o  -o game $(LDLIBS)  


clean:
	rm -f game
	rm -f *.o