#include "TicTacToe.h"

// constructors
TicTacToe::TicTacToe(){
    char choose;
    this->board = new char[9];

    std::cout << "Choose your character? \n";
    std::cin >> choose;

    if (toupper(choose) == 'X')
    {
        this->player = 'X';
        this->pc = 'O';
    }else{
        this->player = 'O';
        this->pc = 'X';
    }

    for (int i = 0; i < 9; i++)
    {
        this->board[i] = this->empty;
    }
    

    // this->board = std::make_shared<char[9]>();
}

// destructor
TicTacToe::~TicTacToe(){
    delete [] board;
}

// getters
const char TicTacToe::getPosition(const int &row, const int &col) const{
    return this->board[row*3 + col];
}

const int TicTacToe::getFreeSpaces() const{
    int freeSpaces{0};
    for (int i = 0; i < 9; i++)
    {
        if (this->board[i] == this->empty)
        {
            freeSpaces++;
        }
    }
    return freeSpaces;
}

const char TicTacToe::getWinner() const{

    // Check if the characters in the right diagonal are equal and different from empty
    if (this->getPosition(0, 0) == this->getPosition(1 , 1) && this->getPosition(0, 0) == this->getPosition(2, 2)){
        if (!(this->getPosition(0, 0) == this->empty))
        {
            return this->getPosition(0, 0);
        }
    }

    // Check if the characters in the left diagonal are equal and different from empty
    if (this->getPosition(0, 2) == this->getPosition(1, 1) && this->getPosition(0, 2) == this->getPosition(2, 0))
    {
        if (!(this->getPosition(0, 2) == this->empty))
        {
            return this->getPosition(0, 2);
        }
    }

    // Check if the characters in the rows are equal and different from empty
    for (int i = 0; i < 3; i++)
    {
        if (this->getPosition(i, 0) == this->getPosition(i, 1) && this->getPosition(i, 0) == this->getPosition(i, 2))
        {
            if (!(this->getPosition(i, 0) == this->empty))
            {
                return this->getPosition(i, 0);
            }
        }   
    }

    // Check if the characters in the columns are equal and different from empty
    for (int j = 0; j < 3; j++)
    {
        if (this->getPosition(0, j) == this->getPosition(1, j) && this->getPosition(0, j) == this->getPosition(2, j))
        {
            if (!(this->getPosition(0, j) == this->empty))
            {
                return this->getPosition(0, j);
            }
        }   
    }

    return this->empty;
}

// setters
void TicTacToe::setPosition(const int &row, const int &col,const char &position){
    this->board[row*3 + col] = position;
}

// configuration methods
void TicTacToe::resetBoard(){
    for (int i = 0; i < 9; i++)
    {
        this->board[i] = this->empty;
    }   
}

void TicTacToe::playerMove(){
    int x, y;
    
    do
    {
        std::cout << " Enter a row between 1 and 3: ";
        std::cin >> x;
        std::cout << " Enter a column between 1 and 3: ";
        std::cin >> y;

        if(this->getPosition(x - 1, y - 1) != this->empty){
            std::cout << " Your move is invalid!" << std::endl;
        }
        else
        {
            this->setPosition(x - 1, y - 1, this->player);
            break;
        }
    } while (this->getPosition(x - 1, y - 1) != this->empty);    
}

const int TicTacToe::evaluate(){

    // Looking for X or O to win for rows
    for (int i = 0; i < 3; i++)
    {
        if (this->getPosition(i, 0) == this->getPosition(i, 1) && this->getPosition(i, 0) == this->getPosition(i, 2))
        {
            if (this->getPosition(i, 0) == pc)
            {
                return +1;
            }else if(this->getPosition(i, 0) == player){
                return -1;
            }
        }
        
    }

    // Looking for X or O to win for columns
    for (int j = 0; j<3; j++)
    {
        if (this->getPosition(0, j) == this->getPosition(1, j) && this->getPosition(0, j) == this->getPosition(2, j))
        {
            if (this->getPosition(0, j) == pc){
                return +1;
            }
            else if (this->getPosition(0, j) == player){
                return -1;
            }
        }
    }
 
    // Looking for X or O to win for diagonals.
    if (this->getPosition(0, 0) == this->getPosition(1, 1) && this->getPosition(0, 0) == this->getPosition(2, 2))
    {
        if (this->getPosition(0, 0) == pc){
            return +1;
        }
        else if (this->getPosition(0, 0) == player){
            return -1;
        }
    }
 
    if (this->getPosition(0, 2) == this->getPosition(1, 1) && this->getPosition(0, 2) == this->getPosition(2, 0))
    {
        if (this->getPosition(0, 2) == pc){
            return +1;
        }
        else if (this->getPosition(0, 2) == player){
            return -1;
        }
    }
 
    // Else if none of them have won then return 0
    return 0;   
}

const int TicTacToe::minimax(const int &depth, const bool &isAi){
    int score = this->evaluate();
    // If maximize has won the game return their evaluated score
    if (score == 1){
        return score;
    }
    // If Minimizer has won the game return their evaluated score
    if (score == -1){
        return score;
    }
    // If there are no more moves and no winner then it's a tie
    if (this->getFreeSpaces() == 0){
        return 0;
    }
    if (depth < 9)
    {    
        // if this maximizar's move
        if (isAi)
        {
            int bestScore = -1000;

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    // Check if the position is empty
                    if (this->getPosition(i, j) == this->empty)
                    {
                        // Pc does a move
                        this->setPosition(i, j, pc);
                        logT("PC");
                        // Call minimax recursively and choose the maximum value
                        bestScore = std::max(bestScore, this->minimax(depth + 1, false));

                        // Undo the move
                        this->setPosition(i, j, this->empty);
                    }    
                }
            }
            return bestScore;
        }
        
        // if this minimizer's move
        else{
            int bestScore = 1000;

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; i < 3; j++)
                {
                    // Check if the position is empty
                    if (this->getPosition(i, j) == this->empty)
                    {
                        // Pc does a move
                        this->setPosition(i, j, player);
                        logT("Player");
                        // Call minimax recursively and choose the maximum value
                        bestScore = std::min(bestScore, this->minimax(depth + 1, true));

                        // Undo the move
                        this->setPosition(i, j, this->empty);
                    }
                }
                
            }
            return bestScore;
        }
    }else{
        return 0;
    }  
} // this shit sucks

TicTacToe::Move TicTacToe::findBestMovePosition()
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;
 
    // Traverse all cells, evaluate minimax function for all empt cells. And return the cell with optimal value
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            // Check if cell is empty
            if (this->getPosition(i, j) == this->empty)
            {
                // Make the move
                this->setPosition(i, j, this->pc);
            
                // compute evaluation function for this move
                int moveVal = this->minimax(0, false);
                
                // Undo the move
                this->setPosition(i, j, this->empty);
 
                // If the value of the current move is more than the best balue, then update best
                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

void TicTacToe::pcMove()
{
    if(this->getFreeSpaces() > 0)
    {        
        Move bestMove = this->findBestMovePosition();
        this->setPosition(bestMove.row, bestMove.col, pc);
    }
    else
    {
        printWinner();
    }
}

// utilities methods
void TicTacToe::printBoard(){
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << this->getPosition(i, j) << " | ";
        }
        std::cout << "\n";
        std::cout << "--|---|--\n";
    }
}

void TicTacToe::printWinner(){
    if (this->getWinner() == this->pc)
    {
        std::cout << "You lost, good luck next time!!\n";
    }else if(this->getWinner() == this->player){
        std::cout << "Congratulations you won!!\n";
    }else{
        std::cout << "It's tie\n";
    }
}