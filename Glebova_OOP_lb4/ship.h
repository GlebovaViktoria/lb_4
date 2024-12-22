#pragma once

#include <vector>

#include "segment.h"

using namespace std;


class Ship{
    public:
        enum Orientation{
            NONE = -1,
            VERTICAL = 0,
            HORIZONTAL = 1
        };
        Ship(size_t len);
        Ship(size_t len, Orientation orientation);

        Orientation getOrientation();
        void setOrientation(Orientation orientation);
        size_t len();
        Segment& getSegment(size_t index);
    private:
        size_t m_len;
        Orientation m_orientation;
        vector<Segment> m_segments;
};