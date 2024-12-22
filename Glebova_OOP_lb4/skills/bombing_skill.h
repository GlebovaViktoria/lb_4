#pragma once

#include "i_skill.h"


class BombingSkill: public ISkill{
    public:
        bool useSkill(InfoHolder& info_holder);
};
