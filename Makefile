all:
	g++ main.cpp mainTitle.cpp mainGame.cpp map.cpp character.cpp graph.cpp -o program -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

run:
	./program

everything:
	make all
	make run

clean:
	rm program
	rm savestate.txt
