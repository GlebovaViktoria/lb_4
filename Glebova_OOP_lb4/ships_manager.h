#pragma once

#include <vector>
#include <iostream>
#include <bits/stdc++.h>

#include "ship.h"

using namespace std;


class ShipsManager{
    public:
        ShipsManager(size_t ship_count, vector<unsigned short int> ship_lens);

        size_t len();
        Ship& getShip(size_t index);
        size_t getNewDeads();
    private:
        size_t m_len;
        vector<Ship> m_ships;
        vector<size_t> m_dead_ships;
};