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
	Player v(1);

	int round = 1; // 1 or 2

	v.init_board("boards/board_1.txt");
	v.load_board("boards/board_1.txt");
	
	while(true){
		
		if(round > MAX_ROUNDS){
			cout << "Reached max rounds";
			break;
		}

		cout << "Playing as player 1" << endl;
		board_name =  "boards/board_" + std::to_string(round) + ".txt";
		cout << "Reading board " << board_name << endl;
		
		try{
			p1.load_board(board_name);
			std::this_thread::sleep_for (std::chrono::milliseconds(100));

			p1.move();

			board_name =  "boards/board_" + std::to_string(++round) + ".txt";
			p1.store_board(board_name);

			if(p1.wins()){
				cout << "Player 1 wins\n" << endl;
				break;
			}
		}catch(player_exception e){
			cout << e.msg << endl;
		}

		try{
			v.load_board(board_name);
			if(!v.valid_move()){
				cout << "Player 1 loses for invalid move\n";
				break;
			}
		}catch(player_exception e){
			cout << e.msg << endl;
		}

		cout << "Playing as player 2" << endl;
		board_name =  "boards/board_" + std::to_string(round) + ".txt";
		cout << "Reading board " << board_name << endl;
			
		try{
			p2.load_board(board_name);
			std::this_thread::sleep_for (std::chrono::milliseconds(100));

			p2.move();

			board_name =  "boards/board_" + std::to_string(++round) + ".txt";
			p2.store_board(board_name);

			if(p2.wins()){
				cout << "Player 2 wins\n" << endl;
				break;
			}
		}catch(player_exception e){
			cout << e.msg << endl;
		}

		try{
			v.load_board(board_name);

			if(!v.valid_move()){
				cout << "Player 2 loses for invalid move\n";
				break;
			}
		}catch(player_exception e){
			cout << e.msg << endl;
		}
	}

	Player p3(p1);
	Player p4 = p2;

	std::cout << p1.recurrence();
	
}