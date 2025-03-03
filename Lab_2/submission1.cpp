#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include <utility>
using namespace std;

// vector<string> splitBySpaces(string input)
// {
//     vector<string> output;
//     int findSpace = input.find(" ");
//     output.push_back(input.substr(0, findSpace));
//     for (int i = 0; i < input.size(); i++)
//     {
//         if (isspace(input.at(i)))
//         {
//             output.push_back(input.substr(i + 1, 3));
//         }
//     }

//     return output;
// }

// vector<pair<int, int>> splitIntoDigits(string input)
// {
//     vector<pair<int, int>> cell;
//     vector<int> digits;
//     int allowsMoreDigits;
//     for (string word : splitBySpaces(input))
//     {
//         cout << word << endl;
//         allowsMoreDigits = 0;
//         for (char c : word)
//         {
//             if (!isdigit(c))
//             {
//                 allowsMoreDigits = 0;
//             }
//             if (isdigit(c))
//             {
//                 digits.push_back(c - '0');
//             }
//         }
//     }
//     for (int i = 0; i < digits.size() / 2; i++)
//     {
//         cell.push_back({digits[i + i], digits[i + i + 1]});
//     }
//     // for (int i = 0; i < cell.size(); i++)
//     // {
//     //     cout << cell[i].first << "," << cell[i].second << endl;
//     // }
//     return cell;
// }

// this wasn't really mentioned.
// changed to this way because old way didn't account for multiple digits
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
    int k;
    for (int i = 0; i < boardSize; i++)
    {
        k = i + 1;
        for (int j = 0; j < boardSizeAtI; j++)
        {
            // cout << "K: " << k << endl;
            if (boardSize == k)
            {
                // if it goes through all and doesn't find a dominanting row
                // any row that isn't k will dominate all other rows.
                // Last row dominates all other rows since it went through all iterations.
                // cout << "I DOMNINATED: " << i - 1 << endl;
                return i - 1;
            }
            if (board[i][j].first > board[k][j].first)
            {
                // cout << "COMES HERE?: " << j << endl;
                if (j == boardSizeAtI - 1)
                {
                    // cout << "K ROW IS DOMINANTED BY I's ROW: K: " << k << " I: " << i << endl;
                    return k;
                }
                continue;
            }
            else
            {
                break;
            }
            // k's row is dominiated by i
            // cout << "K DOMNINATED: " << k << endl;
            return k;
        }
    }
    return -1;
}

int columnDominated(vector<vector<pair<int, int>>> board)
{
    int boardSize = static_cast<int>(board.size());
    int boardSizeAtI = static_cast<int>(board[0].size());
    int k;
    for (int i = 0; i < boardSizeAtI; i++)
    {
        k = i + 1;
        for (int j = 0; j < boardSize; j++)
        {
            // cout << "COUNTERS: J " << j << " COUNTERS : I " << i << " BOARDSIZE: " << boardSize << " BOARDSIZEATI " << boardSizeAtI << endl;
            // cout << "III BOARD: " << board[j][i].second << " COMPARES: " << board[j][k].second << endl;
            if (k == boardSizeAtI)
            {
                // if it goes through all and doesn't find a dominanting row
                // any row that isn't k will dominate all other rows.
                // Last row dominates all other rows since it went through all iterations.
                // cout << "J DOMNINATES: " << j << endl;
                return j;
            }
            if (board[j][i].second > board[j][k].second)
            {
                // cout << "IN IF STATEMENT BOARD: " << board[j][i].second << " COMPARES: " << board[j][k].second << " J " << j << " I " << i << endl;
                // cout << "NEW BOARD" << board[j][k].second << endl;
                // cout << "COMES HERE?: " << j << endl;
                if (j == boardSize - 1)
                {
                    // cout << "K COL IS DOMINANTED BY I's COL: K: " << k << " I: " << i << endl;
                    return k;
                }
                continue;
            }
            else
            {
                break;
            }
            // k's row is dominiated by i
            // cout << "K DOMNINATED: " << k << endl;
            return k;
        }
    }
    return -1;
}

vector<vector<pair<int, int>>> elimination(vector<vector<pair<int, int>>> board, string rowOrColumn)
{

    int min = 1000;
    int minIndexI = -1;
    int minIndexJ = -1;
    int boardSize = static_cast<int>(board.size());
    int boardSizeAtI = static_cast<int>(board.size());

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSizeAtI; j++)
        {
            if (rowOrColumn == "row")
            {
                minIndexI = rowDominated(board);
                // if (board[i][j].first < min)
                // {
                //     minIndexJ = j;
                //     minIndexI = i;
                //     min = board[i][j].first;
                // }
            }
            if (rowOrColumn == "column")
            {
                // if (board[i][j].second < min)
                // {
                //     minIndexJ = j;
                //     minIndexI = i;
                //     min = board[i][j].second;
                // }
                minIndexJ = columnDominated(board);
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
    printBoard(elimination(board, "row"));
}