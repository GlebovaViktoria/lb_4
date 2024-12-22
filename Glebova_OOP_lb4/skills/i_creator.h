#pragma once

#include <memory>

#include "i_skill.h"


class ICreator{
    public:
        virtual ~ICreator() = default;
        virtual std::unique_ptr<ISkill> create() = 0;
};
