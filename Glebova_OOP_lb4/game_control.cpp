#include "game_control.h"


GameControl::GameControl() {
    this->setDefault();
}

void GameControl::setDefault(){
    this->commands = {
        {"help", 'h'},
        {"load", 'l'},
        {"save", 's'},
        {"attack", 'a'}
    };
    this->reverse_commands = {
        {'h', "help"},
        {'l', "load"},
        {'s', "save"},
        {'a', "attack"}
    };
}

char GameControl::getCommandKey(const string& command) {
    if (this->commands.find(command) == this->commands.end())
        throw invalid_argument("Ошибка: Команда '" + command + "' не найдена!");
    return this->commands[command];
}

vector<string> GameControl::split(const string &s, char delim) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

void GameControl::load(const string& filename) {
    ifstream in(filename);
    if (!in)
        throw logic_error("Ошибка: Файл с управлением '" + filename + "' не найден!");
    
    stringstream buffer;
    buffer << in.rdbuf();
    string text = buffer.str();
    vector<string> lines = this->split(text, '\n');
    in.close();

    map<string, char> tmp_commands;
    vector<char> keys;
    
    for (size_t i = 0; i < lines.size(); ++i) {
        vector<string> command = this->split(lines[i], ':');
        
        if (command.size() != 2)
            throw logic_error("Ошибка: Неверный формат строки в конфигурационном файле: '" + lines[i] + "'");
        
        string command_name = command[0];
        char command_key = command[1][0];

        if (command_name != "help" && command_name != "load" && 
            command_name != "save" && command_name != "attack") {
            throw logic_error("Ошибка: Недопустимая команда '" + command_name + "' в конфигурационном файле!");
        }
        
        if (tmp_commands.find(command_name) != tmp_commands.end())
            throw logic_error("Ошибка: Дублирование команды '" + command_name + "' в конфигурационном файле!");

        if (find(keys.begin(), keys.end(), command_key) != keys.end())
            throw logic_error("Ошибка: Клавиша '" + string(1, command_key) + "' назначена более чем одной команде!");
        
        tmp_commands[command_name] = command_key;
        keys.push_back(command_key);
    }
    
    if (keys.size() != 4)
        throw logic_error("Ошибка: Должны быть заданы все 4 команды (help, load, save, attack)!");
    
    vector<string> required_commands = {"help", "load", "save", "attack"};
    for (const auto& command : required_commands) {
        if (tmp_commands.find(command) == tmp_commands.end())
            throw logic_error("Ошибка: Команда '" + command + "' не задана в конфигурационном файле!");
    }

    this->commands = tmp_commands;
    this->reverse_commands.clear();
    for (const auto& command : required_commands) {
        this->reverse_commands[tmp_commands[command]] = command;
    }
}

string GameControl::parseCommand(char command) {
    if (this->reverse_commands.find(command) == this->reverse_commands.end())
        throw invalid_argument("Ошибка: Команда для клавиши '" + string(1, command) + "' не найдена!");
    return this->reverse_commands[command];
}
