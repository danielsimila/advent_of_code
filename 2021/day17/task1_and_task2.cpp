#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

void time_update(int &x, int &y, int &vx, int &vy)
{
    x += vx;
    y += vy;
    if (vx < 0)
    {
        vx += 1;
    }
    else if (vx > 0)
    {
        vx += -1;
    }
    vy += -1;
}

bool in_goal(int const &x, int const &y, int const &xmin, int const &xmax, int const &ymin, int const &ymax)
{
    return ((x >= xmin) and (x <= xmax) and (y >= ymin) and (y <= ymax));
}

int main()
{
    // ifstream file{"test.txt"};
    ifstream file{"input.txt"};
    string line{};
    int xmin{};
    int xmax{};
    int ymin{};
    int ymax{};

    while (getline(file, line))
    {
        stringstream ss{line};
        string trash;
        char bin;
        ss >> trash >> trash >> bin >> bin >> xmin;
        ss >> bin >> bin >> xmax;
        ss >> bin >> bin >> bin >> ymin;
        ss >> bin >> bin >> ymax;
    }
    int vxmin{int(ceil(0.5 * (sqrt(8 * xmin + 1) - 1)))}; // *note
    int vxmax{xmax};                                      // *note

    std::cout << "X  limits: " << xmin << ", " << xmax << endl;
    std::cout << "Y  limits: " << ymin << ", " << ymax << endl;
    std::cout << "Vx limits: " << vxmin << ", " << vxmax << endl;

    vector<int> maxheight{};
    for (int vyinit{-100}; vyinit < 100; vyinit++) // [-100, 100] is an assumption
    {
        for (int vxinit{vxmin}; vxinit <= vxmax; vxinit++) // *note: assumes positive dx from start->goal
        {
            int x{0};
            int y{0};
            int vx{vxinit};
            int vy{vyinit};
            int y_max{y};

            for (int steps{1}; steps <= 10000; steps++)
            {
                // Time update:
                time_update(x, y, vx, vy);

                if (y > y_max)
                {
                    y_max = y;
                }

                // Goal status:
                if (in_goal(x, y, xmin, xmax, ymin, ymax))
                {
                    maxheight.push_back(y_max);
                    break;
                }

                // Breaks if we have passed the goal
                if ((y < ymin) or (x > xmax))
                {
                    break;
                }
            }
        }
    }

    std::cout << "Ymax: " << (*max_element(begin(maxheight), end(maxheight))) << endl;
    std::cout << "Velocity Pairs: " << maxheight.size() << endl;

    return 0;
}