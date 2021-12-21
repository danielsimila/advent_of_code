#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Player
{
public:
    Player(int n, int p) : name{n}, position{p} {};

    void update_position(int roll)
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

vector<unsigned long long> play(int const &turn, vector<Player> players, map<int, int> const &rolls)
{
    vector<unsigned long long> wins_in_universe{0, 0};
    int initscore{players[turn].score};
    int initpos{players[turn].position};

    for (auto roll : rolls)
    {
        players[turn].update_position(roll.first);
        players[turn].update_score();
        if (players[turn].score >= 21)
        {
            wins_in_universe[turn] += roll.second * 1;
        }
        else
        {
            auto tmp{play(!turn, players, rolls)};
            wins_in_universe[0] += roll.second * tmp[0];
            wins_in_universe[1] += roll.second * tmp[1];
        }

        // Reseting for iteration:
        players[turn].score = initscore;
        players[turn].position = initpos;
    }

    return wins_in_universe;
}

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

    map<int, int> rolls{};
    for (int roll_1{1}; roll_1 <= 3; roll_1++) // roll 1
    {
        for (int roll_2{1}; roll_2 <= 3; roll_2++) // roll 2
        {
            for (int roll_3{1}; roll_3 <= 3; roll_3++) // roll 3
            {
                int roll{roll_1 + roll_2 + roll_3};
                rolls[roll] += 1;
            }
        }
    }

    vector<unsigned long long> wins{0, 0};
    int turn{0};
    wins = play(turn, players, rolls);

    cout << "Done!" << endl;
    cout << "Player 1 wins: " << wins[0] << endl;
    cout << "Player 2 wins: " << wins[1] << endl;

    return 0;
}