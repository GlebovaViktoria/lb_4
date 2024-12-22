#pragma once

#include "i_creator.h"
#include "i_skill.h"
#include "double_damage_skill.h"


class DoubleDamageCreator : public ICreator {
    public:
        std::unique_ptr<ISkill> create();
};
