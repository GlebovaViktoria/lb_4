#include "segment.h"

Segment::Segment(){
    this->m_state = State::UNDAMAGED; 
}

Segment::State Segment::getState(){
    return this->m_state;
}

void Segment::setState(State state){
    this->m_state = state;
}

void Segment::changeStateDelta(int delta){
    int new_value = this->m_state + delta;
    if (new_value >= Segment::State::UNDAMAGED)
        this->m_state = Segment::State::UNDAMAGED;
    else if (new_value <= Segment::State::DESTROYED)
        this->m_state = Segment::State::DESTROYED;
    else
        this->m_state = Segment::State::DAMAGED;
}
