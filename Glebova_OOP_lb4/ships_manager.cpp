#include "ships_manager.h"


ShipsManager::ShipsManager(size_t ship_count, vector<unsigned short int> ship_lens){
    if (ship_lens.size() < ship_count)
        throw invalid_argument("size of ship_lens must be less or equal ship_count");
    this->m_len = ship_count;
    for (size_t i = 0; i < ship_count; ++i)
        this->m_ships.push_back(Ship(ship_lens[i]));
}

size_t ShipsManager::len(){
    return this->m_len;
}

Ship& ShipsManager::getShip(size_t index){
    return this->m_ships.at(index);
}

size_t ShipsManager::getNewDeads(){
    size_t k = 0;
    bool alive;
    for (size_t i = 0; i < this->m_len; ++i){
        alive = false;
        if (count(this->m_dead_ships.begin(), this->m_dead_ships.end(), i) == 0){
            for (size_t j = 0; j < this->m_ships[i].len(); ++j){
                if (this->m_ships[i].getSegment(j).getState() != Segment::State::DESTROYED){
                    alive = true;
                    break;
                }
            }
            if (!alive){
                k++;
                this->m_dead_ships.push_back(i);
            }
        }
    }
    return k;
}