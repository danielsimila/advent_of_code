#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Octopus
{
public:
    Octopus(vector<vector<int>> v) : octopus{v}
    {
        rows = int(octopus.size());
        cols = int(octopus[0].size());
        for (int row{0}; row < rows; row++)
        {
            flashed.push_back(vector<bool>(cols, false));
        }
    };

    void print()
    {
        cout << "\n"
             << "Step: " << steps << ", Flashes: " << flashes << endl;
        for (auto vec : octopus)
        {
            for (int i : vec)
            {
                cout << i;
            }
            cout << endl;
        }
    }

    void flash(int row, int col)
    {
        int rr{};
        int cc{};
        for (auto p : moves)
        {
            rr = row + p.first;
            cc = col + p.second;
            if ((rr >= 0) and (rr < rows) and
                (cc >= 0) and (cc < cols))
            {
                octopus[rr][cc] += 1;
            }
        }
    }

    void update()
    {
        steps += 1;

        // First, the energy level of each octopus increases by 1
        for (int row{0}; row < rows; row++)
        {
            for (int col{0}; col < cols; col++)
            {
                octopus[row][col] += 1;
            }
        }

        // Flashes if > 9 and not flashed...
        bool flashing_done{false};
        while (!flashing_done)
        {
            vector<vector<bool>> tmp{flashed};
            for (int row{0}; row < rows; row++)
            {
                for (int col{0}; col < cols; col++)
                {
                    if ((octopus[row][col] > 9) and (!flashed[row][col]))
                    {
                        flash(row, col);
                        flashed[row][col] = true;
                    }
                }
            }
            if (tmp == flashed)
            {
                flashing_done = true;
            }
        }

        // Reset flahes and flashed octopuses
        bool all_flashed{true};
        for (int row{0}; row < rows; row++)
        {
            for (int col{0}; col < cols; col++)
            {
                if (octopus[row][col] > 9)
                {
                    octopus[row][col] = 0;
                }
                if (flashed[row][col])
                {
                    flashes += 1;
                }
                else
                {
                    all_flashed = false;
                }
                flashed[row][col] = false;
            }
        }

        if (all_flashed)
        {
            print();
            cout << "All flashed!" << endl;
        }
    }

    // Members:
    vector<vector<int>> octopus{};
    vector<vector<bool>> flashed{};
    vector<pair<int, int>> moves{
        {1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, 0}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
    int rows{};
    int cols{};
    int flashes{};
    int steps{};
};

int main()
{
    ifstream file{"input.txt"};
    string line{};
    char var{};

    vector<vector<int>> data{};

    while (getline(file, line))
    {
        stringstream ss{line};
        vector<int> vec{};
        int tmp{};
        while (ss >> var)
        {
            tmp = var - '0';
            vec.push_back(tmp);
        }
        data.push_back(vec);
    }

    Octopus octo(data);

    int iter_max{250};
    for (int iter{0}; iter <= iter_max; iter++)
    {
        if (iter == 100)
        {
            octo.print();
        }
        octo.update();
    }

    return 0;
}