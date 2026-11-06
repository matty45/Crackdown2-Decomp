#ifndef GameManagement_cRooftopRaceGameModePrototype_H
#define GameManagement_cRooftopRaceGameModePrototype_H

#include "GameManagement/cPvPGameModePrototype.h"

namespace GameManagement
{
    class cRooftopRaceGameModePrototype : public cPvPGameModePrototype
    {
    public:
        // CD2 0x82854908 inlines this constructor over 0x8283E2F8.
        __forceinline cRooftopRaceGameModePrototype() {}
        // CD2 table 0x8215C888: own slots 42..44 precede RetClassName at 45.
        virtual void vf42();
        virtual void vf43();
        virtual void vf44();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual int RetStringID() const;
        virtual void Destruct();
        CD2_LAYOUT_CHECKS(cRooftopRaceGameModePrototype, CD2_SIZE(cRooftopRaceGameModePrototype, 0x148))
    };
}

#endif
