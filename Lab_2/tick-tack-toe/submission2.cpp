#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include <utility>
using namespace std;

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

void printBoard(string input)
{
    string board = formatBoard(input);
    for (int i = 0; i < board.size(); i++)
    {
        cout << board.at(i) << " ";
        if ((i + 1) % 3 == 0)
        {
            cout << endl;
        }
    }
    cout << endl;
}

int main()
{
    string input;
    cin >> input;
    printBoard(input);
}