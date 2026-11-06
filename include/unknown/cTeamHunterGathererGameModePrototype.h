#ifndef unknown_cTeamHunterGathererGameModePrototype_H
#define unknown_cTeamHunterGathererGameModePrototype_H

#include "unknown/cHunterGathererGameModePrototype.h"

namespace unknown
{
    class cTeamHunterGathererGameModePrototype : public cHunterGathererGameModePrototype
    {
    public:
        // CD2 factory 0x82881B18 inlines this over cHunterGathererGameModePrototype.
        __forceinline cTeamHunterGathererGameModePrototype() {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual int RetStringID() const;
    };
}

#endif
