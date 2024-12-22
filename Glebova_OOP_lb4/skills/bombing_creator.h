#pragma once

#include "i_creator.h"
#include "i_skill.h"
#include "bombing_skill.h"


class BombingCreator : public ICreator {
    public:
        std::unique_ptr<ISkill> create();
};
