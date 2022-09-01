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

bool validPosition(int r, int c){
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
                        if(validPosition(i - 1, j + 1)){
                            if( (*player)(i - 1, j + 1, 0) == Player::e){
                            availableMoves[nAvailableMoves++] = {j, i, false, "dx-up"};
                            }
                        }
                        if(validPosition(i - 1, j - 1)){
                            if( (*player)(i - 1, j - 1, 0) == Player::e){
                                availableMoves[nAvailableMoves++] = {j, i, false, "sx-up"};
                            }
                        }
                        if(validPosition(i - 2, j + 2)){
                            if( (*player)(i - 1, j + 1, 0) == Player::o &&
                                (*player)(i - 2, j + 2, 0) == Player::e){
                                availableJumps[nAvailableJumps++] = {j, i, true, "dx-up"};
                            }
                        }
                        if(validPosition(i - 2, j - 2)){
                            if( (*player)(i - 1, j - 1, 0) == Player::o &&
                                (*player)(i - 2, j - 2, 0) == Player::e){
                                availableJumps[nAvailableJumps++] = {j, i, true, "sx-up"};
                            }
                        }
                    }catch(player_exception e){}
                }else if(board[i * BOARD_DIM + j] == Player::X){
                    try{
                        if(validPosition(i + 1, j + 1)){
                            if( (*player)(i + 1, j + 1, 0) == Player::e){
                                availableMoves[nAvailableMoves++] = {j, i, false, "dx-down"};
                            }
                        }
                        if(validPosition(i + 1, j - 1)){
                            if( (*player)(i + 1, j - 1, 0) == Player::e){
                                availableMoves[nAvailableMoves++] = {j, i, false, "sx-down"};
                            }
                        }
                        if(validPosition(i - 1, j + 1)){
                            if( (*player)(i - 1, j + 1, 0) == Player::e){
                                availableMoves[nAvailableMoves++] = {j, i, false, "dx-up"};
                            }
                        }
                        if(validPosition(i - 1, j - 1)){
                            if( (*player)(i - 1, j - 1, 0) == Player::e){
                                availableMoves[nAvailableMoves++] = {j, i, false, "sx-up"};
                            }
                        }
                        if(validPosition(i + 2, j + 2)){
                            if( ((*player)(i + 1, j + 1, 0) == Player::o ||
                                (*player)(i + 1, j + 1, 0) == Player::O) &&
                                (*player)(i + 2, j + 2, 0) == Player::e){
                                availableJumps[nAvailableJumps++] = {j, i, true, "dx-down"};
                            }
                        }
                        if(validPosition(i + 2, j - 2)){
                            if( ((*player)(i + 1, j - 1, 0) == Player::o ||
                                (*player)(i + 1, j - 1, 0) == Player::O) &&
                                (*player)(i + 2, j - 2, 0) == Player::e){
                                availableJumps[nAvailableJumps++] = {j, i, true, "sx-down"};
                            }
                        }
                        if(validPosition(i - 2, j + 2)){
                            if( ((*player)(i - 1, j + 1, 0) == Player::o ||
                                (*player)(i - 1, j + 1, 0) == Player::O) &&
                                (*player)(i - 2, j + 2, 0) == Player::e){
                            availableJumps[nAvailableJumps++] = {j, i, true, "dx-up"};
                            }
                        }
                        if(validPosition(i - 2, j - 2)){
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

        /* If there are pawns to be eliminated, I choose one of those randomly.*/
        if(nAvailableJumps > 0){
            int randomPosition = rand() % (nAvailableJumps);
            return availableJumps[randomPosition];
        }

        /* Otherwise I choose the move randomly from those that do not eliminate pawns */
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
                        if(validPosition(i + 1, j + 1)){
                            if( (*player)(i + 1, j + 1, 0) == Player::e){
                                availableMoves[nAvailableMoves++] = {j, i, false, "dx-down"};
                            }
                        }
                        if(validPosition(i + 1, j - 1)){
                            if( (*player)(i + 1, j - 1, 0) == Player::e){
                                availableMoves[nAvailableMoves++] = {j, i, false, "sx-down"};
                            }
                        }
                        if(validPosition(i + 2, j + 2)){
                            if( (*player)(i + 1, j + 1, 0) == Player::x &&
                                (*player)(i + 2, j + 2, 0) == Player::e){
                                availableJumps[nAvailableJumps++] = {j, i, true, "dx-down"};
                            }
                        }
                        if(validPosition(i + 2, j - 2)){
                            if( (*player)(i + 1, j - 1, 0) == Player::x &&
                                (*player)(i + 2, j - 2, 0) == Player::e){
                                availableJumps[nAvailableJumps++] = {j, i, true, "sx-down"};
                            }
                        }
                    }catch(player_exception e){}
                }else if(board[i * BOARD_DIM + j] == Player::O){
                    try{
                        if(validPosition(i - 1, j + 1)){
                            if( (*player)(i - 1, j + 1, 0) == Player::e){
                                availableMoves[nAvailableMoves++] = {j, i, false, "dx-up"};
                            }
                        }
                        if(validPosition(i - 1, j - 1)){
                            if( (*player)(i - 1, j - 1, 0) == Player::e){
                                availableMoves[nAvailableMoves++] = {j, i, false, "sx-up"};
                            }
                        }
                        if(validPosition(i + 1, j + 1)){
                            if( (*player)(i + 1, j + 1, 0) == Player::e){
                            availableMoves[nAvailableMoves++] = {j, i, false, "dx-down"};
                            }
                        }
                        if(validPosition(i + 1, j - 1)){
                            if( (*player)(i + 1, j - 1, 0) == Player::e){
                                availableMoves[nAvailableMoves++] = {j, i, false, "sx-down"};
                            }
                        }
                        if(validPosition(i - 2, j + 2)){
                            if( ((*player)(i - 1, j + 1, 0) == Player::x ||
                                (*player)(i - 1, j + 1, 0) == Player::X) &&
                                (*player)(i - 2, j + 2, 0) == Player::e){
                                availableJumps[nAvailableJumps++] = {j, i, true, "dx-up"};
                            }
                        }
                        if(validPosition(i - 2, j - 2)){
                            if( ((*player)(i - 1, j - 1, 0) == Player::x ||
                                (*player)(i - 1, j - 1, 0) == Player::X) &&
                                (*player)(i - 2, j - 2, 0) == Player::e){
                                availableJumps[nAvailableJumps++] = {j, i, true, "sx-up"};
                            }
                        }
                        if(validPosition(i + 2, j + 2)){
                            if( ((*player)(i + 1, j + 1, 0) == Player::x ||
                                (*player)(i + 1, j + 1, 0) == Player::X) &&
                                (*player)(i + 2, j + 2, 0) == Player::e){
                                availableJumps[nAvailableJumps++] = {j, i, true, "dx-down"};
                            }
                        }
                        if(validPosition(i + 2, j - 2)){
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
        int nEntry;

    void prepend(Player::piece *board){
        if(!head){
            this->head = new node{board, nullptr};
            ++nEntry;
            return;
        }
        node_ptr newNode = new node{board, head};
        this->head = newNode;
        ++nEntry;
    }

    void deleteRecursively(node_ptr current){
        if(!current)
            return;

        deleteRecursively(current->next);

        delete[] current->board;
        delete current;
    }

    Player::piece* copyBoard(Player::piece* source){
        Player::piece *newBoard = new Player::piece[BOARD_DIM * BOARD_DIM];

        for(int i = 0; i < BOARD_DIM * BOARD_DIM; ++i){
            newBoard[i] = source[i];
        }

        return newBoard;
    }

    node_ptr copyList(node_ptr source) {
        if (!source)
            return nullptr;
        else{
            node_ptr newNode = new node;
            newNode->board = copyBoard(source->board);
            newNode->next = copyList(source->next);
            return newNode;
        }
    }

    public:
        History(){
            this->head = nullptr;
            this->nEntry = 0;
        };

        History(const History& source){
            this->nEntry = source.nEntry;
            this->head = copyList(source.head);
        };
 
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

        int getNumberOfEntry(){
            return this->nEntry;
        }
};

struct Player::Impl{
    int player_nr;
    History boardHistory;
};

Player::Player(int player_nr){
    if(player_nr < 1 || player_nr > 2)
        throw player_exception{player_exception::index_out_of_bounds, "Player_nr must be equal to 1 or 2!"};
    
    srand(time(0));
    this->pimpl = new Impl{player_nr, History{}};
}

Player::~Player() {
    delete this->pimpl;
}

Player::Player(const Player& source){
    this->pimpl = new Impl{source.pimpl->player_nr, History{source.pimpl->boardHistory}};
}

Player& Player::operator=(const Player& source){
    if(this != &source){
        this->~Player();
        this->pimpl = new Impl{source.pimpl->player_nr, History{source.pimpl->boardHistory}};
    }
    return *this;
}

Player::piece Player::operator()(int r, int c, int history_offset) const{
    if(!validPosition(r, c) || history_offset >= this->pimpl->boardHistory.getNumberOfEntry())
        throw player_exception{player_exception::index_out_of_bounds, "Index Out Of Bounds!"};

    Player::piece *board = this->pimpl->boardHistory.getBoard(history_offset);

    return board[r * BOARD_DIM + c];
}

void Player::load_board(const string& filename){
    std::ifstream fileIn{filename};
    Player::piece* board = new Player::piece[BOARD_DIM * BOARD_DIM];

    if(!fileIn.is_open()) 
        throw player_exception{player_exception::missing_file, "File not found"};

    string line;
    size_t row = 0, cols = 0;
    while(std::getline(fileIn, line, '\n')){
        cols = 0;
        for(int lineIndex = 0; lineIndex < line.size(); lineIndex+= 2){
            switch((char)line[lineIndex]){
                case 'x':
                    board[row * BOARD_DIM + cols] = x;
                break;
                case 'X':
                    board[row * BOARD_DIM + cols] = X;
                break;
                case 'o':
                    board[row * BOARD_DIM + cols] = o;
                break;
                case 'O':
                    board[row * BOARD_DIM + cols] = O;
                break;
                case ' ':
                    board[row * BOARD_DIM + cols] = e;
                break;
                default:
                    throw player_exception{player_exception::invalid_board, "Board contains invalid character!"};
                break;
            }
            ++cols;
        }
        ++row;
    }
    fileIn.close();
    this->pimpl->boardHistory.addBoard(board);
}

void Player::store_board(const string& filename, int history_offset) const{
    if(history_offset >= this->pimpl->boardHistory.getNumberOfEntry())
        throw player_exception{player_exception::index_out_of_bounds, "Board doesn't exist in memory"};

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
    if(this->pimpl->boardHistory.getNumberOfEntry() == 0)
        throw player_exception{player_exception::index_out_of_bounds, "History is empty!"};

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

void Player::pop(){
    if(this->pimpl->boardHistory.getNumberOfEntry() == 0)
        throw player_exception{player_exception::index_out_of_bounds, "History is empty!"};

    this->pimpl->boardHistory.pop();
}

bool Player::wins(int player_nr) const{
    if(this->pimpl->boardHistory.getNumberOfEntry() == 0)
        throw player_exception{player_exception::index_out_of_bounds, "History is empty!"};

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
    if(this->pimpl->boardHistory.getNumberOfEntry() == 0)
        throw player_exception{player_exception::index_out_of_bounds, "History is empty!"};

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

bool Player::valid_move() const{
    if(this->pimpl->boardHistory.getNumberOfEntry() < 2)
        throw player_exception{player_exception::index_out_of_bounds, "There are less than two boards in memory!"};

    Player::piece* lastBoard = this->pimpl->boardHistory.getBoard(0);
    Player::piece* secondToLastBoard = this->pimpl->boardHistory.getBoard(1);

    for(int i = 0; i < BOARD_DIM; ++i){
        for(int j = 0; j < BOARD_DIM; ++j){
            if(validPosition(i + 1, j + 1)){
                if( lastBoard[i * BOARD_DIM + j] == Player::X && 
                    secondToLastBoard[(i + 1) * BOARD_DIM + (j + 1)] == Player::x)
                    return true;

                if( secondToLastBoard[i * BOARD_DIM + j] == Player::o &&
                    lastBoard[(i + 1) * BOARD_DIM + (j + 1)] == Player::O)
                    return true;
            }
            if(validPosition(i + 1, j - 1)){
                if( lastBoard[i * BOARD_DIM + j] == Player::X && 
                    secondToLastBoard[(i + 1) * BOARD_DIM + (j - 1)] == Player::x)
                    return true;
                
                if( secondToLastBoard[i * BOARD_DIM + j] == Player::o &&
                    lastBoard[(i + 1) * BOARD_DIM + (j - 1)] == Player::O)
                    return true;
            }

            if(validPosition(i + 2, j - 2)){
                if( lastBoard[i * BOARD_DIM + j] == Player::X && 
                    secondToLastBoard[(i + 2) * BOARD_DIM + (j - 2)] == Player::x &&
                    secondToLastBoard[(i + 1) * BOARD_DIM + (j - 1)] == Player::o)
                    return true;
                
                if( secondToLastBoard[i * BOARD_DIM + j] == Player::o &&
                    lastBoard[(i + 2) * BOARD_DIM + (j - 2)] == Player::O &&
                    secondToLastBoard[(i + 1) * BOARD_DIM + (j - 1) == Player::x])
                    return true;
            }

            if(validPosition(i + 2, j + 2)){
                if( lastBoard[i * BOARD_DIM + j] == Player::X && 
                    secondToLastBoard[(i + 2) * BOARD_DIM + (j + 2)] == Player::x &&
                    secondToLastBoard[(i + 1) * BOARD_DIM + (j + 1)] == Player::o)
                    return true;
                
                if( secondToLastBoard[i * BOARD_DIM + j] == Player::o &&
                    lastBoard[(i + 2) * BOARD_DIM + (j + 2)] == Player::O &&
                    secondToLastBoard[(i + 1) * BOARD_DIM + (j + 1) == Player::x])
                    return true;
            }

            if(lastBoard[i * BOARD_DIM + j] != secondToLastBoard[i * BOARD_DIM + j]){
                if(secondToLastBoard[i * BOARD_DIM + j] == Player::o) {
                        bool isValid = false;
                        if(validPosition(i + 1, j + 1)){
                            if(lastBoard[(i + 1) * BOARD_DIM + (j + 1)] == Player::o)
                                isValid = true;
                        }
                        if(validPosition(i + 1, j - 1)){
                            if(lastBoard[(i + 1) * BOARD_DIM + (j - 1)] == Player::o)
                                isValid = true;
                        }
                        if(validPosition(i + 2, j - 2)){
                            if(lastBoard[(i + 2) * BOARD_DIM + (j - 2)] == Player::o &&
                                lastBoard[(i + 1) * BOARD_DIM + (j - 1) == Player::e] &&
                                secondToLastBoard[(i + 1) * BOARD_DIM + (j - 1)] == Player::x)
                                isValid = true;
                        }
                        if(validPosition(i + 2, j + 2)){
                            if(lastBoard[(i + 2) * BOARD_DIM + (j + 2)] == Player::o &&
                                lastBoard[(i + 1) * BOARD_DIM + (j + 1) == Player::e] &&
                                secondToLastBoard[(i + 1) * BOARD_DIM + (j + 1)] == Player::x)
                                isValid = true;
                        }
                        return isValid;
                }

                if(lastBoard[i * BOARD_DIM + j] == Player::x) {
                        bool isValid = false;
                        if(validPosition(i + 1, j + 1)){
                            if(secondToLastBoard[(i + 1) * BOARD_DIM + (j + 1)] == Player::x)
                                isValid = true;
                        }
                        if(validPosition(i + 1, j - 1)){
                            if(secondToLastBoard[(i + 1) * BOARD_DIM + (j - 1)] == Player::x)
                                isValid = true;
                        }
                        if(validPosition(i + 2, j + 2)){
                            if( secondToLastBoard[(i + 1) * BOARD_DIM + (j + 1)] == Player::o &&
                                secondToLastBoard[(i + 2) * BOARD_DIM + (j + 2)] == Player::x &&
                                lastBoard[(i + 1) * BOARD_DIM + (j + 1)] == Player::e)
                                isValid = true;
                        }
                        if(validPosition(i + 2, j - 2)){
                            if( secondToLastBoard[(i + 1) * BOARD_DIM + (j - 1)] == Player::o &&
                                secondToLastBoard[(i + 2) * BOARD_DIM + (j - 2)] == Player::x &&
                                lastBoard[(i + 1) * BOARD_DIM + (j - 1)] == Player::e)
                                isValid = true;
                        }

                        return isValid;
                }

                if(lastBoard[i * BOARD_DIM + j] == Player::O) {
                        bool isValid = false;
                        if(validPosition(i + 1, j + 1)){
                            if(secondToLastBoard[(i + 1) * BOARD_DIM + (j + 1)] == Player::O)
                                isValid = true;
                        }
                        if(validPosition(i + 1, j - 1)){
                            if(secondToLastBoard[(i + 1) * BOARD_DIM + (j - 1)] == Player::O)
                                isValid = true;
                        }
                        if(validPosition(i + 2, j + 2)){
                            if( (secondToLastBoard[(i + 1) * BOARD_DIM + (j + 1)] == Player::x ||
                                secondToLastBoard[(i + 1) * BOARD_DIM + (j + 1)] == Player::X) &&
                                secondToLastBoard[(i + 2) * BOARD_DIM + (j + 2)] == Player::O)
                                isValid = true;
                        }
                        if(validPosition(i + 2, j - 2)){
                            if( (secondToLastBoard[(i + 1) * BOARD_DIM + (j - 1)] == Player::x ||
                                secondToLastBoard[(i + 1) * BOARD_DIM + (j - 1)] == Player::X) &&
                                secondToLastBoard[(i + 2) * BOARD_DIM + (j - 2)] == Player::O)
                                isValid = true;
                        }
                        return isValid;
                }

                if(secondToLastBoard[i * BOARD_DIM + j] == Player::O) {
                        bool isValid = false;
                        if(validPosition(i + 1, j + 1)){
                            if(lastBoard[(i + 1) * BOARD_DIM + (j + 1)] == Player::O)
                                isValid = true;
                        }
                        if(validPosition(i + 1, j - 1)){
                            if(lastBoard[(i + 1) * BOARD_DIM + (j - 1)] == Player::O)
                                isValid = true;
                        }
                        if(validPosition(i + 2, j - 2)){
                            if( (secondToLastBoard[(i + 1) * BOARD_DIM + (j - 1)] == Player::x || 
                                secondToLastBoard[(i + 1) * BOARD_DIM + (j - 1)] == Player::X) &&
                                lastBoard[(i + 2) * BOARD_DIM + (j - 2)] == Player::O)
                                isValid = true;
                        }
                        if(validPosition(i + 2, j + 2)){
                            if( (secondToLastBoard[(i + 1) * BOARD_DIM + (j + 1)] == Player::x || 
                                secondToLastBoard[(i + 1) * BOARD_DIM + (j + 1)] == Player::X) &&
                                lastBoard[(i + 2) * BOARD_DIM + (j + 2)] == Player::O)
                                isValid = true;
                        }
                        
                        return isValid;
                }

                if(lastBoard[i * BOARD_DIM + j] == Player::X) {
                        bool isValid = false;
                        if(validPosition(i + 1, j + 1)){
                            if(secondToLastBoard[(i + 1) * BOARD_DIM + (j + 1)] == Player::X)
                                isValid = true;
                        }
                        if(validPosition(i + 1, j - 1)){
                            if(secondToLastBoard[(i + 1) * BOARD_DIM + (j - 1)] == Player::X)
                                isValid = true;
                        }
                        if(validPosition(i + 2, j + 2)){
                            if( (secondToLastBoard[(i + 1) * BOARD_DIM + (j + 1)] == Player::o ||
                                secondToLastBoard[(i + 1) * BOARD_DIM + (j + 1)] == Player::O) &&
                                secondToLastBoard[(i + 2) * BOARD_DIM + (j + 2)] == Player::X)
                                isValid = true;
                        }
                        if(validPosition(i + 2, j - 2)){
                            if( (secondToLastBoard[(i + 1) * BOARD_DIM + (j - 1)] == Player::o ||
                                secondToLastBoard[(i + 1) * BOARD_DIM + (j - 1)] == Player::O) &&
                                secondToLastBoard[(i + 2) * BOARD_DIM + (j - 2)] == Player::X)
                                isValid = true;
                        }
                        return isValid;
                }

                if(secondToLastBoard[i * BOARD_DIM + j] == Player::X) {
                        bool isValid = false;
                        if(validPosition(i + 1, j + 1)){
                            if(lastBoard[(i + 1) * BOARD_DIM + (j + 1)] == Player::X)
                                isValid = true;
                        }
                        if(validPosition(i + 1, j - 1)){
                            if(lastBoard[(i + 1) * BOARD_DIM + (j - 1)] == Player::X)
                                isValid = true;
                        }
                        if(validPosition(i + 2, j - 2)){
                            if( (secondToLastBoard[(i + 1) * BOARD_DIM + (j - 1)] == Player::o || 
                                secondToLastBoard[(i + 1) * BOARD_DIM + (j - 1)] == Player::O) &&
                                lastBoard[(i + 2) * BOARD_DIM + (j - 2)] == Player::X)
                                isValid = true;
                        }
                        if(validPosition(i + 2, j + 2)){
                            if( (secondToLastBoard[(i + 1) * BOARD_DIM + (j + 1)] == Player::o || 
                                secondToLastBoard[(i + 1) * BOARD_DIM + (j + 1)] == Player::O) &&
                                lastBoard[(i + 2) * BOARD_DIM + (j + 2)] == Player::X)
                                isValid = true;
                        }
                        return isValid;
                }

                return false;
            } 
        }
    }

    return false;
}


int Player::recurrence() const {
    if(this->pimpl->boardHistory.getNumberOfEntry() == 0)
        throw player_exception{player_exception::index_out_of_bounds, "History is empty!"};
        
    Player::piece *lastBoard = this->pimpl->boardHistory.getBoard(0);
    int countRec = 1;

    for(int i = 1; i < this->pimpl->boardHistory.getNumberOfEntry(); ++i){
        bool equal = true;
        Player::piece *currentBoard = this->pimpl->boardHistory.getBoard(i);
        for(int j = 0; j < BOARD_DIM * BOARD_DIM; ++j){
            if(lastBoard[j] != currentBoard[j]){
                equal = false;
                break;
            }
        }
        if(equal)
            ++countRec;
    }

    return countRec;
}