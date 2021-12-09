#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>

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

    // Finds basins
    vector<int> basins{};
    set<pair<int, int>> visited{};
    for (int row{0}; row < rows; row++)
    {
        for (int col{0}; col < cols; col++)
        {
            if (lowpoints[row][col] == 1)
            {
                queue<pair<int, int>> Q{};
                Q.push(pair<int, int>(row, col));
                visited.insert(pair<int, int>(row, col));
                int size{1};
                while (!Q.empty())
                {
                    pair<int, int> q{Q.front()};
                    Q.pop();
                    int rr{q.first};
                    int cc{q.second};
                    if (rr + 1 < rows)
                    {
                        if ((heatmap[rr + 1][cc] < 9) and (end(visited) == visited.find(pair<int, int>(rr + 1, cc))))
                        {
                            Q.push(pair<int, int>(rr + 1, cc));
                            visited.insert(pair<int, int>(rr + 1, cc));
                            size += 1;
                        }
                    }
                    // row-1
                    if (rr - 1 >= 0)
                    {
                        if ((heatmap[rr - 1][cc] < 9) and (end(visited) == visited.find(pair<int, int>(rr - 1, cc))))
                        {
                            Q.push(pair<int, int>(rr - 1, cc));
                            visited.insert(pair<int, int>(rr - 1, cc));
                            size += 1;
                        }
                    }
                    // col+1
                    if (cc + 1 < cols)
                    {
                        if ((heatmap[rr][cc + 1] < 9) and (end(visited) == visited.find(pair<int, int>(rr, cc + 1))))
                        {
                            Q.push(pair<int, int>(rr, cc + 1));
                            visited.insert(pair<int, int>(rr, cc + 1));
                            size += 1;
                        }
                    }
                    // col-1
                    if (cc - 1 >= 0)
                    {
                        if ((heatmap[rr][cc - 1] < 9) and (end(visited) == visited.find(pair<int, int>(rr, cc - 1))))
                        {
                            Q.push(pair<int, int>(rr, cc - 1));
                            visited.insert(pair<int, int>(rr, cc - 1));
                            size += 1;
                        }
                    }
                }

                basins.push_back(size);
            }
        }
    }

    sort(begin(basins), end(basins), [](int a, int b)
         { return a > b; });

    std::cout << "Answer: " << basins[0] * basins[1] * basins[2] << endl;

    return 0;
}