#include "cell.h"


Cell::Cell(){
    this->m_is_empty = true;
    this->m_state = Cell::VisibilityCondition::HIDDEN;
    this->m_segment = nullptr;
}

bool Cell::isEmpty(){
    return this->m_is_empty;
}

void Cell::setSegment(Segment& segment){
    this->m_segment = &segment;
    this->m_is_empty = false;
}

Segment& Cell::getSegment(){
    if (isEmpty())
        throw invalid_argument("This cell is empty!");
    return *this->m_segment;
}

void Cell::setCondition(Cell::VisibilityCondition state){
    this->m_state = state;
}

Cell::VisibilityCondition Cell::getCondition(){
    return this->m_state;
}