#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

pair<int, int> find_max_x_and_y(vector<pair<int, int>> const &dots)
{
    pair<int, int> tmp{};

    for (auto xy : dots)
    {
        if (xy.first > tmp.first)
        {
            tmp.first = xy.first;
        }
        if (xy.second > tmp.second)
        {
            tmp.second = xy.second;
        }
    }
    return tmp;
}

int main()
{
    ifstream file{"input.txt"};
    string line{};
    int xx{};
    int yy{};
    int max_x{};
    int max_y{};

    vector<pair<int, int>> dots{};
    vector<pair<char, int>> folds{};
    while (getline(file, line))
    {
        stringstream ss{line};
        if (line[0] == 'f')
        {
            string bin;
            char trash;
            char dir;
            ss >> bin >> bin >> dir >> trash >> xx;

            folds.push_back(pair<char, int>{dir, xx});
        }
        else
        {
            char trash;
            ss >> xx >> trash >> yy;

            dots.push_back(pair<int, int>{xx, yy});
        }
    }

    // PART 1:
    pair<char, int> f{folds[0]};
    vector<pair<int, int>> copy{dots};

    transform(begin(dots), end(dots), begin(dots),
              [&f](auto dot)
              {
                  if (f.first == 'y')
                  {
                      if (dot.second > f.second)
                      {
                          dot.second = 2 * f.second - dot.second; // y changed
                      }
                  }
                  else if (f.first == 'x')
                  {
                      if (dot.first > f.second)
                      {
                          dot.first = 2 * f.second - dot.first; // x changed
                      }
                  }
                  return dot;
              });

    auto maxes{find_max_x_and_y(dots)};
    max_x = maxes.first;
    max_y = maxes.second;

    int sum_dots{};
    for (int y{0}; y <= max_y; y++)
    {
        for (int x{0}; x <= max_x; x++)
        {
            if (find(begin(dots), end(dots), pair<int, int>{x, y}) != end(dots))
            {
                sum_dots += 1;
            }
        }
    }
    cout << "Sum dots, part 1: " << sum_dots << endl;

    // PART 2:
    dots = copy;
    for (auto f : folds)
    {
        transform(begin(dots), end(dots), begin(dots),
                  [&f](auto dot)
                  {
                      if (f.first == 'y')
                      {
                          if (dot.second > f.second)
                          {
                              dot.second = 2 * f.second - dot.second; // y changed
                          }
                      }
                      else if (f.first == 'x')
                      {
                          if (dot.first > f.second)
                          {
                              dot.first = 2 * f.second - dot.first; // x changed
                          }
                      }
                      return dot;
                  });
    }

    auto last{unique(begin(dots), end(dots))};
    dots.erase(last, end(dots));

    maxes = find_max_x_and_y(dots);
    max_x = maxes.first;
    max_y = maxes.second;

    cout << "Output after all folds, part 2: " << endl;
    for (int y{0}; y <= max_y; y++)
    {
        for (int x{0}; x <= max_x; x++)
        {
            if (find(begin(dots), end(dots), pair<int, int>{x, y}) != end(dots))
            {
                cout << '#';
            }
            else
            {
                cout << ' ';
            }
        }
        cout << endl;
    }

    return 0;
}