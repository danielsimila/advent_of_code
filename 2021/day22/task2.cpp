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

bool perform_instruction_on_cube_xyz(int const &z, vector<Instruction> const &instructions)
{
    bool on{false};
    for (Instruction i : instructions)
    {
        if ((z >= i.zlim[0]) and (z <= i.zlim[1]))
        {
            on = i.on;
        }
    }
    return on;
}

bool x_in_range(int const &x, vector<Instruction> &instructions)
{
    bool in_range{false};
    vector<Instruction> tmp{};
    for (Instruction i : instructions)
    {
        if ((x >= i.xlim[0]) and (x <= i.xlim[1]))
        {
            in_range = true;
            tmp.push_back(i);
        }
    }
    instructions = tmp;
    return in_range;
}

bool y_in_range(int const &y, vector<Instruction> &instructions)
{
    bool in_range{false};
    vector<Instruction> tmp{};
    for (Instruction i : instructions)
    {
        if ((y >= i.ylim[0]) and (y <= i.ylim[1]))
        {
            in_range = true;
            tmp.push_back(i);
        }
    }
    instructions = tmp;
    return in_range;
}

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

    // SOLVING:
    cout << "Starting solve!" << endl;
    // Finding limits, assumes < and > 0 :
    int xmin{};
    int xmax{};
    int ymin{};
    int ymax{};
    int zmin{};
    int zmax{};
    for (Instruction i : instructions)
    {
        // x:
        if (i.xlim[0] < xmin)
        {
            xmin = i.xlim[0];
        }
        if (i.xlim[1] > xmax)
        {
            xmax = i.xlim[1];
        }
        // y:
        if (i.ylim[0] < ymin)
        {
            ymin = i.ylim[0];
        }
        if (i.ylim[1] > ymax)
        {
            ymax = i.ylim[1];
        }
        // z:
        if (i.zlim[0] < zmin)
        {
            zmin = i.zlim[0];
        }
        if (i.zlim[1] > zmax)
        {
            zmax = i.zlim[1];
        }
    }

    unsigned long long on_cubes{};
    for (int x{xmin}; x <= xmax; x++)
    {
        if (x % 10 == 0)
        {
            cout << "At x = " << x << endl;
        }

        vector<Instruction> instructions_x{instructions};
        if (!x_in_range(x, instructions_x))
        {
            continue;
        }
        for (int y{ymin}; y <= ymax; y++)
        {
            vector<Instruction> instructions_xy{instructions_x};
            if (!y_in_range(y, instructions_xy))
            {
                continue;
            }
            for (int z{zmin}; z <= zmax; z++)
            {
                // Perform operation returns bool:
                if (perform_instruction_on_cube_xyz(z, instructions_xy))
                {
                    on_cubes += 1;
                }
            }
        }
    }

    cout << "Cubes that are on: " << on_cubes << endl;

    return 0;
}