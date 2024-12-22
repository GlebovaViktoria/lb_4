#pragma once

#include "i_skill.h"


class ScannerSkill: public ISkill{
    public:
        bool useSkill(InfoHolder& info_holder);
};
