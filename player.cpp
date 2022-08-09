#include "player.hpp"

#define BOARD_DIM 8

using std::size_t;

struct Position{
    int x;
    int y;
};

struct availableMove{
    int x;
    int y;
    bool canJump;
    string direction;
};

bool checkPosition(int r, int c){
    if(r < 0 || r > 7 || c < 0 || c > 7)
        return false;
    return true;
}

availableMove findPieceToMove(Player* player, Player::piece *board, Player::piece type){
    if(type == Player::x){
        availableMove availableMoves[26];
        availableMove availableJumps[26];

        int nAvailableMoves = 0;
        int nAvailableJumps = 0;
        for(int i = 0; i < BOARD_DIM; ++i){
            for(int j = 0; j < BOARD_DIM; ++j){
                if(board[i * BOARD_DIM + j] == Player::x){
                    try{
                        if(checkPosition(i - 1, j + 1)){
                            if( (*player)(i - 1, j + 1, 0) == Player::e){
                            availableMoves[nAvailableMoves++] = {j, i, false, "dx-up"};
                            }
                        }
                        if(checkPosition(i - 1, j - 1)){
                            if( (*player)(i - 1, j - 1, 0) == Player::e){
                                availableMoves[nAvailableMoves++] = {j, i, false, "sx-up"};
                            }
                        }
                        if(checkPosition(i - 2, j + 2)){
                            if( (*player)(i - 1, j + 1, 0) == Player::o &&
                                (*player)(i - 2, j + 2, 0) == Player::e){
                                availableJumps[nAvailableJumps++] = {j, i, true, "dx-up"};
                            }
                        }
                        if(checkPosition(i - 2, j - 2)){
                            if( (*player)(i - 1, j - 1, 0) == Player::o &&
                                (*player)(i - 2, j - 2, 0) == Player::e){
                                availableJumps[nAvailableJumps++] = {j, i, true, "sx-up"};
                            }
                        }
                    }catch(player_exception e){}
                }else if(board[i * BOARD_DIM + j] == Player::X){
                    try{
                        if(checkPosition(i + 1, j + 1)){
                            if( (*player)(i + 1, j + 1, 0) == Player::e){
                                availableMoves[nAvailableMoves++] = {j, i, false, "dx-down"};
                            }
                        }
                        if(checkPosition(i + 1, j - 1)){
                            if( (*player)(i + 1, j - 1, 0) == Player::e){
                                availableMoves[nAvailableMoves++] = {j, i, false, "sx-down"};
                            }
                        }
                        if(checkPosition(i - 1, j + 1)){
                            if( (*player)(i - 1, j + 1, 0) == Player::e){
                                availableMoves[nAvailableMoves++] = {j, i, false, "dx-up"};
                            }
                        }
                        if(checkPosition(i - 1, j - 1)){
                            if( (*player)(i - 1, j - 1, 0) == Player::e){
                                availableMoves[nAvailableMoves++] = {j, i, false, "sx-up"};
                            }
                        }
                        if(checkPosition(i + 2, j + 2)){
                            if( ((*player)(i + 1, j + 1, 0) == Player::o ||
                                (*player)(i + 1, j + 1, 0) == Player::O) &&
                                (*player)(i + 2, j + 2, 0) == Player::e){
                                availableJumps[nAvailableJumps++] = {j, i, true, "dx-down"};
                            }
                        }
                        if(checkPosition(i + 2, j - 2)){
                            if( ((*player)(i + 1, j - 1, 0) == Player::o ||
                                (*player)(i + 1, j - 1, 0) == Player::O) &&
                                (*player)(i + 2, j - 2, 0) == Player::e){
                                availableJumps[nAvailableJumps++] = {j, i, true, "sx-down"};
                            }
                        }
                        if(checkPosition(i - 2, j + 2)){
                            if( ((*player)(i - 1, j + 1, 0) == Player::o ||
                                (*player)(i - 1, j + 1, 0) == Player::O) &&
                                (*player)(i - 2, j + 2, 0) == Player::e){
                            availableJumps[nAvailableJumps++] = {j, i, true, "dx-up"};
                            }
                        }
                        if(checkPosition(i - 2, j - 2)){
                            if( ((*player)(i - 1, j - 1, 0) == Player::o ||
                                (*player)(i - 1, j - 1, 0) == Player::O) &&
                                (*player)(i - 2, j - 2, 0) == Player::e){
                                availableJumps[nAvailableJumps++] = {j, i, true, "sx-up"};
                            }
                        }
                    }catch(player_exception e){}
                }
            }
        }

        if(nAvailableJumps > 0){
            int randomPosition = rand() % (nAvailableJumps);
            return availableJumps[randomPosition];
        }
        int randomPosition = rand() % (nAvailableMoves);
        return availableMoves[randomPosition];
    }else{
        availableMove availableMoves[26];
        availableMove availableJumps[26];

        int nAvailableMoves = 0;
        int nAvailableJumps = 0;

        for(int i = 0; i < BOARD_DIM; ++i){
            for(int j = 0; j < BOARD_DIM; ++j){
                if(board[i * BOARD_DIM + j] == Player::o){
                    try{
                        if(checkPosition(i + 1, j + 1)){
                            if( (*player)(i + 1, j + 1, 0) == Player::e){
                                availableMoves[nAvailableMoves++] = {j, i, false, "dx-down"};
                            }
                        }
                        if(checkPosition(i + 1, j - 1)){
                            if( (*player)(i + 1, j - 1, 0) == Player::e){
                                availableMoves[nAvailableMoves++] = {j, i, false, "sx-down"};
                            }
                        }
                        if(checkPosition(i + 2, j + 2)){
                            if( (*player)(i + 1, j + 1, 0) == Player::x &&
                                (*player)(i + 2, j + 2, 0) == Player::e){
                                availableJumps[nAvailableJumps++] = {j, i, true, "dx-down"};
                            }
                        }
                        if(checkPosition(i + 2, j - 2)){
                            if( (*player)(i + 1, j - 1, 0) == Player::x &&
                                (*player)(i + 2, j - 2, 0) == Player::e){
                                availableJumps[nAvailableJumps++] = {j, i, true, "sx-down"};
                            }
                        }
                    }catch(player_exception e){}
                }else if(board[i * BOARD_DIM + j] == Player::O){
                    try{
                        if(checkPosition(i - 1, j + 1)){
                            if( (*player)(i - 1, j + 1, 0) == Player::e){
                                availableMoves[nAvailableMoves++] = {j, i, false, "dx-up"};
                            }
                        }
                        if(checkPosition(i - 1, j - 1)){
                            if( (*player)(i - 1, j - 1, 0) == Player::e){
                                availableMoves[nAvailableMoves++] = {j, i, false, "sx-up"};
                            }
                        }
                        if(checkPosition(i + 1, j + 1)){
                            if( (*player)(i + 1, j + 1, 0) == Player::e){
                            availableMoves[nAvailableMoves++] = {j, i, false, "dx-down"};
                            }
                        }
                        if(checkPosition(i + 1, j - 1)){
                            if( (*player)(i + 1, j - 1, 0) == Player::e){
                                availableMoves[nAvailableMoves++] = {j, i, false, "sx-down"};
                            }
                        }
                        if(checkPosition(i - 2, j + 2)){
                            if( ((*player)(i - 1, j + 1, 0) == Player::x ||
                                (*player)(i - 1, j + 1, 0) == Player::X) &&
                                (*player)(i - 2, j + 2, 0) == Player::e){
                                availableJumps[nAvailableJumps++] = {j, i, true, "dx-up"};
                            }
                        }
                        if(checkPosition(i - 2, j - 2)){
                            if( ((*player)(i - 1, j - 1, 0) == Player::x ||
                                (*player)(i - 1, j - 1, 0) == Player::X) &&
                                (*player)(i - 2, j - 2, 0) == Player::e){
                                availableJumps[nAvailableJumps++] = {j, i, true, "sx-up"};
                            }
                        }
                        if(checkPosition(i + 2, j + 2)){
                            if( ((*player)(i + 1, j + 1, 0) == Player::x ||
                                (*player)(i + 1, j + 1, 0) == Player::X) &&
                                (*player)(i + 2, j + 2, 0) == Player::e){
                                availableJumps[nAvailableJumps++] = {j, i, true, "dx-down"};
                            }
                        }
                        if(checkPosition(i + 2, j - 2)){
                            if( ((*player)(i + 1, j - 1, 0) == Player::x ||
                                (*player)(i + 1, j - 1, 0) == Player::X) &&
                                (*player)(i + 2, j - 2, 0) == Player::e){
                                availableJumps[nAvailableJumps++] = {j, i, true, "sx-down"};
                            }
                        }
                    }catch(player_exception e){}
                }
            }
        }

        if(nAvailableJumps > 0){
            int randomPosition = rand() % (nAvailableJumps);
            return availableJumps[randomPosition];
        }
        int randomPosition = rand() % (nAvailableMoves);
        return availableMoves[randomPosition];

    }
}

void makeDama(Player::piece *board, Player::piece type){
    if(type == Player::x){
        for(int i = 0; i < BOARD_DIM; ++i){
            if(board[i] == Player::x)
                board[i] = Player::X;
        }
    }else if(type == Player::o){
        for(int i = 0 ; i < BOARD_DIM; ++i){
            if(board[(BOARD_DIM - 1) * BOARD_DIM + i] == Player::o)
                board[(BOARD_DIM - 1) * BOARD_DIM + i] = Player::O;
        }
    }
}

class History{
    private:
        struct node{
            Player::piece *board;
            node* next;
        };
        using node_ptr = node*;

        node_ptr head;

    void prepend(Player::piece *board){
        if(!head){
            this->head = new node{board, nullptr};
            return;
        }
        node_ptr newNode = new node{board, head};
        this->head = newNode;
    }

    void deleteRecursively(node_ptr current){
        if(!current)
            return;
        deleteRecursively(current->next);
        delete(current->board);
        delete(current);
    }

    public:
        History() : head{nullptr} {};
 
        ~History(){
            deleteRecursively(this->head);
        }

        void addBoard(Player::piece* board){
            this->prepend(board);
        }

        Player::piece* getBoard(int history_offset) const{
            node_ptr current = this->head;
            while(current && history_offset > 0){
                current = current->next;
                --history_offset;   
            }

            return current->board;
        }

        void pop(){
            node_ptr temp = this->head;
            this->head = temp->next;
            delete(temp);
        }
};

struct Player::Impl{
    int player_nr;
    int nDame;
    History boardHistory;
};

Player::Player(int player_nr){
    if(player_nr < 1 || player_nr > 2)
        throw player_exception{player_exception::index_out_of_bounds, "Player_nr must be equal to 1 or 2!"};
    
    srand(time(0));
    this->pimpl = new Impl{player_nr, 0, History{}};
}

Player::~Player() {
    delete this->pimpl;
}

Player::Player(const Player& source){
    this->pimpl = new Impl{source.pimpl->player_nr, 0, History{source.pimpl->boardHistory}};
}

Player& Player::operator=(const Player& source){
    this->~Player();
    this->pimpl = new Impl{source.pimpl->player_nr, 0, History{source.pimpl->boardHistory}};
    return *this;
}

Player::piece Player::operator()(int r, int c, int history_offset) const{
    if(r < 0 || r > 7 || c < 0 || c > 7)
        throw player_exception{player_exception::index_out_of_bounds, "Index Out Of Bounds!"};

    Player::piece *board = this->pimpl->boardHistory.getBoard(history_offset);

    return board[r * BOARD_DIM + c];
}

void Player::load_board(const string& filename){
    std::ifstream fileIn{filename};
    Player::piece* board = new Player::piece[BOARD_DIM * BOARD_DIM];

    if(!fileIn.is_open()) 
        throw std::runtime_error("Could not open file");

    string line;
    size_t raw = 0, cols = 0;
    while(std::getline(fileIn, line, '\n')){
        cols = 0;
        for(int lineIndex = 0; lineIndex < line.size(); lineIndex+= 2){
            switch((char)line[lineIndex]){
                case 'x':
                    board[raw * BOARD_DIM + cols] = x;
                break;
                case 'X':
                    board[raw * BOARD_DIM + cols] = X;
                break;
                case 'o':
                    board[raw * BOARD_DIM + cols] = o;
                break;
                case 'O':
                    board[raw * BOARD_DIM + cols] = O;
                break;
                case ' ':
                    board[raw * BOARD_DIM + cols] = e;
                break;
                default:
                    throw player_exception{player_exception::invalid_board, "Board contains invalid character!"};
                break;
            }
            ++cols;
        }
        ++raw;
    }
    this->pimpl->boardHistory.addBoard(board);
    fileIn.close();
}

void Player::store_board(const string& filename, int history_offset) const{
    Player::piece *board = this->pimpl->boardHistory.getBoard(history_offset);
    ofstream outFile{filename};

    for(int i = 0; i < BOARD_DIM; ++i){
        string temp = "";
        for(int j = 0; j < BOARD_DIM; ++j){
            switch(board[i * BOARD_DIM + j]){
                case x:
                    temp.append("x ");
                break;
                case X:
                    temp.append("X ");
                break;
                case o:
                    temp.append("o ");
                break;
                case O:
                    temp.append("O ");
                break;
                case e:
                    temp.append("  ");
                break;
            }
        }
        if(i != BOARD_DIM - 1)  
            temp.at(15) = '\n';
        else if(i == BOARD_DIM - 1)
            temp.erase(temp.end() - 1);
        outFile << temp;
    }

    outFile.close();
}

void Player::init_board(const string& filename) const {
    ofstream outFile{filename};

    string initialBoard = 
                "o   o   o   o  \n"
                "  o   o   o   o\n"
                "o   o   o   o  \n"
                "               \n"
                "               \n"
                "  x   x   x   x\n"
                "x   x   x   x  \n"
                "  x   x   x   x";
    
    outFile << initialBoard;

    outFile.close();
}

void Player::move(){
    /* Player 1 -> x || Player 2 -> o */
    Player::piece *board = this->pimpl->boardHistory.getBoard(0);
    if(this->pimpl->player_nr == 1){
        availableMove pieceToMove = findPieceToMove(this, board, Player::x);
        int x = pieceToMove.x;
        int y = pieceToMove.y;

        if(!pieceToMove.canJump){
            if(board[y * BOARD_DIM + x] == Player::x){
                board[y * BOARD_DIM + x] = Player::e;
                if(pieceToMove.direction == "sx-up"){
                    board[(y - 1) * BOARD_DIM + (x - 1)] = Player::x;
                }
                if(pieceToMove.direction == "dx-up"){
                    board[(y - 1) * BOARD_DIM + (x + 1)] = Player::x;
                }
            }else if(board[y * BOARD_DIM + x] == Player::X){
                board[y * BOARD_DIM + x] = Player::e;
                if(pieceToMove.direction == "sx-down"){
                    board[(y + 1) * BOARD_DIM + (x - 1)] = Player::X;
                }
                if(pieceToMove.direction == "dx-down"){
                    board[(y + 1) * BOARD_DIM + (x + 1)] = Player::X;
                }
                if(pieceToMove.direction == "sx-up"){
                    board[(y - 1) * BOARD_DIM + (x - 1)] = Player::X;
                }
                if(pieceToMove.direction == "dx-up"){
                    board[(y - 1) * BOARD_DIM + (x + 1)] = Player::X;
                }
            }
        }else{
            if(board[y * BOARD_DIM + x] == Player::x){
                board[y * BOARD_DIM + x] = Player::e;
                if(pieceToMove.direction == "sx-up"){
                    board[(y - 1) * BOARD_DIM + (x - 1)] = Player::e;
                    board[(y - 2) * BOARD_DIM + (x - 2)] = Player::x;
                }
                if(pieceToMove.direction == "dx-up"){
                    board[(y - 1) * BOARD_DIM + (x + 1)] = Player::e;
                    board[(y - 2) * BOARD_DIM + (x + 2)] = Player::x;
                }
            }else if(board[y * BOARD_DIM + x] == Player::X){
                board[y * BOARD_DIM + x] = Player::e;
                if(pieceToMove.direction == "sx-down"){
                    board[(y + 1) * BOARD_DIM + (x - 1)] = Player::e;
                    board[(y + 2) * BOARD_DIM + (x - 2)] = Player::X;
                }
                if(pieceToMove.direction == "dx-down"){
                    board[(y + 1) * BOARD_DIM + (x + 1)] = Player::e;
                    board[(y + 2) * BOARD_DIM + (x + 2)] = Player::X;
                }
                if(pieceToMove.direction == "sx-up"){
                    board[(y - 1) * BOARD_DIM + (x - 1)] = Player::e;
                    board[(y - 2) * BOARD_DIM + (x - 2)] = Player::X;
                }
                if(pieceToMove.direction == "dx-up"){
                    board[(y - 1) * BOARD_DIM + (x + 1)] = Player::e;
                    board[(y - 2) * BOARD_DIM + (x + 2)] = Player::X;
                }
            }
        }

        makeDama(board, Player::x);
    }else{
        availableMove pieceToMove = findPieceToMove(this, board, Player::o);
        int x = pieceToMove.x;
        int y = pieceToMove.y;

        if(!pieceToMove.canJump){
            if(board[y * BOARD_DIM + x] == Player::o){
                board[y * BOARD_DIM + x] = Player::e;
                if(pieceToMove.direction == "sx-down"){
                    board[(y + 1) * BOARD_DIM + (x - 1)] = Player::o;
                }
                if(pieceToMove.direction == "dx-down"){
                    board[(y + 1) * BOARD_DIM + (x + 1)] = Player::o;
                }
            }else if(board[y * BOARD_DIM + x] == Player::O){
                board[y * BOARD_DIM + x] = Player::e;
                if(pieceToMove.direction == "sx-down"){
                    board[(y + 1) * BOARD_DIM + (x - 1)] = Player::O;
                }
                if(pieceToMove.direction == "dx-down"){
                    board[(y + 1) * BOARD_DIM + (x + 1)] = Player::O;
                }
                if(pieceToMove.direction == "sx-up"){
                    board[(y - 1) * BOARD_DIM + (x - 1)] = Player::O;
                }
                if(pieceToMove.direction == "dx-up"){
                    board[(y - 1) * BOARD_DIM + (x + 1)] = Player::O;
                }
            }
        }else{
            if(board[y * BOARD_DIM + x] == Player::o){
                board[y * BOARD_DIM + x] = Player::e;
                if(pieceToMove.direction == "sx-down"){
                    board[(y + 1) * BOARD_DIM + (x - 1)] = Player::e;
                    board[(y + 2) * BOARD_DIM + (x - 2)] = Player::o;
                }
                if(pieceToMove.direction == "dx-down"){
                    board[(y + 1) * BOARD_DIM + (x + 1)] = Player::e;
                    board[(y + 2) * BOARD_DIM + (x + 2)] = Player::o;
                }
            }else if(board[y * BOARD_DIM + x] == Player::O){
                board[y * BOARD_DIM + x] = Player::e;
                if(pieceToMove.direction == "sx-down"){
                    board[(y + 1) * BOARD_DIM + (x - 1)] = Player::e;
                    board[(y + 2) * BOARD_DIM + (x - 2)] = Player::O;
                }
                if(pieceToMove.direction == "dx-down"){
                    board[(y + 1) * BOARD_DIM + (x + 1)] = Player::e;
                    board[(y + 2) * BOARD_DIM + (x + 2)] = Player::O;
                }
                if(pieceToMove.direction == "sx-up"){
                    board[(y - 1) * BOARD_DIM + (x - 1)] = Player::e;
                    board[(y - 2) * BOARD_DIM + (x - 2)] = Player::O;
                }
                if(pieceToMove.direction == "dx-up"){
                    board[(y - 1) * BOARD_DIM + (x + 1)] = Player::e;
                    board[(y - 2) * BOARD_DIM + (x + 2)] = Player::O;
                }
            }
        }
        makeDama(board, Player::o);
    }
}

bool Player::valid_move() const{
    return false;
}

void Player::pop(){
    this->pimpl->boardHistory.pop();
}

bool Player::wins(int player_nr) const{
    Player::piece *board = this->pimpl->boardHistory.getBoard(0);

    if(player_nr == 1){
        for(int i = 0; i < BOARD_DIM; ++i){
            for(int j = 0; j < BOARD_DIM; ++j){
                if(board[i * BOARD_DIM + j] == o || board[i * BOARD_DIM + j] == O)
                    return false;
            }
        }
        return true;
    }else{
        for(int i = 0; i < BOARD_DIM; ++i){
            for(int j = 0; j < BOARD_DIM; ++j){
                if(board[i * BOARD_DIM + j] == x || board[i * BOARD_DIM + j] == X)
                    return false;
            }
        }
        return true;
    }
}

bool Player::wins() const{
    return this->wins(this->pimpl->player_nr);
}

bool Player::loses(int player_nr) const{
    Player::piece *board = this->pimpl->boardHistory.getBoard(0);

    if(player_nr == 1){
        for(int i = 0; i < BOARD_DIM; ++i){
            for(int j = 0; j < BOARD_DIM; ++j){
                if(board[i * BOARD_DIM + j] == x || board[i * BOARD_DIM + j] == X)
                    return false;
            }
        }
        return true;
    }else{
        for(int i = 0; i < BOARD_DIM; ++i){
            for(int j = 0; j < BOARD_DIM; ++j){
                if(board[i * BOARD_DIM + j] == o || board[i * BOARD_DIM + j] == O)
                    return false;
            }
        }
        return true;
    }
}

bool Player::loses() const{
    return this->loses(this->pimpl->player_nr);
}