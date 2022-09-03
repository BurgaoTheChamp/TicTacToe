#ifndef TicTacToe_H
#define TicTacToe_H

#include <memory>
#include <iostream>
#include <cctype>

class TicTacToe
{
    private:
        char *board; // board[i*col +j]
        // std::shared_ptr<char[9]> board; // board[i*col +j] 
        char player, pc; // Holds the players characters
    public:
        // construrctors
        TicTacToe();
        // destructor
        ~TicTacToe();

        // getters
        const char getPosition(const int &row, const int &col) const;

        const int getFreeSpaces() const;

        const char getWinner() const;

        // setters
        void setPosition(const int &row, const int &col, const char &position);

        // configuration methods
        void resetBoard();

        void playerMove();

        const int evaluate();

        const int minimax(const int &depth, const bool &isMax);

        const int findBestMovePosition();

        void pcMove();
        // utilities methods

        void printBoard();

        void printWinner();
};

#endif