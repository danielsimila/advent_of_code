#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>

using namespace std;

long long int bitstring2num(string const &s)
{
    long long int tmp{};
    double val{};
    for (int iter{0}; iter < int(s.size()); iter++)
    {
        val = s[iter] - '0';
        tmp += val * pow(2, int(s.size()) - iter - 1);
    }
    return tmp;
}

long long int collect_package(string &packet, vector<long long int> &versions)
{
    int version{};
    int type{};
    long long int result{};
    // Getting version:
    {
        string tmp{};
        copy(begin(packet), begin(packet) + 3, back_inserter(tmp));
        packet.erase(begin(packet), begin(packet) + 3);
        version = bitstring2num(tmp);
        versions.push_back(version);
    }

    // Getting type ID:
    {
        string tmp{};
        copy(begin(packet), begin(packet) + 3, back_inserter(tmp));
        packet.erase(begin(packet), begin(packet) + 3);
        type = bitstring2num(tmp);
    }

    if (type == 4)
    {
        string combined{};
        bool read{true};
        while (read)
        {
            if (packet[0] == '0')
            {
                read = false;
            }
            packet.erase(begin(packet), begin(packet) + 1);
            copy(begin(packet), begin(packet) + 4, back_inserter(combined));
            packet.erase(begin(packet), begin(packet) + 4);
            if (packet.find('1') == std::string::npos)
            {
                read = false;
            }
        }
        result += bitstring2num(combined);
    }
    else
    {
        // Getting length type ID:
        vector<long long int> results{};
        char typeID{packet[0]};
        packet.erase(begin(packet), begin(packet) + 1);

        if (typeID == '0')
        {
            string tmp{};
            copy(begin(packet), begin(packet) + 15, back_inserter(tmp));
            packet.erase(begin(packet), begin(packet) + 15);

            long long int no_of_bits{bitstring2num(tmp)};
            bool read{true};
            long long int read_bits{};
            while (read and (read_bits < no_of_bits))
            {
                long long int size{int(packet.size())};
                long long int res_tmp{collect_package(packet, versions)};
                results.push_back(res_tmp);
                read_bits += size - int(packet.size());
            }
        }
        else
        {
            string tmp{};
            copy(begin(packet), begin(packet) + 11, back_inserter(tmp));
            packet.erase(begin(packet), begin(packet) + 11);

            bool read{true};
            int iter(bitstring2num(tmp));
            int count{};
            while (read and (count < iter))
            {
                count += 1;
                long long int res_tmp{collect_package(packet, versions)};
                results.push_back(res_tmp);
            }
        }

        // Depending on package types...
        if (type == 0) // sum
        {
            long long int tmp{0};
            for (long long int r : results)
            {
                tmp += r;
            }
            result += tmp;
        }
        else if (type == 1) // product
        {
            long long int tmp{1};
            for (long long int r : results)
            {
                tmp *= r;
            }
            result += tmp;
        }
        else if (type == 2) // minimum
        {
            result += *min_element(begin(results), end(results));
        }
        else if (type == 3) // maxmimum
        {
            result += *max_element(begin(results), end(results));
        }
        else if (type == 5) // greater
        {
            result += (results[0] > results[1]);
        }
        else if (type == 6) // less
        {
            result += (results[0] < results[1]);
        }
        else if (type == 7) // equal
        {
            result += (results[0] == results[1]);
        }
    }

    return result;
}

int main()
{
    map<char, string> hex2bits{};
    hex2bits['0'] = "0000";
    hex2bits['1'] = "0001";
    hex2bits['2'] = "0010";
    hex2bits['3'] = "0011";
    hex2bits['4'] = "0100";
    hex2bits['5'] = "0101";
    hex2bits['6'] = "0110";
    hex2bits['7'] = "0111";
    hex2bits['8'] = "1000";
    hex2bits['9'] = "1001";
    hex2bits['A'] = "1010";
    hex2bits['B'] = "1011";
    hex2bits['C'] = "1100";
    hex2bits['D'] = "1101";
    hex2bits['E'] = "1110";
    hex2bits['F'] = "1111";

    ifstream file{"input.txt"};
    string line{};
    vector<long long int> versions{};
    long long int result{};

    while (getline(file, line))
    {
        string packet{};
        for (char c : line)
        {
            packet += hex2bits[c];
        }
        result = collect_package(packet, versions);
    }

    cout << "Version ";
    long long int sum{};
    for (long long int v : versions)
    {
        sum += v;
    }
    cout << "sum: " << sum << endl;

    cout << "Result: " << result << endl;

    return 0;
}
