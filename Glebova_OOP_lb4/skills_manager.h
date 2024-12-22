#pragma once

#include <vector>
#include <queue>
#include <algorithm>
#include <random>

#include "skills/i_creator.h"
#include "skills/bombing_creator.h"
#include "skills/double_damage_creator.h"
#include "skills/scanner_creator.h"
#include "no_skill_exception.h"
#include "info_holder.h"


class SkillsManager{
    public:
        SkillsManager();
        SkillsManager(vector<string> skills_names);
        unique_ptr<ISkill> popSkill();
        void addRandomSkill();
        void addRandomSkills(size_t n);
        bool usePopSkill(InfoHolder& info_holder);
        size_t size();
        size_t size() const;
        vector<string> getPrettySkills() const;
    private:
        ICreator& getRandomCreator();

        vector<unique_ptr<ISkill>> skills;
        vector<unique_ptr<ICreator>> creators;
};