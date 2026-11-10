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
        // CD2: cTeamHunterGathererGameModePrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual GameManagement::etGameModeType RetType() const; // 14: 0x825ECFA8
        virtual void vf16(); // 16: 0x8288FB78
        virtual void vf24(); // 24: 0x8288FB78
        virtual void vf26(); // 26: 0x8288AD98
        virtual void vf40(); // 40: 0x82881BA8
    };
}

#endif
