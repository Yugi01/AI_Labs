#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include <utility>
using namespace std;

vector<pair<int, int>> splitIntoPairs(string input)
{
    vector<pair<int, int>> pairs;
    istringstream iss(input);
    string cell;

    while (iss >> cell)
    {
        int comma = cell.find(',');
        string firstNum = cell.substr(0, comma);
        string secondNum = cell.substr(comma + 1);
        pairs.push_back({stoi(firstNum), stoi(secondNum)});
    }
    return pairs;
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
    int boardSize = static_cast<int>(board.size());
    int boardSizeAtI = static_cast<int>(board[0].size());

    if (boardSizeAtI == 1)
    {
        if (board[0][0].first == board[1][0].first)
        {
            if (board[0][0].second >= board[1][0].second)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        if (board[0][0].first > board[1][0].first)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    for (int i = 0; i < boardSize; i++)
    {
        for (int k = i + 1; k < boardSize; k++)
        {
            for (int j = 0; j < boardSizeAtI; j++)
            {
                if (board[i][j].first > board[k][j].first)
                {
                    if (j == boardSizeAtI - 1)
                    {
                        return k;
                    }
                    continue;
                }
                else
                {
                    break;
                }
            }
            for (int j = 0; j < boardSizeAtI; j++)
            {
                if (board[i][j].first < board[k][j].first)
                {
                    if (j == boardSizeAtI - 1)
                    {
                        return i;
                    }
                    continue;
                }
                else
                {
                    break;
                }
            }
        }
    }

    cout << "NOT HERE?" << endl;
    return -1;
}

int columnDominated(vector<vector<pair<int, int>>> board)
{
    int boardSize = static_cast<int>(board.size());
    int boardSizeAtI = static_cast<int>(board[0].size());

    if (boardSize == 1)
    {
        if (board[0][1].second == board[0][0].second)
        {
            if (board[0][1].first >= board[0][0].first)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        if (board[0][1].second >= board[0][0].second)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    for (int i = 0; i < boardSizeAtI; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            for (int k = i + 1; k <= boardSizeAtI; k++)
            {
                if (board[j][i].second > board[j][k].second)
                {
                    if (j == boardSize - 1)
                    {
                        return k;
                    }
                    continue;
                }
                else
                {
                    break;
                }
            }

            for (int k = i + 1; k < boardSizeAtI; k++)
            {
                if (board[j][i].second < board[j][k].second)
                {
                    if (j == boardSize - 1)
                    {
                        return i;
                    }
                    continue;
                }
                else
                {
                    break;
                }
            }
        }
    }

    return -1;
}

vector<vector<pair<int, int>>> elimination(vector<vector<pair<int, int>>> board, string rowOrColumn)
{

    int minIndexI = -1;
    int minIndexJ = -1;
    int boardSize = static_cast<int>(board.size());
    int boardSizeAtI = static_cast<int>(board[0].size());

    if (rowOrColumn == "row")
    {
        minIndexI = rowDominated(board);
    }
    else
    {
        minIndexJ = columnDominated(board);
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
            board = elimination(board, "column");
        }
        else
        {
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
        board[i] = splitIntoPairs(input[i + 1]);
    }
    // columnDominated(board);
    if (board.size() == 1 && board[0].size() == 1)
    {
        printBoard(board);
    }
    else
    {
        printBoard(elimination(board, "row"));
    }
}