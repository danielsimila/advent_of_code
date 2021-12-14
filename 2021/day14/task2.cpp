#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

int main()
{
    // GATHERING INPUT:
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

    // Collecting pairs in input:
    map<string, long long int> polymor{};
    char prev{'X'};
    for (char c : input)
    {
        if (prev != 'X')
        {
            pair.erase(begin(pair), end(pair));
            pair.push_back(prev);
            pair.push_back(c);
            polymor[pair] += 1;
        }
        prev = c;
    }

    // SOLVING:
    int iter{1};
    for (; iter <= 40; iter++)
    {
        map<string, long long int> tmp{polymor};
        for (auto p : polymor)
        {
            // First pair
            pair.erase(begin(pair), end(pair));
            pair.push_back(p.first[0]);
            pair.push_back(pairs[p.first]);
            tmp[pair] += p.second;

            // Second pair
            pair.erase(begin(pair), end(pair));
            pair.push_back(pairs[p.first]);
            pair.push_back(p.first[1]);
            tmp[pair] += p.second;

            // Remove from modifed pair
            tmp[p.first] += -p.second;
        }
        polymor = tmp;
    }

    // Counting chars in the pairs:
    map<char, long long int> result{};
    result[input[0]] += 1;
    for (auto p : polymor)
    {
        result[p.first[1]] += p.second;
    }

    // Find max and min
    long long int maxcount{};
    long long int mincount{result[input[0]]};
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