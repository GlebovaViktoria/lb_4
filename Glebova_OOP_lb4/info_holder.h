#pragma once

#include "battleground.h"
#include "ships_manager.h"
#include <memory>


class InfoHolder{
    public:
        InfoHolder(shared_ptr<Battleground> battleground, shared_ptr<ShipsManager> ships_manager, size_t x=0, size_t y=0);

        shared_ptr<Battleground> battleground;
        size_t x;
        size_t y;
        shared_ptr<ShipsManager> ships_manager;
};