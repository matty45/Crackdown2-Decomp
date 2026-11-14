// Burn/RuffKing field names; CD2 constructor 0x82756238 walks five 16-byte entries.
#ifndef ORB_TSKILLPICKUPDATA_H
#define ORB_TSKILLPICKUPDATA_H
#include "RPG/eSkills.h"
#include "cd2/layout.h"
namespace ORB
{
    struct tSkillPickupData
    {
        unsigned int nMaxPickups;
        int nEffectID;
        int nSquadEffectID;
        RPG::eSkills nSkill;
        CD2_LAYOUT_CHECKS(tSkillPickupData,
            CD2_SIZE(tSkillPickupData, 0x10)
            CD2_OFFSET(tSkillPickupData, nMaxPickups, 0)
            CD2_OFFSET(tSkillPickupData, nEffectID, 4)
            CD2_OFFSET(tSkillPickupData, nSquadEffectID, 8)
            CD2_OFFSET(tSkillPickupData, nSkill, 0xC))
    };
}
#endif
