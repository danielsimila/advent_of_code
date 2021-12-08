#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

int main()
{
    ifstream file{"input.txt"};
    string line{};
    string var{};

    int total_sum{};
    bool search{true};
    while (search)
    {
        vector<string> input{};
        vector<string> output{};

        while (getline(file, line, '|'))
        {
            // Input handling:
            stringstream ss1{line};
            while (ss1 >> var)
            {
                input.push_back(var);
            }

            // Output handling:
            getline(file, line);
            stringstream ss2{line};
            while (ss2 >> var)
            {
                output.push_back(var);
            }
            break;
        }

        // Sorting words in alphabetical order:
        transform(begin(input), end(input), begin(input),
                  [](string s)
                  {
                      sort(begin(s), end(s));
                      return s;
                  });
        transform(begin(output), end(output), begin(output),
                  [](string s)
                  {
                      sort(begin(s), end(s));
                      return s;
                  });

        map<int, string> coupled{};
        vector<string> input_left{input};

        // Finds 1, 4, 7, 8
        for (string s : input)
        {
            if (s.size() == 2)
            {
                coupled[1] = s;
                auto it{remove(begin(input_left), end(input_left), s)};
                input_left.erase(it, end(input_left));
            }
            else if (s.size() == 3)
            {
                coupled[7] = s;
                auto it{remove(begin(input_left), end(input_left), s)};
                input_left.erase(it, end(input_left));
            }
            else if (s.size() == 4)
            {
                coupled[4] = s;
                auto it{remove(begin(input_left), end(input_left), s)};
                input_left.erase(it, end(input_left));
            }
            else if (s.size() == 7)
            {
                coupled[8] = s;
                auto it{remove(begin(input_left), end(input_left), s)};
                input_left.erase(it, end(input_left));
            }
        }

        // Finds 3
        for (string s : input_left)
        {
            string tmp{s};
            for (char c : coupled[7])
            {
                auto it{remove(begin(tmp), end(tmp), c)};
                tmp.erase(it, end(tmp));
            }
            if (tmp.size() == 2)
            {
                coupled[3] = s;
                auto it{remove(begin(input_left), end(input_left), s)};
                input_left.erase(it, end(input_left));
                break;
            }
        }

        // Finds 6
        for (string s : input_left)
        {
            string tmp{s};
            for (char c : coupled[7])
            {
                auto it{remove(begin(tmp), end(tmp), c)};
                tmp.erase(it, end(tmp));
            }
            if (tmp.size() == 4)
            {
                coupled[6] = s;
                auto it{remove(begin(input_left), end(input_left), s)};
                input_left.erase(it, end(input_left));
                break;
            }
        }

        // Finds 0
        for (string s : input_left)
        {
            string tmp{s};
            for (char c : coupled[3])
            {
                auto it{remove(begin(tmp), end(tmp), c)};
                tmp.erase(it, end(tmp));
            }
            if (tmp.size() == 2)
            {
                coupled[0] = s;
                auto it{remove(begin(input_left), end(input_left), s)};
                input_left.erase(it, end(input_left));
                break;
            }
        }

        // Finds 2
        for (string s : input_left)
        {
            string tmp{s};
            for (char c : (coupled[7] + coupled[4]))
            {
                auto it{remove(begin(tmp), end(tmp), c)};
                tmp.erase(it, end(tmp));
            }
            if (tmp.size() == 2)
            {
                coupled[2] = s;
                auto it{remove(begin(input_left), end(input_left), s)};
                input_left.erase(it, end(input_left));
                break;
            }
        }

        // Finds 9
        for (string s : input_left)
        {
            string tmp{s};
            for (char c : coupled[6])
            {
                auto it{remove(begin(tmp), end(tmp), c)};
                tmp.erase(it, end(tmp));
            }
            if (tmp.size() == 1)
            {
                coupled[9] = s;
                auto it{remove(begin(input_left), end(input_left), s)};
                input_left.erase(it, end(input_left));
                break;
            }
        }

        // Finds 5
        for (string s : input_left)
        {
            string tmp{s};
            if (tmp.size() != 0)
            {
                coupled[5] = s;
                auto it{remove(begin(input_left), end(input_left), s)};
                input_left.erase(it, end(input_left));
                break;
            }
        }

        int factor{1000};
        int sum{};
        for (string s : output)
        {
            for (auto ss : coupled)
            {
                if (ss.second == s)
                {
                    sum += ss.first * factor;
                }
            }
            factor = factor / 10;
        }

        total_sum += sum;
        if (sum == 0)
        {
            search = false;
        }
    }

    std::cout << "Answer: " << total_sum << endl;
    if (total_sum == 1091609)
    {
        std::cout << "Correct! (if running with input.txt)" << endl;
    }
    else
    {
        std::cerr << "WRONG! (if running with input.txt)" << endl;
    }

    return 0;
}