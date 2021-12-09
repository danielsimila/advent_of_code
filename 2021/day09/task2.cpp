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

    // Finds low-points
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

    // Sets lowpoint as pairs
    vector<pair<int, int>> lowpoint_pairs{};
    for (int row{0}; row < rows; row++)
    {
        for (int col{0}; col < cols; col++)
        {
            if (lowpoints[row][col] == 1)
            {
                lowpoint_pairs.push_back(pair<int, int>{row, col});
            }
        }
    }

    // Exapnds basins for each lowpoint
    vector<vector<int>> basin(rows, vector<int>(cols, 0));
    vector<vector<int>> zeros{basin};
    vector<int> basins{};
    for (auto p : lowpoint_pairs)
    {
        int row{p.first};
        int col{p.second};
        basin[row][col] = 1;

        bool success{false};
        while (!success)
        {
            vector<vector<int>> basin_init{basin};
            for (int row{0}; row < rows; row++)
            {
                for (int col{0}; col < cols; col++)
                {
                    if (basin[row][col] == 1)
                    {
                        // row+1
                        if (row + 1 < rows)
                        {
                            if (heatmap[row + 1][col] < 9)
                            {
                                basin[row + 1][col] = 1;
                            }
                        }
                        // row-1
                        if (row - 1 >= 0)
                        {
                            if (heatmap[row - 1][col] < 9)
                            {
                                basin[row - 1][col] = 1;
                            }
                        }
                        // col+1
                        if (col + 1 < cols)
                        {
                            if (heatmap[row][col + 1] < 9)
                            {
                                basin[row][col + 1] = 1;
                            }
                        }
                        // col-1
                        if (col - 1 >= 0)
                        {
                            if (heatmap[row][col - 1] < 9)
                            {
                                basin[row][col - 1] = 1;
                            }
                        }
                    }
                }
            }

            if (basin_init == basin)
            {
                success = true;
            }
        }

        // This basin size:
        int size{};
        for (auto v : basin)
        {
            for (int i : v)
            {
                size += i;
            }
        }

        // Storing basin sizes...
        basins.push_back(size);

        // Iterating:
        basin = zeros;
    }

    sort(begin(basins), end(basins), [](int a, int b)
         { return a > b; });

    std::cout << "Answer: " << basins[0] * basins[1] * basins[2] << endl;

    return 0;
}