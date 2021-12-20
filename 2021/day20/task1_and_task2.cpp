#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void pad_input(vector<vector<int>> &input, int const &padding, int const &padnr)
{
    int len{int(input[0].size())};
    vector<int> pad(len, padnr);

    // Top and bottom margin:
    for (int i{}; i < padding; i++)
    {
        input.insert(begin(input), pad);
        input.push_back(pad);
    }

    // Side margins:
    for (auto &row : input)
    {
        for (int i{}; i < padding; i++)
        {
            row.insert(begin(row), padnr);
            row.push_back(padnr);
        }
    }
}

void depad_input(vector<vector<int>> &input, int const &padding)
{
    // Top and bottom margin:
    for (int i{}; i < padding; i++)
    {
        input.erase(begin(input));
        input.pop_back();
    }

    // Side margins:
    for (auto &row : input)
    {
        for (int i{}; i < padding; i++)
        {
            row.erase(begin(row));
            row.pop_back();
        }
    }
}

int print_and_calculate_sum(vector<vector<int>> &input, bool const &print)
{
    int sum{};
    for (auto row : input)
    {
        for (auto col : row)
        {
            if (col == 1)
            {
                sum += 1;
            }
            if (print)
            {
                if (col == 1)
                {
                    cout << "#";
                }
                else
                {
                    cout << ".";
                }
            }
        }
        if (print)
        {
            cout << endl;
        }
    }
    return sum;
}

void enhance_input(vector<vector<int>> &input, vector<int> const &enhancement_alg)
{
    vector<vector<int>> output{input};
    for (int row{1}; (row + 1) < int(input.size()); row++)
    {
        for (int col{1}; (col + 1) < int(input[0].size()); col++)
        {
            int key{};
            key += input[row - 1][col - 1] * 256;
            key += input[row - 1][col - 0] * 128;
            key += input[row - 1][col + 1] * 64;
            key += input[row + 0][col - 1] * 32;
            key += input[row + 0][col - 0] * 16;
            key += input[row + 0][col + 1] * 8;
            key += input[row + 1][col - 1] * 4;
            key += input[row + 1][col - 0] * 2;
            key += input[row + 1][col + 1] * 1;
            output[row][col] = enhancement_alg[key];
        }
    }

    depad_input(output, 1); // removes outer row:
    input = output;
    pad_input(input, 2, output[0][0]);
}

int main()
{
    // Input handling:
    ifstream file{"input.txt"};
    string line{};

    vector<int> enhancement_alg{};
    getline(file, line);
    for (char c : line)
    {
        if (c == '.')
        {
            enhancement_alg.push_back(0);
        }
        else
        {
            enhancement_alg.push_back(1);
        }
    }

    cout << "Enhancment algorithm read. Size: " << enhancement_alg.size() << endl;

    vector<vector<int>> input{};
    while (getline(file, line))
    {
        vector<int> tmp{};
        for (char c : line)
        {
            if (c == '.')
            {
                tmp.push_back(0);
            }
            else
            {
                tmp.push_back(1);
            }
        }
        if (!tmp.empty())
        {
            input.push_back(tmp);
        }
    }

    cout << "Input figure read. Size: " << input.size() << " x " << input[0].size() << endl;

    // Solving:
    pad_input(input, 3, 0);

    for (int iter{}; iter < 50; iter++) // choose number of iterations
    {
        enhance_input(input, enhancement_alg);
    }
    cout << "Input figure updated. Size: " << input.size() << " x " << input[0].size() << endl;

    int sum{print_and_calculate_sum(input, false)};

    cout << "Sum white pixels: " << sum << endl;

    return 0;
}