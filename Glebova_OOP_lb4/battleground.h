#pragma once

#include "segment.h"
#include "ship.h"
#include "cell.h"
#include "coordinates_place_ship_exception.h"
#include "out_of_battleground_exception.h"
#include "out_of_battleground_attack_exception.h"

#include <cstring>


class Battleground{
    public:
        Battleground(size_t width, size_t height);
        Battleground(const Battleground& battleground);
        Battleground& operator=(const Battleground& battleground);
        Battleground(Battleground&& battleground);
        Battleground& operator=(Battleground&& battleground);
        ~Battleground();

        void placeShip(size_t x, size_t y, Ship& ship, Ship::Orientation orientation);
        void attackCell(size_t x, size_t y, size_t damage=1);
        void setDamageMultiplier(unsigned short int multiplier);
        Cell& getCell(size_t x, size_t y);
        size_t getWidth();
        size_t getHeight();
        bool isHaveAliveShips();

    private:
        size_t m_width;
        size_t m_height;
        Cell** m_field;
        unsigned short int m_damage_multiplier;

        bool canPlaceSegment(long int x, long int y);
};