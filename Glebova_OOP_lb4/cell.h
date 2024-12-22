#pragma once

#include "segment.h"


class Cell{
    public:
        enum VisibilityCondition{
            HIDDEN = 0,
            EMPTY = 1,
            SHIP = 2
        };

        Cell();

        bool isEmpty();
        void setSegment(Segment& segment);
        Segment& getSegment();
        void setCondition(VisibilityCondition state);
        VisibilityCondition getCondition();

    private:
        Segment* m_segment;
        bool m_is_empty;
        VisibilityCondition m_state;
};