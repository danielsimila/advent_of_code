#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    ifstream file{"input.txt"};
    string line{};
    int var{};

    while (getline(file,line))
    {
        stringstream ss{line};
        ss >> var; // variable to load to
        // code
    }

    return 0;
}