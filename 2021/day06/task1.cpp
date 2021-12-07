#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Fish
{
public:
    Fish(int val) : timer{val} {}

    bool update()
    {
        timer += -1;
        if (timer == -1)
        {
            timer = 6;
            return true;
        }
        return false;
    }

    int timer{};
};

int main()
{
    ifstream file{"input.txt"};
    string input{};
    getline(file,input);

    vector<Fish*> fish{};

    stringstream ss{input};
    int var{};
    char trash;
    while (ss >> var >> trash)
    {
        fish.push_back(new Fish {var});
    }

    // For days:
    int iter{80};
    for (int i{0}; i < iter; i++)
    {
        // Update and add fish: 
        vector<Fish*> new_fish{};
        for (auto f : fish)
        {
            if (f->update()) // f.update updates fish f as well
            {
                new_fish.push_back(new Fish{8});
            }
        }
        copy(begin(new_fish),end(new_fish),back_inserter(fish));
    }

    cout << "Answer: After " << iter << " days, there are " << fish.size() << " fish" << endl;

    for (auto f : fish)
    {
        delete f;
    }

    return 0;
}