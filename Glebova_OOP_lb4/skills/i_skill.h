#pragma once

#include <memory>

#include "info_holder.h"


class ISkill {
    public:
        virtual ~ISkill() = default;
        virtual bool useSkill(InfoHolder& info_holder) = 0;
};
