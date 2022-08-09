#include "player.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::string;

#define MAX_ROUNDS 1000

int main(int argc, char **argv){
	string board_name;

	Player p1(1);
	Player p2(2);
	
	int round = 1; // 1 or 2

	p1.init_board("boards/board_1.txt");
	while(true){
		
		if(round > MAX_ROUNDS){
			cout << "reached max rounds";
			exit(0);
		}

		cout << "Playing as player 1" << endl;
		board_name =  "boards/board_" + std::to_string(round) + ".txt";
		cout << "Reading board " << board_name << endl;
			
		p1.load_board(board_name);
		std::this_thread::sleep_for (std::chrono::milliseconds(100));

		p1.move();

		board_name =  "boards/board_" + std::to_string(++round) + ".txt";
		p1.store_board(board_name);

		if(p1.wins()){
			cout << "Player 1 wins" << endl;
			exit(0);
		}

		cout << "Playing as player 2" << endl;
		board_name =  "boards/board_" + std::to_string(round) + ".txt";
		cout << "Reading board " << board_name << endl;
			
		p2.load_board(board_name);

		std::this_thread::sleep_for (std::chrono::milliseconds(100));
		p2.move();

		board_name =  "boards/board_" + std::to_string(++round) + ".txt";
		p2.store_board(board_name);

		if(p2.wins()){
			cout << "Player 2 wins" << endl;
			exit(0);
		}
	}
	
}
