#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

int main()
{
    ifstream file{"input.txt"};
    string line{};
    getline(file, line);

    map<int, int> numbers{};

    stringstream ss{line};
    int var{};
    char trash;
    int max{};
    while (ss >> var >> trash)
    {
        numbers[var] += 1;
        if (var > max)
        {
            max = var;
        }
    }

    int min{-1};
    for (int i{}; i <= max; i++)
    {
        int sum{};
        for (auto p : numbers)
        {
            sum += abs(p.first - i) * p.second;
        }
        if ((sum < min) or (min < 0))
        {
            min = sum;
        }
    }

    cout << "Min sum: " << min << endl;

    return 0;
}