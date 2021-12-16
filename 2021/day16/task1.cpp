#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int bitstring2num(string const &s)
{
    int tmp{};
    double val{};
    for (int iter{0}; iter < int(s.size()); iter++)
    {
        val = s[iter] - '0';
        tmp += val * pow(2, int(s.size()) - iter - 1);
    }
    return tmp;
}

void collect_package(string packet, vector<string> &packets, vector<int> &versions)
{
    int version{};
    int type{};
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

    packets.push_back(packet);

    if (type == 4)
    {
        bool read{true};
        while (read)
        {
            if (packet[0] == '0')
            {
                read = false;
            }
            packet.erase(begin(packet), begin(packet) + 5);
        }
        if (packet.find('1') != std::string::npos)
        {
            collect_package(packet, packets, versions);
        }
        std::cout << "Literal Values! Version: " << version << endl;
    }
    else
    {
        std::cout << "Operator Package! Version: " << version << endl;

        // Getting length type ID:
        char typeID{packet[0]};
        packet.erase(begin(packet), begin(packet) + 1);

        // Getting length:
        if (typeID == '0')
        {
            packet.erase(begin(packet), begin(packet) + 15);
            collect_package(packet, packets, versions);
        }
        else
        {
            packet.erase(begin(packet), begin(packet) + 11);
            collect_package(packet, packets, versions);
        }
    }
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
    vector<string> packets{};
    vector<int> versions{};

    while (getline(file, line))
    {
        string packet{};
        for (char c : line)
        {
            packet += hex2bits[c];
        }
        collect_package(packet, packets, versions);
    }

    std::cout << "Packets: " << packets.size() << endl;
    std::cout << "Version: ";
    int sum{};
    for (int v : versions)
    {
        std::cout << v << ", ";
        sum += v;
    }
    std::cout << "sum: " << sum << endl;

    return 0;
}
