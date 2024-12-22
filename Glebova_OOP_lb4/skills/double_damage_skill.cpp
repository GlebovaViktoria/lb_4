
#include "double_damage_skill.h"


bool DoubleDamageSkill::useSkill(InfoHolder& info_holder){
    info_holder.battleground->setDamageMultiplier(2);
    return true;
}
