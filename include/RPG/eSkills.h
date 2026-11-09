// Names/order from RuffKing cSkillPickupProfile.h. CD2's character level wrappers select 0, 2, 3 and 4;
// cSkillSet stores six skill entries. Only the reference-named skills are declared here.
#ifndef RPG_ESKILLS_H
#define RPG_ESKILLS_H
namespace RPG
{
    enum eSkills
    {
        eSk_None = -1,
        eSk_Athletics = 0,
        eSk_Driving,
        eSk_Explosives,
        eSk_Fighting,
        eSk_FireArms,
        eSk_Squad,
        eSk_Num
    };
}
#endif
