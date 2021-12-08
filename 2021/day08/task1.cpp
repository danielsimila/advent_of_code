#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

int main()
{
    ifstream file{"test.txt"};
    string line{};
    string var{};
    map<int, int> output{}; 

    while (getline(file, line, '|'))
    {
        getline(file, line);
        stringstream ss{line};
        while (ss >> var)
        {
            output[int(var.size())] += 1;
        }
    }

    int count{output[2] + output[3] + output[4] + output[7]};

    cout << "Answer Part 1: " << count  << endl;

    return 0;
}