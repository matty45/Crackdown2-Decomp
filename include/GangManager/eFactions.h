// GangManager::eFactions: the factions, as RuffKing names them. CD2's cFactionTargetingProfile::HandleAttributes
// (0x82452160) passes 0..5 to SetupTargetData in this order, matching its command IDs CMD_CIVILIANS..CMD_AGENT_ROGUE.
#ifndef GANGMANAGER_EFACTIONS_H
#define GANGMANAGER_EFACTIONS_H

namespace GangManager
{
    enum eFactions
    {
        FACTION_CIVILIANS = 0,
        FACTION_FREAKS = 1,
        FACTION_AGENCY = 2,
        FACTION_CELL = 3,
        FACTION_AGENT = 4,
        FACTION_AGENT_ROGUE = 5,
        FACTION_NUM = 6
    };
}

#endif // GANGMANAGER_EFACTIONS_H
