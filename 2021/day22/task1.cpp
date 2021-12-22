// EASY SOLUTION I KNOW WONT WORK FOR PART 2 ...
// 1 gold star is enough for today!

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Instruction
{
public:
    // Members:
    bool on{};
    vector<int> xlim{0, 0};
    vector<int> ylim{0, 0};
    vector<int> zlim{0, 0};
};

int main()
{
    ifstream file{"inputpart1.txt"};
    string line{};

    vector<Instruction> instructions{};
    string onoff{};
    char trash{};
    int minlim{};
    int maxlim{};
    while (getline(file, line))
    {
        stringstream ss{line};
        Instruction instruction{};

        // On or off:
        ss >> onoff >> trash >> trash;
        if (onoff == "on")
        {
            instruction.on = true;
        }
        else
        {
            instruction.on = false;
        }

        // xlim:
        ss >> minlim >> trash >> trash >> maxlim;
        instruction.xlim[0] = minlim;
        instruction.xlim[1] = maxlim;

        // ylim:
        ss >> trash >> trash >> trash >> minlim >> trash >> trash >> maxlim;
        instruction.ylim[0] = minlim;
        instruction.ylim[1] = maxlim;

        // zlim:
        ss >> trash >> trash >> trash >> minlim >> trash >> trash >> maxlim;
        instruction.zlim[0] = minlim;
        instruction.zlim[1] = maxlim;

        instructions.push_back(instruction);
    }

    // Solving:
    set<vector<int>> on_cubes{};
    int count{0};
    for (Instruction i : instructions)
    {
        for (int x{i.xlim[0]}; x <= i.xlim[1]; x++)
        {
            for (int y{i.ylim[0]}; y <= i.ylim[1]; y++)
            {
                for (int z{i.zlim[0]}; z <= i.zlim[1]; z++)
                {
                    if (i.on)
                    {
                        on_cubes.insert(vector<int>{x, y, z});
                    }
                    else
                    {
                        auto it{on_cubes.find(vector<int>{x, y, z})};
                        if (it != end(on_cubes))
                        {
                            on_cubes.erase(it);
                        }
                    }
                }
            }
        }
        count += 1;
        cout << "Instruction " << count << " done..." << endl;
    }

    cout << "Cubes that are on: " << on_cubes.size() << endl;

    return 0;
}