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

int main(int argc, char **argv){
	string board_name;

	Player p1(1);
	Player p2(2);
	
	int round = 1; // 1 or 2
	
	p1.init_board("board_1.txt");
	while(true){
		
		cout << "Playing as player 1" << endl;
		board_name =  "board_" + std::to_string(round) + ".txt";
		
		cout << "Reading board " << board_name << endl;
		
		std::this_thread::sleep_for (std::chrono::milliseconds(100));
			
		p1.load_board(board_name);
		p1.move();
		board_name =  "board_" + std::to_string(++round) + ".txt";
		p1.store_board(board_name);
		board_name =  "board_" + std::to_string(round) + ".txt";
		
		cout << "Playing as player 2" << endl;
		cout << "Reading board " << board_name << endl;
		
		std::this_thread::sleep_for (std::chrono::milliseconds(100));
			
		p2.load_board(board_name);
		p2.move();
		board_name =  "board_" + std::to_string(++round) + ".txt";
		p2.store_board(board_name);

	}
	
}
