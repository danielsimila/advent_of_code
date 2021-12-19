#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <set>

using namespace std;

class Scanner
{
public:
    bool position_set{false};
    vector<int> position{0, 0, 0};
    vector<vector<int>> readings{};
};

void add_beacons(Scanner const &scanner, set<vector<int>> &known_beacons)
{
    for (auto reading : scanner.readings)
    {
        known_beacons.insert(reading);
    }
}

void find_position(Scanner &scanner, set<vector<int>> const &known_beacons)
{
    // Assumes correct orientation:
    for (int i{}; i < 15; i++) // assumes max 25 readings per scanner
    {
        if (scanner.position_set)
        {
            break;
        }
        for (auto beacon : known_beacons)
        {
            int x_diff{beacon[0] - scanner.readings[i][0]};
            int y_diff{beacon[1] - scanner.readings[i][1]};
            int z_diff{beacon[2] - scanner.readings[i][2]};
            int counts{};
            for (auto reading : scanner.readings)
            {
                reading[0] += x_diff;
                reading[1] += y_diff;
                reading[2] += z_diff;
                if (known_beacons.find(reading) != end(known_beacons))
                {
                    counts += 1;
                }
            }
            if (counts >= 12) // 3, 6, or 12 depending on: position.txt, rotation.txt, test.txt/input.txt
            {
                scanner.position[0] = x_diff;
                scanner.position[1] = y_diff;
                scanner.position[2] = z_diff;
                scanner.position_set = true;
                for (auto &reading : scanner.readings)
                {
                    reading[0] += scanner.position[0];
                    reading[1] += scanner.position[1];
                    reading[2] += scanner.position[2];
                }
                break;
            }
        }
    }
}

void find_rotation_and_postion(Scanner &scanner, set<vector<int>> const &known_beacons)
{
    auto scanner_readings{scanner.readings};
    vector<pair<int, int>> dirs{{1, 0}, {1, 1}, {1, 2}, {-1, 0}, {-1, 1}, {-1, 2}};
    for (auto x : dirs)
    {
        for (auto y : dirs)
        {
            for (auto z : dirs)
            {
                if (scanner.position_set)
                {
                    break;
                }

                if ((x.second == y.second) or (x.second == z.second) or (y.second == z.second)) // do not need to check these...
                {
                    continue;
                }

                // Transposing measurements:
                for (auto &reading : scanner.readings)
                {
                    auto tmp{reading};
                    reading[0] = x.first * tmp[x.second];
                    reading[1] = y.first * tmp[y.second];
                    reading[2] = z.first * tmp[z.second];
                }

                // Finds position and breaks if successful:
                find_position(scanner, known_beacons);
                if (scanner.position_set)
                {
                    break;
                }

                scanner.readings = scanner_readings; // reset readings for next iteration
            }
        }
    }
}

int main()
{
    ifstream file{"test.txt"};
    string line{};
    vector<Scanner> scanners{};
    set<vector<int>> known_beacons;

    while (getline(file, line))
    {
        getline(file, line); // Overrides scanner info...

        int var{};
        char bin{};
        Scanner scanner{};

        while (line.size() != 0)
        {
            stringstream ss{line};
            vector<int> reading{};
            ss >> var >> bin;
            reading.push_back(var);
            ss >> var >> bin;
            reading.push_back(var);
            ss >> var;
            reading.push_back(var);

            scanner.readings.push_back(reading);

            getline(file, line);
        }

        scanners.push_back(scanner);
    }

    // First scanner:
    scanners[0].position = {0, 0, 0};
    scanners[0].position_set = true;
    add_beacons(scanners[0], known_beacons);

    // Finds positions of the rest of the scanners:
    for (int i{}; i < 10; i++) // assumes 10 iterations is enough...
    {
        cout << "Iteration " << i << ": " << flush;
        for (auto &scanner : scanners)
        {
            if (!scanner.position_set)
            {
                find_rotation_and_postion(scanner, known_beacons);
                if (scanner.position_set)
                {
                    add_beacons(scanner, known_beacons);
                }
            }

            // Printing:
            if (!scanner.position_set)
            {
                cout << "." << flush;
            }
            else
            {
                cout << "#" << flush;
            }
        }
        cout << endl;
    }

    // Finds max distance between all scanners:
    int maxdist{};
    for (auto scanner : scanners)
    {
        for (auto other : scanners)
        {
            int dist{};
            dist += abs(scanner.position[0] - other.position[0]);
            dist += abs(scanner.position[1] - other.position[1]);
            dist += abs(scanner.position[2] - other.position[2]);
            if (dist > maxdist)
            {
                maxdist = dist;
            }
        }
    }

    cout << "\n"
         << "ANSWERS: " << endl;
    cout << "Number of beacons : " << known_beacons.size() << endl;
    cout << "Maximum distance  : " << maxdist << endl;

    return 0;
}