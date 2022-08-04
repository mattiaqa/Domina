#include "player.hpp"

#define BOARD_DIM 8

using std::size_t;

struct position{
    int x;
    int y;
};

position findPiecePosition(int checkerNumber, Player::piece type, Player::piece *board){
    int countPassedChecker = 0;

    for(int i = 0; i < BOARD_DIM; ++i){
        for(int j = 0; j < BOARD_DIM; ++j){
            if(board[i * BOARD_DIM + j] == type || board[i * BOARD_DIM + j] == type + 2)
                ++countPassedChecker;
            
            if(countPassedChecker == checkerNumber)
                return {j, i};
        }
    }

    return {-1, -1};
}

int moveDama(Player& currentObj, Player::piece *board, position coords, Player::piece type){
    int pos_y = coords.y;
    int pos_x = coords.x;
    Player::piece checker;
    Player::piece opponentChecker;

    if(type == Player::X){
        checker = Player::X;
        opponentChecker = Player::O;
    }else{
        checker = Player::O;
        opponentChecker = Player::X;
    }

    try{
        if(currentObj(pos_y + 1, pos_x + 1, 0) == Player::e){
            board[pos_y * BOARD_DIM + pos_x] = Player::e;
            board[(pos_y + 1) * BOARD_DIM + (pos_x - 1)] = checker;
            return 0;
        }else if(currentObj(pos_y + 1, pos_x - 1, 0) == Player::e){
            board[pos_y * BOARD_DIM + pos_x] = Player::e;
            board[(pos_y + 1) * BOARD_DIM + (pos_x - 1)] = checker;
            return 0;
        }else if(currentObj(pos_y - 1, pos_x + 1, 0) == Player::e){
            board[pos_y * BOARD_DIM + pos_x] = Player::e;
            board[(pos_y - 1) * BOARD_DIM + (pos_x + 1)] = checker;
            return 0;
        }else if(currentObj(pos_y - 1, pos_x - 1, 0) == Player::e){
            board[pos_y * BOARD_DIM + pos_x] = Player::e;
            board[(pos_y + 1) * BOARD_DIM + (pos_x - 1)] = checker;
            return 0;
        }else if(currentObj(pos_y + 1, pos_x + 1, 0) == opponentChecker &&
                 currentObj(pos_y + 1, pos_x + 1, 0) != checker - 2 &&
                 currentObj(pos_y + 2, pos_x + 2, 0) == Player::e){
                
                board[pos_y * BOARD_DIM + pos_x] = Player::e;
                board[(pos_y + 1) * BOARD_DIM + (pos_x + 1)] = Player::e;
                board[(pos_y + 2) * BOARD_DIM + (pos_x + 2)] = checker;
        }else if(currentObj(pos_y + 1, pos_x - 1, 0) == opponentChecker &&
                 currentObj(pos_y + 1, pos_x - 1, 0) != checker - 2 &&
                 currentObj(pos_y + 2, pos_x - 2, 0) == Player::e){
                
                board[pos_y * BOARD_DIM + pos_x] = Player::e;
                board[(pos_y + 1) * BOARD_DIM + (pos_x - 1)] = Player::e;
                board[(pos_y + 2) * BOARD_DIM + (pos_x - 2)] = checker;
        }else if(currentObj(pos_y - 1, pos_x + 1, 0) == opponentChecker &&
                 currentObj(pos_y - 1, pos_x + 1, 0) != checker - 2 &&
                 currentObj(pos_y - 2, pos_x + 2, 0) == Player::e){
                
                board[pos_y * BOARD_DIM + pos_x] = Player::e;
                board[(pos_y - 1) * BOARD_DIM + (pos_x + 1)] = Player::e;
                board[(pos_y - 2) * BOARD_DIM + (pos_x + 2)] = checker;
        }else if(currentObj(pos_y - 1, pos_x - 1, 0) == opponentChecker &&
                 currentObj(pos_y - 1, pos_x - 1, 0) != checker - 2  &&
                 currentObj(pos_y - 2, pos_x - 2, 0) == Player::e){
                
                board[pos_y * BOARD_DIM + pos_x] = Player::e;
                board[(pos_y - 1) * BOARD_DIM + (pos_x - 1)] = Player::e;
                board[(pos_y - 2) * BOARD_DIM + (pos_x - 2)] = checker;
        }
    }catch(player_exception e){
        return 2;
    }
    return -1;
}

int movePiece(Player& currentObj, Player::piece *board, position coords, Player::piece type){
    int pos_y = coords.y;
    int pos_x = coords.x;

    if(type == Player::x){
        try{
            if(currentObj(pos_y - 1, pos_x - 1, 0) == Player::e){
                board[pos_y * BOARD_DIM + pos_x] = Player::e;
                board[(pos_y - 1) * BOARD_DIM + (pos_x - 1)] = Player::x;
                return 0;
            }else if(currentObj(pos_y - 1, pos_x + 1, 0) == Player::e){
                board[pos_y * BOARD_DIM + pos_x] = Player::e;
                board[(pos_y - 1) * BOARD_DIM + (pos_x + 1)] = Player::x;
                return 0;
            }else if(currentObj(pos_y - 2, pos_x - 2, 0) == Player::e &&
                    currentObj(pos_y - 1, pos_x - 1, 0) == Player::o){
                board[pos_y * BOARD_DIM + pos_x] = Player::e;
                board[(pos_y - 1) * BOARD_DIM + (pos_x - 1)] = Player::e;
                board[(pos_y - 2) * BOARD_DIM + (pos_x - 2)] = Player::x;
                return 0;
            }else if(currentObj(pos_y - 2, pos_x + 2, 0) == Player::e &&
                    currentObj(pos_y - 1, pos_x + 1, 0) == Player::o){
                board[pos_y * BOARD_DIM + pos_x] = Player::e;
                board[(pos_y - 1) * BOARD_DIM + (pos_x + 1)] = Player::e;
                board[(pos_y - 2) * BOARD_DIM + (pos_x + 2)] = Player::x;
                return 0;
            }else{
                return 1;
            }
        }catch(player_exception e){
            return 2;
        }
    }else if(type == Player::o){
        try{
            if(currentObj(pos_y + 1, pos_x - 1, 0) == Player::e){
                board[pos_y * BOARD_DIM + pos_x] = Player::e;
                board[(pos_y + 1) * BOARD_DIM + (pos_x - 1)] = Player::o;
                return 0;
            }else if(currentObj(pos_y + 1, pos_x + 1, 0) == Player::e){
                board[pos_y * BOARD_DIM + pos_x] = Player::e;
                board[(pos_y + 1) * BOARD_DIM + (pos_x + 1)] = Player::o;
                return 0;
            }else if(currentObj(pos_y + 2, pos_x - 2, 0) == Player::e &&
                    currentObj(pos_y + 1, pos_x - 1, 0) == Player::x){
                board[pos_y * BOARD_DIM + pos_x] = Player::e;
                board[(pos_y + 1) * BOARD_DIM + (pos_x - 1)] = Player::e;
                board[(pos_y + 2) * BOARD_DIM + (pos_x - 2)] = Player::o;
                return 0;
            }else if(currentObj(pos_y + 2, pos_x + 2, 0) == Player::e &&
                    currentObj(pos_y + 1, pos_x + 1, 0) == Player::x){
                board[pos_y * BOARD_DIM + pos_x] = Player::e;
                board[(pos_y + 1) * BOARD_DIM + (pos_x + 1)] = Player::e;
                board[(pos_y + 2) * BOARD_DIM + (pos_x + 2)] = Player::o;
                return 0;
            }else{
                return 1;
            }
        }catch(player_exception e){
            return 2;
        }
    }
    return -1;
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

bool isStall(Player::piece *board){
    for(int i = 0; i < BOARD_DIM; ++i){
        for(int j = 0; j < BOARD_DIM; ++j){
            
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
    
    srand(time(NULL));
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
        else
            temp.erase(temp.end());
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
        int resultCode;
        bool valid = false;

        while(!valid){
            try{
                int pieceNum = rand() % 12 + 1;
            
                position piecePosition = findPiecePosition(pieceNum, x, board);
                int pos_x = piecePosition.x;
                int pos_y = piecePosition.y;

                if((*this)(pos_y, pos_x, 0) == X)
                    resultCode = moveDama(*this, board, piecePosition, X);
                else if((*this)(pos_y, pos_x, 0) == x)
                    resultCode = movePiece(*this, board, piecePosition, x);

                makeDama(board, x);

                if(resultCode == 0)
                    valid = true;
            }catch(player_exception e){}
        }
    }else{
        bool valid = false;
        int resultCode;
        
        while(!valid){
            try{
                int pieceNum = rand() % 12 + 1;
            
                position piecePosition = findPiecePosition(pieceNum, o, board);
                int pos_x = piecePosition.x;
                int pos_y = piecePosition.y;

                if((*this)(pos_y, pos_x, 0) == O)
                    resultCode = moveDama(*this, board, piecePosition, O);
                else if((*this)(pos_y, pos_x, 0) == o)
                    resultCode = movePiece(*this, board, piecePosition, o);

                makeDama(board, o);

                if(resultCode == 0)
                    valid = true;
            }catch(player_exception e){}
        }
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
                if(board[i * BOARD_DIM + j] == o)
                    return false;
            }
        }
        return true;
    }else{
        for(int i = 0; i < BOARD_DIM; ++i){
            for(int j = 0; j < BOARD_DIM; ++j){
                if(board[i * BOARD_DIM + j] == x)
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
                if(board[i * BOARD_DIM + j] == x)
                    return false;
            }
        }
        return true;
    }else{
        for(int i = 0; i < BOARD_DIM; ++i){
            for(int j = 0; j < BOARD_DIM; ++j){
                if(board[i * BOARD_DIM + j] == o)
                    return false;
            }
        }
        return true;
    }
}

bool Player::loses() const{
    return this->loses(this->pimpl->player_nr);
}