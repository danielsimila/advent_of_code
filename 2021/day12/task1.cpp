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
    stack<pair<Cave *, map<string, int>>> path;
    map<string, int> visits{};
    visits["start"] += 1;
    path.push(pair<Cave *, map<string, int>>{&cavesystem["start"], visits});

    int sum{};
    while (!path.empty())
    {
        map<string, int> visited{path.top().second};
        Cave *current{path.top().first};
        path.pop();

        if (current->name == "end")
        {
            sum += 1;
            continue;
        }

        for (auto next : current->connections)
        {
            if (!next->big_cave)
            {
                int times_visited{visited[next->name]};

                // Small caves
                if (times_visited >= 1)
                {
                    continue;
                }
            }

            visited[next->name] += 1;
            path.push(pair<Cave *, map<string, int>>{
                next, visited});
            visited[next->name] += -1;
        }
    }

    cout << "Sum: " << sum << endl;

    return 0;
}