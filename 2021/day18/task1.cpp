#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class SnailfishNumber
{
public:
    SnailfishNumber(SnailfishNumber *prnt) : parent{prnt} {};
    int value{};
    SnailfishNumber *left{};
    SnailfishNumber *right{};
    SnailfishNumber *parent{};
};

pair<string, string> split2snailno(string line)
{
    pair<string, string> tmp{};
    line.erase(begin(line));
    line.erase(end(line) - 1);
    stringstream ss{line};
    getline(ss, tmp.first, ',');
    getline(ss, tmp.second);
    return tmp;
}

void read_snailno(string line, SnailfishNumber *parent)
{
    SnailfishNumber *left_snailno{parent};
    SnailfishNumber *right_snailno{parent};

    auto tmp{split2snailno(line)};
    int left{stoi(tmp.first)};
    int right{stoi(tmp.second)};

    cout << left << endl;
    cout << right << endl;

    left_snailno->value = left;
    right_snailno->value = right;
}

int main()
{
    ifstream file{"reading.txt"};
    string line{};

    vector<SnailfishNumber *> snailnumbers;
    while (getline(file, line))
    {
        SnailfishNumber *main{nullptr};
        read_snailno(line, main);
        snailnumbers.push_back(main);
    }

    return 0;
}