#include <iostream>
#include <string>
#include <map>
#include <queue>

using namespace std;

void print(char board[3][3]);
void play(char board[3][3]);
bool checkWinner(char board[3][3]);
int whowin(char board[3][3]);
int minimax(char board[3][3], int depth, bool isMaximizing, bool firstTime = true);
char player = 'O';

int main()
{
    cout << "\t\t\t    ~~~ Welcome to the [ X & O ] 3D game ~~~" << endl;
    for(int j = 0 ; j < 3 ; j++)
    {
        system("cls");
        char board [3][3] =  { {' ',' ',' '} , {' ',' ',' '} , {' ',' ',' '} };
        cout << "        ~~~   ROUND [" << j+1 << "]  ~~~ \n\n press ( 1 ) to start the game : ";
        int s;
        cin >> s;
        if (s == 1)
        {
            print(board);
            for (int k = 0 ; k < 9 ; k++)
            {
                play(board);
                print(board);
                if (checkWinner(board))
                {
                    cout << player << " is the winner :) . \n ~ Press any key to move to next. :) . ";
                    break;
                }
                else if(k == 8)
                    cout << " \n\t    ): ~~ tie ~~ :( \n ~ Press any key to move to next. :) . ";
            }
            char a;
            cin >> a;
        }
    }
    return 0;
}

void print(char board[3][3])
{
    system("cls");
    cout << "\n\n\t      || C:1 || C:2 || C:3 | " << "\n\t  __________________________\n\n";
    for (int j = 0 ; j < 3 ; j++)
    {
        cout << " \t  R:" << j+1 << " |";
        for (int k = 0 ; k < 3 ; k++)
        {
                cout << "|  " << board[j][k] << "  |";
        }
        cout << "\n\t  __________________________\n\n";
    }
}

void play(char board[3][3])
{
    if(player == 'O')
    {
        player = 'X';
        int r,c;
        cout << "Player [X] : \n\t Enter the (Row number & Column number) : ";
        cin >> r >> c;
        while( r > 3 || c > 3 || r < 1 || c < 1 || board[r-1][c-1] == 'X' || board[r-1][c-1] == 'O')
        {
            cout << " ~ Sorry, The wrong row or column number (must be between 1 and 3) :( ";
            cout << "\n Enter the (Row number & Column number) : ";
            cin >> r >> c;
        }
        board[r-1][c-1] = 'X';
    }
    else if(player == 'X')
    {
        player = 'O';
        int result = minimax(board, 9, false);
    }
}

bool checkWinner(char board[3][3])
{
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    for (int i = 0 ; i < 3 ; i++)
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
    for (int j = 0 ; j < 3 ; j++)
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
            return true;
    return false;
}

int whowin(char board[3][3])
{
    if(player == 'X' && checkWinner(board) == true)
        return 2;
    if(player == 'O' && checkWinner(board) == true)
        return -2;

    bool tie = true;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(board[i][j] == ' ')
                tie = false;
    if(tie)
        return 0;

    return 1;
}

int minimax(char board[3][3], int depth, bool isMaximizing, bool firstTime )
{
    int result = whowin(board);
    if(depth == 0 || result != 1)
        return result;

    if(isMaximizing)
    {
        player = 'X';
        int finalScore = -10;
        int finalI, finalJ;
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                if(board[i][j] == ' ')
                {
                    board[i][j] = 'X';
                    int score = minimax(board, depth - 1, false, false);
                    board[i][j] = ' ';
                    if(score > finalScore)
                    {
                        finalScore = score;
                        finalI = i;
                        finalJ = j;
                    }
                }
        if(firstTime)
        {
            player = 'O';
            board[finalI][finalJ] = 'O';
        }
        return finalScore;
    }

    else
    {
        player = 'O';
        int finalScore = 10;
        int finalI, finalJ;
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                if(board[i][j] == ' ')
                {
                    board[i][j] = 'O';
                    int score = minimax(board, depth - 1, true, false);
                    board[i][j] = ' ';
                    if(score < finalScore)
                    {
                        finalScore = score;
                        finalI = i;
                        finalJ = j;
                    }
                }
        if(firstTime)
        {
            player = 'O';
            board[finalI][finalJ] = 'O';
        }
        return finalScore;
    }
}
