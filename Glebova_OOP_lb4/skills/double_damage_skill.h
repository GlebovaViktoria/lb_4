#pragma once

#include "i_skill.h"


class DoubleDamageSkill: public ISkill{
    public:
        bool useSkill(InfoHolder& info_holder);
};
