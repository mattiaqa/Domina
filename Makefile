dama: Main.cpp player.cpp
	g++ --std=c++14 Main.cpp player.cpp -o dama && ./dama

play: play.cpp player.cpp
	g++ --std=c++14 play.cpp player.cpp -o play && ./play

clean:
	rm *.txt

