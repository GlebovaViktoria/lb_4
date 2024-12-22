#include "info_holder.h"


InfoHolder::InfoHolder(shared_ptr<Battleground> battleground, shared_ptr<ShipsManager> ships_manager, size_t x, size_t y):
    battleground(battleground), x(x), y(y), ships_manager(ships_manager) {}
