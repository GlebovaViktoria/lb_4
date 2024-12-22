#include "battleground.h"


Battleground::Battleground(size_t width, size_t height){
    this->m_width = width;
    this->m_height = height;
    this->m_damage_multiplier = 1;

    this->m_field = new Cell*[height];
    for (size_t i = 0; i < height; ++i)
        this->m_field[i] = new Cell[width]();
}

Battleground::Battleground(const Battleground& battleground){
    this->m_width = battleground.m_width;
    this->m_height = battleground.m_height;
    this->m_damage_multiplier = battleground.m_damage_multiplier;

    this->m_field = new Cell*[this->m_height];
    for (size_t i = 0; i < this->m_height; ++i){
        this->m_field[i] = new Cell[this->m_width];
        for (size_t j = 0; j < this->m_width; ++j)
            this->m_field[i][j] = battleground.m_field[i][j];
    }
}

bool Battleground::canPlaceSegment(long int x, long int y){
    if (x >= (long int)this->m_width || x < 0 || y >= (long int)this->m_height || y < 0)
        return false;
    for (long int i = y - 1; i <= y + 1; ++i){
        for (long int j = x - 1; j <= x + 1; ++j){
            if (((0 <= j && j < (long int)this->m_width) && (0 <= i && i < (long int)this->m_height)) && !(this->m_field[i][j].isEmpty()))
                return false;
        }
    }

    return true;
}

void Battleground::placeShip(size_t x, size_t y, Ship& ship, Ship::Orientation orientation){
    if (x >= this->m_width || y >= this->m_height)
        throw OutOfBattlegroundException();

    if (orientation == Ship::Orientation::HORIZONTAL){
        for (size_t i = x; i < x + ship.len(); ++i)
            if (!(this->canPlaceSegment(i, y)))
                throw CoordinatesPlaceShipException();
        
        for (size_t i = x; i < x + ship.len(); ++i)
            this->m_field[y][i].setSegment(ship.getSegment(i - x));
    }
    else{
        for (size_t i = y; i < y + ship.len(); ++i)
            if (!(this->canPlaceSegment(x, i)))
                throw CoordinatesPlaceShipException();

        for (size_t i = y; i < y + ship.len(); ++i)
            this->m_field[i][x].setSegment(ship.getSegment(i - y));
    }

    ship.setOrientation(orientation);
}

void Battleground::attackCell(size_t x, size_t y, size_t damage){
    if (x >= this->m_width || y >= this->m_height)
        throw OutOfBattlegroundAttackException();
    
    if (!(this->m_field[y][x].isEmpty())){
        this->m_field[y][x].getSegment().changeStateDelta(-damage*this->m_damage_multiplier);
        this->m_field[y][x].setCondition(Cell::VisibilityCondition::SHIP);
    }
    else
        this->m_field[y][x].setCondition(Cell::VisibilityCondition::EMPTY);
    this->m_damage_multiplier = 1;
}


Battleground& Battleground::operator=(const Battleground& battleground){
    if (this != &battleground){
        if (this->m_field){
            for (size_t i = 0; i < this->m_height; ++i)
                delete[] this->m_field[i];
            delete[] this->m_field;
        }

        this->m_width = battleground.m_width;
        this->m_height = battleground.m_height;
        this->m_damage_multiplier = battleground.m_damage_multiplier;

        this->m_field = new Cell*[this->m_height];
        for (size_t i = 0; i < this->m_height; ++i){
            this->m_field[i] = new Cell[this->m_width];
            for (size_t j = 0; j < this->m_width; ++j)
                this->m_field[i][j] = battleground.m_field[i][j];
        }
    }
    return *this;
}


Battleground::Battleground(Battleground&& battleground){
    this->m_width = battleground.m_width;
    this->m_height = battleground.m_height;
    this->m_field = battleground.m_field;
    this->m_damage_multiplier = battleground.m_damage_multiplier;

    battleground.m_width = 0;
    battleground.m_height = 0;
    battleground.m_field = nullptr;
    battleground.m_damage_multiplier = 0;
}

Battleground& Battleground::operator=(Battleground&& battleground){
    if (this != &battleground){
        if (this->m_field){
            for (size_t i = 0; i < this->m_height; ++i)
                delete[] this->m_field[i];
            delete[] this->m_field;
        }

        this->m_width = battleground.m_width;
        this->m_height = battleground.m_height;
        this->m_field = battleground.m_field;
        this->m_damage_multiplier = battleground.m_damage_multiplier;

        battleground.m_width = 0;
        battleground.m_height = 0;
        battleground.m_field = nullptr;
        battleground.m_damage_multiplier = 0;
    }
    return *this;
}


Battleground::~Battleground(){
    if (this->m_field){
        for (size_t i = 0; i < this->m_height; ++i)
            delete [] this->m_field[i];
        delete [] this->m_field;
    }
}

void Battleground::setDamageMultiplier(unsigned short int multiplier){
    this->m_damage_multiplier = multiplier;
}

Cell& Battleground::getCell(size_t x, size_t y){
    if (x >= this->m_width || y >= this->m_height)
        throw OutOfBattlegroundException();
    return this->m_field[y][x];
}

size_t Battleground::getWidth(){
    return this->m_width;
}

size_t Battleground::getHeight(){
    return this->m_height;
}

bool Battleground::isHaveAliveShips(){
    for (size_t i = 0; i < this->m_height; ++i)
        for (size_t j = 0; j < this->m_width; ++j)
            if (!this->m_field[i][j].isEmpty() && this->m_field[i][j].getSegment().getState() != Segment::State::DESTROYED)
                return true;
    return false;
}