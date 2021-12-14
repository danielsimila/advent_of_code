#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

int main()
{
    ifstream file{"input.txt"};

    string input{};
    getline(file, input);

    string line{};
    string pair{};
    string trash{};
    char between{};
    map<string, char> pairs{};
    while (getline(file, line))
    {
        stringstream ss{line};
        ss >> pair >> trash >> between;

        pairs[pair] = between;
    }

    int iter{1};
    for (; iter <= 10; iter++)
    {
        string tmp{};
        char prev{'X'};
        for (char c : input)
        {
            if (prev != 'X')
            {
                pair.erase(begin(pair), end(pair));
                pair.push_back(prev);
                pair.push_back(c);
                tmp.push_back(prev);
                tmp.push_back(pairs[pair]);
            }
            prev = c;
        }
        tmp.push_back(prev);
        input = tmp;
    }

    map<char, int> result{};
    for (char c : input)
    {
        result[c] += 1;
    }
    int maxcount{};
    int mincount{result[input[0]]};
    for (auto p : result)
    {
        if (p.second > maxcount)
        {
            maxcount = p.second;
        }
        else if (p.second < mincount)
        {
            mincount = p.second;
        }
    }

    cout << "After " << iter - 1 << " iterations: " << maxcount - mincount << endl;

    return 0;
}