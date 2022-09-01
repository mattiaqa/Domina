play: play.cpp player.cpp
	g++ --std=c++14 -Wall play.cpp player.cpp -o play && ./play

verify: verify.cpp player.cpp
	g++ --std=c++14 -Wall verify.cpp player.cpp -o verify && ./verify

clean:
	rm boards/*.txt

