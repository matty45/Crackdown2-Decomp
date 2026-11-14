// Skill-pickup console interface. RuffKing names the callback and shared switch;
// CD2 registers "toggleskillpickuptest" at 0x825D1748 and starts the switch true.
#ifndef RPG_SKILL_PICKUP_DEBUG_H
#define RPG_SKILL_PICKUP_DEBUG_H

namespace RPG
{
    extern bool g_bTestSkillPickup;
    void ToggleSkillPickupTest(void *, wchar_t *);
}

#endif
