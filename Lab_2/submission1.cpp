#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <cctype>
using namespace std;

vector<string> splitBySpaces(string input)
{
    vector<string> output;
    output.push_back(input.substr(0, 3));
    for (int i = 0; i < input.size(); i++)
    {
        if (isspace(input.at(i)))
        {
            output.push_back(input.substr(i + 1, 3));
        }
    }

    return output;
}

vector<pair<int, int>> splitIntoDigits(string input)
{
    vector<pair<int, int>> cell;
    vector<int> digits;
    for (string word : splitBySpaces(input))
    {
        for (char c : word)
        {
            if (isdigit(c))
            {
                digits.push_back(c - '0');
            }
        }
    }
    for (int i = 0; i < digits.size() / 2; i++)
    {
        cell.push_back({digits[i + i], digits[i + i + 1]});
    }
    return cell;
}

void printBoard(vector<vector<pair<int, int>>> board)
{
    for (int i = 0; i < static_cast<int>(board.size()); i++)
    {
        for (int j = 0; j < static_cast<int>(board[i].size()); j++)
        {
            cout << board[i][j].first << "," << board[i][j].second << " ";
        }
        cout << endl;
    }
}

int rowDominated(vector<vector<pair<int, int>>> board)
{

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] > board[i][j] && board[0][j] > board[i][j + 1])
        }
    }
    return -1;
}

vector<vector<pair<int, int>>> elimination(vector<vector<pair<int, int>>> oldBoard, string rowOrColumn)
{

    int min = 1000;
    int minIndexI = -1;
    int minIndexJ = -1;
    vector<vector<pair<int, int>>> board = oldBoard;
    int boardSize = static_cast<int>(board.size());
    int boardSizeAtI = static_cast<int>(board.size());
    cout << "ROW OR COLUMN " << rowOrColumn << endl;
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSizeAtI; j++)
        {
            if (rowOrColumn == "row")
            {
                if (board[i][j] > board[i + 1][j] && board[i][j] > board[i + 1][j + 1] &&)
                    if (board[i][j].first < min)
                    {
                        minIndexJ = j;
                        minIndexI = i;
                        min = board[i][j].first;
                    }
            }
            if (rowOrColumn == "column")
            {
                if (board[i][j].second < min)
                {
                    minIndexJ = j;
                    minIndexI = i;
                    min = board[i][j].second;
                }
            }
        }
    }

    if (rowOrColumn == "row")
    {
        board.erase(board.begin() + minIndexI);
    }
    else
    {
        for (int i = boardSize - 1; i >= 0; i--)
        {
            board[i].erase(next(board[i].begin(), minIndexJ));
        }
    }

    if (!(board.size() == 1 && board[0].size() == 1))
    {
        if (rowOrColumn == "row")
        {

            cout << endl;
            printBoard(board);
            cout << endl;
            board = elimination(board, "column");
        }
        else
        {
            cout << endl;
            printBoard(board);
            cout << endl;
            board = elimination(board, "row");
        }
    }
    return board;
}

int main()
{
    int numberOfLines;
    cin >> numberOfLines;
    vector<string> input;
    vector<string> row;
    vector<vector<pair<int, int>>> board(numberOfLines);

    for (int i = 0; i <= numberOfLines; i++)
    {
        string line = "";
        getline(cin, line);
        input.push_back(line);
    }

    for (int i = 0; i < input.size() - 1; i++)
    {
        board[i] = splitIntoDigits(input[i + 1]);
    }

    printBoard(elimination(board, "column"));
}