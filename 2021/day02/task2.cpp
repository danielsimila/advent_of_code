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
    int aim{};

    while (getline(file,line))
    {
        stringstream ss{line};
        ss >> direction >> length;
        if (direction == "forward")
        {
            horizontal_pos += length;
            depth += aim*length;
        }
        else if (direction == "up")
        {
            aim += -length;
        }
        else if (direction == "down")
        {
            aim += length;
        }
    }

    std::cout << "Final horizontal position: " << horizontal_pos << endl;
    std::cout << "Final depth: " << depth << endl;
    std::cout << "Multiplied: " << horizontal_pos*depth << endl;

    return 0;
}