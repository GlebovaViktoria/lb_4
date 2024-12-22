#pragma once

#include <stdexcept>

using namespace std;


class CoordinatesPlaceShipException : public logic_error{
    public:
        CoordinatesPlaceShipException(): logic_error("Ship cant place near or in other ship"){}
};
