#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include <utility>
#include <algorithm>
using namespace std;

char PLAYER;

pair<int, int> formatMoves(string moves)
{
    pair<int, int> move;
}

string formatBoard(string input)
{
    string output = "";
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == '.')
        {
            output += "_";
            continue;
        }
        output += input[i];
    }
    return output;
}

// char formatPlayer(char player)
// {
//     if (player == '0')
//     {
//         return 'x';
//     }
//     return 'o';
// }

void printBoard(vector<vector<char>> board)
{

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<char>> makeBoard(string input)
{
    vector<vector<char>> output(3, vector<char>(3));
    string board = formatBoard(input);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            output[i][j] = board.at(i * 3 + j);
        }
    }
    return output;
}

vector<vector<char>> doMove(vector<vector<char>> board, char player, pair<int, int> move)
{
    // char player = formatPlayer(player_input);
    board[move.first][move.second] = player;
    return board;
}

string winCon(vector<vector<char>> board)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] != '_' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            return string(1, (char)toupper(board[0][i])) + " wins";
        }
        else if (board[i][0] != '_' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            return string(1, (char)toupper(board[i][0])) + " wins";
        }
    }
    if (board[0][0] != '_' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        return string(1, (char)toupper(board[0][0])) + " wins";
    }
    if (board[0][2] != '_' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        return string(1, (char)toupper(board[0][2])) + " wins";
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '_')
            {
                return "In progress";
            }
        }
    }

    return "Draw";
}

char getPlayersTurn(vector<vector<char>> board)
{
    int os = 0;
    int xs = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 'x')
            {
                xs++;
                continue;
            }
            if (board[i][j] == 'o')
            {
                os++;
                continue;
            }
        }
    }

    if (xs == os)
    {
        return 'x';
    }
    return 'o';
}

vector<pair<int, int>> availableMoves(vector<vector<char>> board)
{
    vector<pair<int, int>> available;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '_')
            {
                available.push_back(make_pair(i, j));
            }
        }
    }
    return available;
}

int minimax(vector<vector<char>> board, char player, bool isMaxing)
{

    char opp = (player == 'x') ? 'o' : 'x';

    if ((winCon(board) == "X wins" && PLAYER == 'x') || ((winCon(board) == "O wins" && PLAYER == 'o')))
    {
        return 1;
    }
    if ((winCon(board) == "O wins" && PLAYER == 'x') || (winCon(board) == "X wins" && PLAYER == 'o'))
    {
        return -1;
    }
    if (winCon(board) == "Draw")
    {
        return 0;
    }
    // maxing
    if (isMaxing)
    {
        int eval = -100;
        vector<pair<int, int>> available = availableMoves(board);
        for (auto move : available)
        {
            vector<vector<char>> newBoard = doMove(board, player, move);
            int score = minimax(newBoard, opp, false);
            eval = max(eval, score);
        }
        return eval;
    }
    else // mining
    {
        int eval = 100;
        vector<pair<int, int>> available = availableMoves(board);
        for (auto move : available)
        {
            vector<vector<char>> newBoard = doMove(board, player, move);
            int score = minimax(newBoard, opp, true);
            eval = min(eval, score);
        }
        return eval;
    }
    return -100;
}

int main()
{
    // initalise consts
    string input;
    char player;
    vector<vector<char>> board;

    // take in inputs, we need the ignore or the getline doesn't fire
    cin >> input;

    board = makeBoard(input);
    player = getPlayersTurn(board);
    char opp = (player == 'x') ? 'o' : 'x';
    PLAYER = player;
    int score = minimax(board, player, true);

    if (score == 1)
    {
        cout << string(1, toupper(player)) << " wins" << endl;
    }
    else if (score == -1)
    {
        cout << string(1, toupper(opp)) << " wins" << endl;
    }
    else
    {
        cout << "Draw" << endl;
    }
    // gameState = winCon(board);
    // cout << gameState << endl;
}