#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

int main()
{
    ifstream file{"input.txt"};
    string line{};
    char tmp{};
    int total{};
    vector<int> sums(12, 0);

    while (getline(file, line))
    {
        istringstream ss(line);
        for (uint i{0}; i < sums.size(); i++)
        {
            ss >> tmp;
            sums[i] += tmp - '0';
        }

        total += 1;
    }

    for (uint i{0}; i < sums.size(); i++)
    {
        sums[i] = sums[i] > (total - sums[i]);
    }

    double gamma{};
    double epsilon{};
    for (uint i{0}; i < sums.size(); i++)
    {
        gamma += sums[i] * pow((2 * sums[i]), (sums.size() - 1 - i));
        epsilon += !sums[i] * pow((2 * !sums[i]), (sums.size() - 1 - i));
    }

    cout << "Power consumption: " << int(gamma * epsilon) << endl;
    cout << "gamma: " << gamma << endl;
    cout << "epsilon: " << epsilon << endl;

    return 0;
}