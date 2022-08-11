#include "player.hpp"

int main(){
	Player p(1);

	p.load_board("board_1.txt");
	p.load_board("board_2.txt");
	p.load_board("board_3.txt");
	p.load_board("board_4.txt");
	
	cout << p.recurrence();
}