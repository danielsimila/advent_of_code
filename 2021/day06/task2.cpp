#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Stim
{
public:
    Stim() : fish{0,0,0,0,0,0,0,0,0} {}

    void add_fish(int val)
    {
        fish[val] += 1;
    }

    void update()
    {
        unsigned long long fish_at_zero{fish[0]};
        for (int i{0}; i < 8; i++)
        {
            fish[i] = fish[i+1];
        }
        fish[6] += fish_at_zero;
        fish[8] = fish_at_zero;
    }

    void print()
    {
        cout << "Stim: ";
        for (auto i : fish)
        {
            cout << i << ',';
        }
        cout << endl;
    }

    unsigned long long size()
    {
        unsigned long long sum{};
        for (auto i : fish)
        {
            sum += i;
        }
        return sum;
    }

    vector<unsigned long long> fish;
};

int main()
{
    ifstream file{"input.txt"};
    string input{};
    getline(file,input);

    Stim stim{};

    stringstream ss{input};
    int var{};
    char trash;
    while (ss >> var >> trash)
    {
        stim.add_fish(var);
    }

    // For days:
    int iter{256};
    for (int i{0}; i < iter; i++)
    {
        stim.update();
    }

    cout << "Answer: After " << iter << " days, there are " << stim.size() << " fish" << endl;

    return 0;
}