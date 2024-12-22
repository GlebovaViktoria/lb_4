#pragma once

#include "i_creator.h"
#include "i_skill.h"
#include "scanner_skill.h"


class ScannerCreator : public ICreator {
    public:
        std::unique_ptr<ISkill> create();
};
