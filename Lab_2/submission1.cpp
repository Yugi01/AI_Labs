#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <cctype>
using namespace std;

vector<string> splitBySpaces(string input)
{
    int index = 0;
    vector<string> output;
    output.push_back(input.substr(0, 3));
    for (int i = 0; i < input.size(); i++)
    {
        if (isspace(input.at(i)))
        {
            index = i;
            output.push_back(input.substr(index + 1, 3));
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
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            cout << board[i][j].first << "" << board[i][j].second << " ";
        }
        cout << endl;
    }
}

// void elimination(vector<vector<pair<int, int>>> board)
// {
// }

int main()
{
    int numberOfLines;
    cin >> numberOfLines;
    vector<string> input;
    vector<string> row;
    vector<vector<pair<int, int>>> board;

    for (int i = 0; i <= numberOfLines; i++)
    {
        string line = "";
        getline(cin, line);
        input.push_back(line);
    }

    for (int i = 0; i <= input.size(); i++)
    {
        board.push_back(splitIntoDigits(input[i]));
    }

    printBoard(board);
}