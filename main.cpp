#include "TicTacToe.h"

int main(){

    char winner = ' ';
    char response = ' ';

    TicTacToe game;

    do
    {
        winner = ' ';
        response = ' ';

        game.resetBoard();

        while(winner == ' ' && game.getFreeSpaces() != 0)
        {
            
            game.printBoard();

            game.playerMove();

            winner = game.getWinner();

            if(winner != ' ' || game.getFreeSpaces() == 0)
            {
                break;
            }

            game.pcMove();

            winner = game.getWinner();

            if(winner != ' ' || game.getFreeSpaces() == 0)
            {
                break;
            }
        }

        game.printBoard();
        game.printWinner();

        std::cout << "\nWould you like to play again? (Y/N): " << std::endl;
        
        std::cin >> response;
        response = toupper(response);
    } while (response == 'Y');

    std::cout << "Thanks for playing!" ;
}