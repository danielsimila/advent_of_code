#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Player
{
public:
    Player(int n, int p) : name{n}, position{p} {};

    void update_position(int &roll)
    {
        while (roll > 0)
        {
            roll += -1;
            position += 1;

            if (position > 10)
            {
                position = 1;
            }
        }
    }

    void update_score()
    {
        score += position;
    }

    // Members
    int name{};
    int score{};
    int position{};
};

class Dice
{
public:
    int roll()
    {
        rolls += 1;
        number += 1;
        if (number > 100)
        {
            number = 1;
        }
        return number;
    }

    // Members:
    int number{0};
    int rolls{0};
};

int main()
{
    ifstream file{"input.txt"};
    string line{};

    vector<Player> players{};
    int playerno{};
    while (getline(file, line))
    {
        playerno += 1;
        char c{line.back()};
        int var{c - '0'};
        players.push_back(Player(playerno, var));
    }

    Dice dice{};
    bool winner{};
    while (!winner)
    {
        for (auto &player : players)
        {
            cout << "Player " << player.name << " rolls ";

            // Rolling
            int roll{};
            for (int i{}; i < 3; i++)
            {
                int r{dice.roll()};
                roll += r;
                cout << r << " ";
            }

            // Moves:
            player.update_position(roll);
            cout << "and moves to space " << player.position;

            // Total score:
            player.update_score();
            cout << " for a total score of " << player.score << "." << endl;

            // Winner?
            if (player.score >= 1000)
            {
                winner = true;
                break;
            }
        }
    }

    int min_score{1000};
    for (auto player : players)
    {
        if (player.score < min_score)
        {
            min_score = player.score;
        }
    }

    cout << min_score << " score x " << dice.rolls << " rolls = " << min_score * dice.rolls << endl;

    return 0;
}