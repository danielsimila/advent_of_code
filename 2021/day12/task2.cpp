#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <stack>

using namespace std;

class Cave
{
public:
    string name{};
    bool big_cave{};
    bool start_end{};
    vector<Cave *> connections{};
};

int main()
{
    ifstream file{"input.txt"};
    string line{};
    string cave1{};
    string cave2{};

    map<string, Cave> cavesystem{};
    while (getline(file, line))
    {
        stringstream ss{line};
        getline(ss, cave1, '-');
        getline(ss, cave2);

        // Checking/Adding caves to system:
        vector<string> caves{cave1, cave2};
        for (string cave : caves)
        {
            if (cavesystem.find(cave) == end(cavesystem))
            {
                Cave tmp{};
                tmp.name = cave;
                tmp.big_cave = false;
                tmp.start_end = false;
                if ((tmp.name == "start") or (tmp.name == "end"))
                {
                    tmp.start_end = true;
                }
                if (isupper(tmp.name[0]))
                {
                    tmp.big_cave = true;
                }
                cavesystem[tmp.name] = tmp;
            }
        }

        // Adding the connections:
        cavesystem[cave1].connections.push_back(&cavesystem[cave2]);
        cavesystem[cave2].connections.push_back(&cavesystem[cave1]);
    }

    // visited caves
    stack<vector<Cave *>> path;
    path.push(vector<Cave *>{&cavesystem["start"]});

    int sum{};
    while (!path.empty())
    {
        vector<Cave *> visited{path.top()};
        Cave *current{visited.back()};
        path.pop();

        if (current->name == "end")
        {
            sum += 1;
        }
        for (auto next : current->connections)
        {
            bool already_visited{false};
            int times_visited{};
            times_visited = count_if(begin(visited), end(visited),
                                     [&next](Cave *vis)
                                     {
                                         return (vis->name == next->name);
                                     });

            // Checking if any small cave visited twice:
            map<string, int> visits{};
            for (auto ptr : visited)
            {
                if (!ptr->big_cave)
                {
                    visits[ptr->name] += 1;
                }
            }
            int max_visits{};
            for (auto p : visits)
            {
                if (p.second > max_visits)
                {
                    max_visits = p.second;
                }
            }
            int correction{};
            if (max_visits == 2)
            {
                correction = 1;
            }

            // Small caves:
            if ((times_visited >= 2 - correction) and (!next->big_cave))
            {
                already_visited = true;
            }
            // Start or goal:
            if ((times_visited >= 1) and (next->start_end))
            {
                already_visited = true;
            }

            if (!already_visited)
            {
                vector<Cave *> tmp{visited};
                tmp.push_back(next);
                path.push(tmp);
            }
        }
    }

    cout << "Sum: " << sum << endl;

    return 0;
}