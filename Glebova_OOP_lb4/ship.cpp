#include "ship.h"


Ship::Ship(size_t len){
    if (len == 0 || len > 4)
        throw invalid_argument("Ship's len not in [1, 4]");

    this->m_len = len;
    this->m_orientation = Ship::Orientation::NONE;
    this->m_segments = vector<Segment>(this->m_len, Segment());
}

Ship::Ship(size_t len, Orientation m_orientation): Ship(len){
    this->m_orientation = m_orientation;
}

void Ship::setOrientation(Orientation m_orientation){
    this->m_orientation = m_orientation;
}

Ship::Orientation Ship::getOrientation(){
    return this->m_orientation;
}

size_t Ship::len(){
    return this->m_len;
}

Segment& Ship::getSegment(size_t index){
    return this->m_segments.at(index);
}

