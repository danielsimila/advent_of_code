#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    vector<int> v{};
    string tmp{};
    ifstream data("input.txt");

    while (getline(data, tmp))
    {
        v.push_back(stoi(tmp));
    }

    int previous_1{v[1]};
    int previous_2{v[0]};
    v.erase(v.begin());
    v.erase(v.begin());
    vector<int> v_sliding{};
    for (int i : v)
    {
        v_sliding.push_back(i + previous_1 + previous_2);
        previous_2 = previous_1;
        previous_1 = i;
    }

    int previous{};
    int no_of_increases{};
    bool first_iter{true};
    for (int i : v_sliding)
    {
        if ((i == v_sliding[0]) and (first_iter = true))
        {
            tmp = "(N/A - no previous measurement)";
            previous = i;
            first_iter = false;
        }
        else
        {
            if (i > previous)
            {
                tmp = "(increased)";
                no_of_increases += 1;
            }
            else 
            {
                tmp = "(decreased)";
            }
            previous = i;
        }
        cout << i << ' ' + tmp << endl;
    }

    cout << '\n' << "There are " << no_of_increases << " increases." << endl;

    return 0; 
}