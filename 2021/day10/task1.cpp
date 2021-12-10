#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int main()
{
    ifstream file{"input.txt"};
    string line{};
    char var{};

    map<char, int> score{};
    score[')'] = 3;
    score[']'] = 57;
    score['}'] = 1197;
    score['>'] = 25137;

    vector<char> illegal_chars{};
    vector<string> corrupted{};
    vector<string> incomplete{};
    string const openchars{"([{<"};
    string const closechars{")]}>"};
    map<char, char> open2close{};
    open2close[')'] = '(';
    open2close[']'] = '[';
    open2close['}'] = '{';
    open2close['>'] = '<';

    while (getline(file, line))
    {
        stringstream ss{line};
        deque<char> Q;

        while (ss >> var)
        {
            if (openchars.find(var) != std::string::npos)
            {
                Q.push_back(var);
            }
            else // if (closechars.find(var) != std::string::npos)
            {
                char c{Q.back()};
                if (c != open2close[var])
                {
                    corrupted.push_back(line);
                    illegal_chars.push_back(var);
                    Q.pop_back();
                    break;
                }
                else
                {
                    Q.pop_back();
                }
            }
        }
    }

    int sum{};
    for (char c : illegal_chars)
    {
        sum += score[c];
    }
    cout << "Score: " << sum << endl;

    return 0;
}