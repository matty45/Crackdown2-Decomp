#ifndef GameManagement_cRoadRaceGameModePrototype_H
#define GameManagement_cRoadRaceGameModePrototype_H

#include "GameManagement/cPvPGameModePrototype.h"

namespace GameManagement
{
    class cRoadRaceGameModePrototype : public cPvPGameModePrototype
    {
    public:
        // CD2 0x82854A48 inlines this constructor over 0x8283E2F8.
        __forceinline cRoadRaceGameModePrototype() {}
        // CD2 table 0x8215CAA0: own slots 42..44 precede RetClassName at 45.
        virtual void vf42();
        virtual void vf43();
        virtual void vf44();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual int RetStringID() const;
        virtual void Destruct();
        CD2_LAYOUT_CHECKS(cRoadRaceGameModePrototype, CD2_SIZE(cRoadRaceGameModePrototype, 0x148))
    };
}

#endif
