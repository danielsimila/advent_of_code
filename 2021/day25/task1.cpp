#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void print(vector<vector<char>> const &seafloor)
{
    for (auto row : seafloor)
    {
        for (auto c : row)
        {
            cout << c;
        }
        cout << endl;
    }
    cout << endl;
}

void update(vector<vector<char>> &seafloor)
{
    int rows{int(seafloor.size())};
    int cols{int(seafloor[0].size())};

    // Move east:
    vector<vector<char>> copy{seafloor};
    for (int r{0}; (r + 1) <= rows; r++)
    {
        for (int c{0}; (c + 1) <= cols; c++)
        {
            if (copy[r][c] == '>') // East-facing...
            {
                // check next slot:
                if (((c + 1) < (cols)) and (copy[r][c + 1] == '.'))
                {
                    seafloor[r][c] = '.';
                    seafloor[r][c + 1] = '>';
                }
                else if (((c + 1) == (cols)) and (copy[r][0] == '.'))
                {
                    seafloor[r][c] = '.';
                    seafloor[r][0] = '>';
                }
            }
        }
    }

    // Move south:
    copy = seafloor;
    for (int c{0}; (c + 1) <= cols; c++)
    {
        for (int r{0}; (r + 1) <= rows; r++)
        {
            if (copy[r][c] == 'v') // South-facing...
            {
                // check next slot:
                if (((r + 1) < (rows)) and (copy[r + 1][c] == '.'))
                {
                    seafloor[r][c] = '.';
                    seafloor[r + 1][c] = 'v';
                }
                else if (((r + 1) == (rows)) and (copy[0][c] == '.'))
                {
                    seafloor[r][c] = '.';
                    seafloor[0][c] = 'v';
                }
            }
        }
    }
}

int main()
{
    ifstream file{"input.txt"};
    string line{};

    vector<vector<char>> seafloor{};
    while (getline(file, line))
    {
        vector<char> row{};
        for (char c : line)
        {
            row.push_back(c);
        }
        seafloor.push_back(row);
    }

    cout << "Initial Seafloor:" << endl;
    print(seafloor);

    bool same_as_before{false};
    int iter{};
    while ((!same_as_before) and (iter < 10000)) // Assuming max iterations less than 10000...
    {
        // Updating the seafloor:
        vector<vector<char>> copy{seafloor};
        update(seafloor);
        if (copy == seafloor)
        {
            same_as_before = true;
        }

        // Print, iterating etc:
        iter += 1;
        if ((iter % 100 == 0) or (same_as_before)) // Tune how often to print...
        {
            cout << "After " << iter << " iteration(s):" << endl;
            print(seafloor);
        }
    }

    cout << "ANSWER, PART 1: Static after " << iter << " iterations." << endl;

    return 0;
}