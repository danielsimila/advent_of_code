#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    ifstream file{"input.txt"};
    string line{};

    vector<vector<int>> heatmap{};
    vector<vector<int>> lowpoints{};
    while (getline(file, line))
    {
        vector<int> tmp;
        vector<int> ones;
        transform(begin(line), end(line), back_inserter(tmp),
                  [](char c)
                  {
                      int i{c - '0'};
                      return i;
                  });
        transform(begin(line), end(line), back_inserter(ones),
                  [](char)
                  {
                      return 1;
                  });
        heatmap.push_back(tmp);
        lowpoints.push_back(ones);
    }

    int rows{int(heatmap.size())};
    int cols{int(heatmap[0].size())};

    // Finding the lowpoints:
    for (int row{0}; row < rows; row++)
    {
        for (int col{0}; col < cols; col++)
        {
            int val{heatmap[row][col]};
            // row+1
            if (row + 1 < rows)
            {
                if (heatmap[row + 1][col] <= val)
                {
                    lowpoints[row][col] = 0;
                }
            }
            // row-1
            if (row - 1 >= 0)
            {
                if (heatmap[row - 1][col] <= val)
                {
                    lowpoints[row][col] = 0;
                }
            }
            // col+1
            if (col + 1 < cols)
            {
                if (heatmap[row][col + 1] <= val)
                {
                    lowpoints[row][col] = 0;
                }
            }
            // col-1
            if (col - 1 >= 0)
            {
                if (heatmap[row][col - 1] <= val)
                {
                    lowpoints[row][col] = 0;
                }
            }
        }
    }

    // Finding risk:
    int risk{};
    for (int row{0}; row < rows; row++)
    {
        for (int col{0}; col < cols; col++)
        {
            if (lowpoints[row][col] == 1)
            {
                risk += heatmap[row][col] + 1;
            }
        }
    }

    cout << "Risk: " << risk << endl;

    return 0;
}