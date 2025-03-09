#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include <utility>
using namespace std;

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

char formatPlayer(char player)
{
    if (player == '0')
    {
        return 'x';
    }
    return 'o';
}

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

vector<vector<char>> doMove(vector<vector<char>> board, char player_input, pair<int, int> move)
{
    char player = formatPlayer(player_input);
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

int main()
{
    // A,B,C
    // A -> 0 -> x
    // A -> 1 -> o
    // B,C is the row then the column

    // initalise consts
    string input;
    string input_moves;
    string gameState;
    char player;
    pair<int, int> move;
    vector<vector<char>> board;
    vector<vector<char>> new_board;

    // take in inputs, we need the ignore or the getline doesn't fire
    cin >> input;
    // cin.ignore();
    // getline(cin, input_moves);

    // set the first at for player, x or o
    // player = input_moves.at(0);
    // get the move position row and col
    // move = make_pair(static_cast<int>(input_moves.at(2) - '0'), static_cast<int>(input_moves.at(4) - '0'));

    board = makeBoard(input);
    // new_board = doMove(board, player, move);
    gameState = winCon(board);
    cout << gameState << endl;
    // printBoard(new_board);
    // printBoard(board);
}