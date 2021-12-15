#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <iomanip>

using namespace std;

int heuristic(pair<int, int> const &current, pair<int, int> const &goal)
{
    return abs(current.first - goal.first) + abs(current.second - goal.second);
}

pair<int, pair<int, int>> make_pair(int const &x, int const &y, vector<vector<int>> const &cost, pair<int, int> const &goal)
{
    return pair<int, pair<int, int>>{cost[y][x] + heuristic(pair<int, int>{x, y}, goal), pair<int, int>{x, y}};
}

struct myComp
{
    constexpr bool operator()(
        pair<int, pair<int, int>> const &a,
        pair<int, pair<int, int>> const &b)
        const noexcept
    {
        return a.first > b.first;
    }
};

int main()
{
    ifstream file{"input.txt"};
    string line{};

    vector<vector<int>> risk{};
    while (getline(file, line))
    {
        vector<int> tmp{};
        int temp{};
        for (int i{0}; i < 5; i++)
        {
            for (char c : line)
            {
                temp = c - '0';
                temp += i;
                if (temp > 9)
                {
                    temp += -9;
                }
                tmp.push_back(temp);
            }
        }
        risk.push_back(tmp);
    }

    vector<vector<int>> risk_tmp{};
    for (int i{0}; i < 5; i++)
    {
        int temp{};
        for (auto row : risk)
        {
            vector<int> tmp{};
            for (int r : row)
            {
                temp = r + i;
                if (temp > 9)
                {
                    temp += -9;
                }
                tmp.push_back(temp);
            }
            risk_tmp.push_back(tmp);
        }
    }
    risk = risk_tmp;

    int max_y{int(risk.size())};
    int max_x{int(risk[0].size())};

    pair<int, int> goal{max_x - 1, max_y - 1};

    // A* search algorithm
    set<pair<int, int>> visited{};
    vector<vector<int>> cost(max_y, vector<int>(max_x, 0));
    vector<vector<pair<int, int>>> parent(max_y, vector<pair<int, int>>(max_x, pair<int, int>{-1, -1}));
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, myComp> Q{};
    vector<pair<int, int>> dirs{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    bool success{false};

    visited.insert(pair<int, int>{0, 0});
    parent[0][0] = pair<int, int>{-1, -1};
    cost[0][0] = 0;
    Q.push(make_pair(0, 0, cost, goal));
    while (!Q.empty())
    {
        pair<int, pair<int, int>> current{Q.top()};
        int x{current.second.first};
        int y{current.second.second};
        Q.pop();

        if (pair<int, int>{x, y} == goal)
        {
            success = true;
            break;
        }

        for (auto dir : dirs)
        {
            int xx{x + dir.first};
            int yy{y + dir.second};

            if ((xx < 0) or (xx >= max_x) or (yy < 0) or (yy >= max_y))
            {
                continue;
            }
            if ((visited.find(pair<int, int>{xx, yy}) == end(visited)) or
                (cost[yy][xx] > cost[y][x] + risk[yy][xx]))
            {
                visited.insert(pair<int, int>{xx, yy});
                parent[yy][xx] = pair<int, int>{x, y};
                cost[yy][xx] = cost[y][x] + risk[yy][xx];
                Q.push(make_pair(xx, yy, cost, goal));
            }
        }
    }

    cout << "Succes: " << success << endl;
    cout << "Total cost: " << cost[goal.second][goal.first] << endl;

    return 0;
}