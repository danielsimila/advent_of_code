#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

void find_rating(vector<vector<int>> &vec, bool type, vector<vector<int>> const& numbers)
{
    for (uint i{0}; i < numbers[0].size(); i++)
    {        
        int bit_count{};
        int total{};
        for (vector<int> row : vec)
        {   
            bit_count += row[i];
            total += 1;
        }

        bool cond{};
        if (type)
        {
            cond = (bit_count >= (total - bit_count));
        }
        else
        {
            cond = !(bit_count >= (total - bit_count));
        }

        vector<vector<int>> tmp{};
        for (vector<int> row : vec)
        {   
            // keep the 1:s / 0:s
            if (row[i] == cond)
            {
                tmp.push_back(row);
            } 
        }
        vec = tmp;
        if (vec.size() == 1)
        {
            break;
        }
    }
    return;
}

double decimal_rating(vector<vector<int>> const& vec)
{
    int count{};
    double rating{};
    for (int i : vec[0])
    {   
        rating += i*pow((2*i),(vec[0].size()-1-count));
        count += 1;  
    }
    return rating;
}

int main()
{
    ifstream file{"test.txt"};
    string line{};
    char tmp{};
    vector<vector<int>> numbers{};
    
    // Reading all numbers to vector:
    while (getline(file,line))
    {   
        istringstream ss(line);   
        vector<int> row{};
        while (ss >> tmp)
        {
            row.push_back(tmp - '0');
        }
        numbers.push_back(row);
    } 

    vector<vector<int>> oxygen{numbers};
    vector<vector<int>> CO2{numbers};

    find_rating(oxygen, true, numbers);
    find_rating(CO2, false, numbers);

    double oxygen_rating{decimal_rating(oxygen)};
    double co2_rating{decimal_rating(CO2)};

    cout << "Power consumption: " << int(oxygen_rating*co2_rating) << endl;
    cout << "oxygen_rating: " << oxygen_rating << endl;
    cout << "co2_rating: " << co2_rating << endl;

    return 0;
}