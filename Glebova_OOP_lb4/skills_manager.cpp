#include "skills_manager.h"


SkillsManager::SkillsManager(){
    creators.emplace_back(make_unique<DoubleDamageCreator>());
    creators.emplace_back(make_unique<BombingCreator>());
    creators.emplace_back(make_unique<ScannerCreator>());

    for (auto& creator : creators)
        this->skills.emplace_back(creator->create());

    random_device rd;
    default_random_engine engine(rd());
    shuffle(this->skills.begin(), this->skills.end(), engine);
}


SkillsManager::SkillsManager(vector<string> skills_names){
    creators.emplace_back(make_unique<DoubleDamageCreator>());
    creators.emplace_back(make_unique<BombingCreator>());
    creators.emplace_back(make_unique<ScannerCreator>());

    for (auto& skill_name : skills_names){
        if (skill_name == "DoubleDamageSkill")
            this->skills.emplace_back(this->creators[0]->create());
        else if (skill_name == "BombingSkill")
            this->skills.emplace_back(this->creators[1]->create());
        else if (skill_name == "ScannerSkill")
            this->skills.emplace_back(this->creators[2]->create());
    }
}


ICreator& SkillsManager::getRandomCreator(){
    random_device rd;
    default_random_engine engine(rd());
    
    return *this->creators[engine() % this->creators.size()];
}

void SkillsManager::addRandomSkill(){
    this->skills.emplace_back(this->getRandomCreator().create());
}

unique_ptr<ISkill> SkillsManager::popSkill(){
    if(this->skills.size() == 0)
        throw NoSkillException();

    auto skill = move(this->skills[0]);
    this->skills.erase(this->skills.begin());

    return skill;
}

bool SkillsManager::usePopSkill(InfoHolder& info_holder){
    return this->popSkill()->useSkill(info_holder);
}

size_t SkillsManager::size(){
    return this->skills.size();
}

void SkillsManager::addRandomSkills(size_t n){
    for (size_t i = 0; i < n; ++i)
        this->skills.emplace_back(this->getRandomCreator().create());
}


size_t SkillsManager::size() const{
    return this->skills.size();
}

vector<string> SkillsManager::getPrettySkills() const{
    vector<string> res;
    for (size_t i = 0; i < this->skills.size(); ++i){
        if (dynamic_cast<DoubleDamageSkill*>(this->skills[i].get())){
            res.push_back("DoubleDamageSkill");
        }
        else if (dynamic_cast<BombingSkill*>(this->skills[i].get())){
            res.push_back("BombingSkill");
        }
        else if (dynamic_cast<ScannerSkill*>(this->skills[i].get())){
            res.push_back("ScannerSkill");
        }
    }
    return res;
}