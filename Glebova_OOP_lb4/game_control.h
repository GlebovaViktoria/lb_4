#pragma once

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <algorithm>


using namespace std;

class GameControl {
public:
    GameControl();
    void setDefault();
    char getCommandKey(const string& command);
    vector<string> split(const string& s, char delim);
    void load(const string& filename);
    string parseCommand(char command);

private:
    map<string, char> commands;
    map<char, string> reverse_commands;
};