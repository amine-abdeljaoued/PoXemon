CXX = g++
LDLIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

pokeball.o: Pokeball.cpp Pokeball.h
	$(CXX) -c Pokeball.cpp

tilemap.o: Pokemon.cpp Pokemon.h
	$(CXX) -c Pokemon.cpp
	
bullet.o: Bullet.cpp Bullet.h 
	$(CXX) -c Bullet.cpp

main.o: main.cpp Pokemon.h Pokeball.h Bullet.h
	$(CXX) -c main.cpp

game:  Pokeball.o main.o Pokemon.o Bullet.o
	$(CXX) main.o  Pokeball.o Pokemon.o Bullet.o  -o game $(LDLIBS)  


clean:
	rm -f game
	rm -f *.o