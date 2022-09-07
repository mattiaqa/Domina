play: play.cpp player.cpp
	g++ --std=c++14 -Wall play.cpp player.cpp -o play && ./play

clean:
	rm boards/*.txt

