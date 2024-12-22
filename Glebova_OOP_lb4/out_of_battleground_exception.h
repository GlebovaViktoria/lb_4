#pragma once

#include <stdexcept>

using namespace std;


class OutOfBattlegroundException : public logic_error{
    public:
        OutOfBattlegroundException():logic_error("Out of battleground!"){}
};
