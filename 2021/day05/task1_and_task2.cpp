#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Line
{
public:
    int x1{};
    int x2{};
    int y1{};
    int y2{};

    void print_line()
    {
        cout << x1 << ',' << y1 << " -> " << x2 << ',' << y2 << endl;
    }
};

void print_diagram(vector<vector<int>> const& diagram)
{
    for (vector<int> row : diagram)
    {
        for (int i : row)
        {
            if (i == 0)
            {
                cout << '.';
            }
            else
            {
                cout << i;
            }
        }
        cout << endl;
    }
}

int calculate_diagram(vector<vector<int>> const& diagram)
{
    int sum{};
    for (vector<int> row : diagram)
    {
        for (int i : row)
        {
            if (i >= 2)
            {
                sum += 1;
            }
        }
    }
    return sum;
}

void add_line_to_diagram(Line * ptr, vector<vector<int>> &diagram, bool use_diag = false)
{
    if (ptr->x1 == ptr->x2)
    {
        int _min{min(ptr->y1,ptr->y2)};
        int _max{max(ptr->y1,ptr->y2)};

        for (int i{_min}; i <= _max; i++)
        {
            diagram[i][ptr->x1] += 1;
        }
    }
    else if (ptr->y1 == ptr->y2)
    {
        int _min{min(ptr->x1,ptr->x2)};
        int _max{max(ptr->x1,ptr->x2)};

        for (int i{_min}; i <= _max; i++)
        {
            diagram[ptr->y1][i] += 1;
        }
    }
    else if (use_diag)
    {
        vector<int> y{};
        if (ptr->y1 < ptr->y2)
        {
            for (int i{ptr->y1}; i <= ptr->y2; i++)
            {
                y.push_back(i);
            }
        }
        else
        {
            for (int i{ptr->y1}; i >= ptr->y2; i--)
            {
                y.push_back(i);
            }
        }

        vector<int> x{};
        if (ptr->x1 < ptr->x2)
        {
            for (int i{ptr->x1}; i <= ptr->x2; i++)
            {
                x.push_back(i);
            }
        }
        else
        {
            for (int i{ptr->x1}; i >= ptr->x2; i--)
            {
                x.push_back(i);
            }
        }
        
        int count{};
        for (int xi : x)
        {
            diagram[y[count]][xi] += 1;
            count += 1;
        }
    }
}

int main()
{
    ifstream file{"input.txt"};
    string line{};

    vector<Line * > lines{};
    while (getline(file,line))
    {
        Line * ptr{new Line};
        lines.push_back(ptr);

        stringstream ss{line};
        char tmp{};
        string temp{};
        ss >> ptr->x1 >> tmp >> ptr->y1;
        ss >> temp >> ptr->x2 >> tmp >> ptr->y2;
    }

    {
        vector<int> tmp(1000,0);
        vector<vector<int>> diagram(1000,tmp);

        for (Line * ptr: lines)
        {
            add_line_to_diagram(ptr, diagram, false);
        }
        // print_diagram(diagram);
        cout << "Answer w/o diag: " << calculate_diagram(diagram) << endl;
    }

    {
        vector<int> tmp(1000,0);
        vector<vector<int>> diagram(1000,tmp);

        for (Line * ptr: lines)
        {
            add_line_to_diagram(ptr, diagram, true);
            delete ptr;
        }
        // print_diagram(diagram);
        cout << "Answer with diag: " << calculate_diagram(diagram) << endl;
    }

    return 0;
}