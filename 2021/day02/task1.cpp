#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    ifstream file{"input.txt"};
    string line{};
    string direction{};
    int length{};

    int horizontal_pos{};
    int depth{};

    while (getline(file,line))
    {
        stringstream ss{line};
        ss >> direction >> length;
        if (direction == "forward")
        {
            horizontal_pos += length;
        }
        else if (direction == "up")
        {
            depth += -length;
        }
        else if (direction == "down")
        {
            depth += length;
        }
    }

    cout << "Final horizontal position: " << horizontal_pos << endl; 
    cout << "Final depth: " << depth << endl;
    cout << "Multiplied: " << horizontal_pos*depth << endl;

    return 0;
}