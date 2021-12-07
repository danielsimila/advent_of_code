#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Board 
{
public:
    vector<int> row1{0, 0, 0, 0, 0};
    vector<int> row2{0, 0, 0, 0, 0};
    vector<int> row3{0, 0, 0, 0, 0};
    vector<int> row4{0, 0, 0, 0, 0};
    vector<int> row5{0, 0, 0, 0, 0};
    vector<vector<int> * > board{&row1, &row2, &row3, &row4, &row5};

    vector<int> row1_dots{0, 0, 0, 0, 0};
    vector<int> row2_dots{0, 0, 0, 0, 0};
    vector<int> row3_dots{0, 0, 0, 0, 0};
    vector<int> row4_dots{0, 0, 0, 0, 0};
    vector<int> row5_dots{0, 0, 0, 0, 0};
    vector<vector<int> * > board_dots{&row1_dots, &row2_dots, &row3_dots, &row4_dots, &row5_dots};

    bool has_bingo{false};

    bool bingo()
    {
        for (vector<int> * row : board_dots)
        {
            if (count(begin(*row), end(*row), 1) == 5)
            {
                return true;
            }
        }
        for (int col : {0,1,2,3,4})
        {
            int sum{};
            for (vector<int> * row : board_dots)
            {
                sum += (*row)[col];
            } 

            if (sum == 5)
            {
                return true;
            }
        }

        return false;
    }

    void add_numbers(string line, int row)
    {
        stringstream ss{line};
        int tmp{};
        row += -1;
        for (int i{0}; i < 5; i++)
        {
            ss >> tmp;
            (*board[row])[i] = tmp;
        }
    }
    
    void check_number(int number)
    {   
        int row_nr{};
        for (vector<int> * row : board)
        {
            int col_nr{};
            for (int i : *row)
            {
                if (i == number)
                {
                    (*board_dots[row_nr])[col_nr] = 1;
                }
                col_nr += 1;
            }
            row_nr += 1;
        }
    }

    int calculate_score(int draw)
    {
        int sum{};
        int row_nr{};
        for (vector<int> * row : board)
        {
            int col_nr{};
            for (int i : *row)
            {
                if ((*board_dots[row_nr])[col_nr] == 0)
                {
                    sum += i;
                }
                col_nr += 1;
            }
            row_nr += 1;
        }
        return sum*draw;
    }

    void erase_board()
    {
        row1_dots = {0, 0, 0, 0, 0};
        row2_dots = {0, 0, 0, 0, 0};
        row3_dots = {0, 0, 0, 0, 0};
        row4_dots = {0, 0, 0, 0, 0};
        row5_dots = {0, 0, 0, 0, 0};
    }

    void print_board()
    {
        cout << "Board: " << endl;
        for (vector<int> * row : board)
        {
            for (int i : *row)
            {
                cout << i << ' ';
            }
            cout << endl;
        }
        cout << "Dots: " << endl;
        for (vector<int> * row : board_dots)
        {
            for (int i : *row)
            {
                cout << i << ' ';
            }
            cout << endl;
        }
    }
};

void erase_boards(vector<Board * > boards)
{
    for (Board * ptr : boards)
    {
        ptr->erase_board();
    }
}

int play_bingo(vector<int> draw, vector<Board * > boards, bool print = true)
{
    for (int i : draw)
    {
        int board_nr{};
        for (Board * ptr : boards)
        {
            board_nr += 1;
            ptr->check_number(i);
            if (ptr->bingo())
            {
                if (print)
                {
                    cout << "Winner is: Board " << board_nr << '!' << endl;
                    cout << "With score: " << ptr->calculate_score(i) << endl;
                    // ptr->print_board();
                }
                return board_nr-1;
            }
        } 
    }
    return -1;
}

void play_anti_bingo(vector<int> draw, vector<Board * > boards)
{
    
    while (boards.size() != 1) 
    {
        int winner{play_bingo(draw, boards, false)};
        boards.erase(begin(boards) + winner);
        erase_boards(boards);
    };
    play_bingo(draw, boards, true);
}

int main()
{
    ifstream file{"input.txt"};
    string line{};
    int var{};

    // Loading draw numbers:
    getline(file,line);
    stringstream ss{line};
    vector<int> draw{};
    while (ss >> var)
    {
        draw.push_back(var);
        char tmp{};
        ss >> tmp;
    }

    // Loading borads:
    vector<Board * > boards{};
    while (getline(file,line))
    {
        if (line.size() != 0)
        {
            boards.push_back(new Board);
            boards.back()->add_numbers(line, 1);
            for (int i{2}; i <= 5; i++)
            {
                getline(file,line);
                boards.back()->add_numbers(line, i);
            }
        }
    }

    cout << "Task 1:" << endl;
    play_bingo(draw, boards);
    erase_boards(boards);
    cout << "Task 2:" << endl;
    play_anti_bingo(draw, boards);

    for (Board * ptr : boards)
    {
        delete ptr;
    }

    return 0;
}