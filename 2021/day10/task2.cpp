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

    map<char, int> SCORE{};
    SCORE[')'] = 1;
    SCORE[']'] = 2;
    SCORE['}'] = 3;
    SCORE['>'] = 4;

    vector<char> illegal_chars{};
    vector<vector<char>> completing_chars{};
    vector<string> corrupted{};
    vector<string> incomplete{};

    string const openchars{"([{<"};
    string const closechars{")]}>"};

    map<char, char> close2open{};
    close2open[')'] = '(';
    close2open[']'] = '[';
    close2open['}'] = '{';
    close2open['>'] = '<';

    map<char, char> open2close{};
    open2close['('] = ')';
    open2close['['] = ']';
    open2close['{'] = '}';
    open2close['<'] = '>';

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
                if (Q.back() != close2open[var])
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

        if ((corrupted.empty()) or (line != corrupted.back()))
        {
            incomplete.push_back(line);
            vector<char> rest_of_queue{};
            while (!Q.empty())
            {
                rest_of_queue.push_back(open2close[Q.back()]);
                Q.pop_back();
            }
            completing_chars.push_back(rest_of_queue);
        }
    }

    int sum{};
    for (char c : illegal_chars)
    {
        sum += score[c];
    }
    cout << "Score Part 1: " << sum << endl;

    vector<unsigned long long> SUMS{};
    for (auto vec : completing_chars)
    {
        unsigned long long SUM{};
        for (char c : vec)
        {
            SUM = SUM * 5;
            SUM += SCORE[c];
        }
        SUMS.push_back(SUM);
    }

    sort(begin(SUMS), end(SUMS));
    cout << "Score Part 2: " << SUMS[int(SUMS.size() / 2)] << endl;

    return 0;
}