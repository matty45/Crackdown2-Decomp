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
        // CD2: cRoadRaceGameModePrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual GameManagement::etGameModeType RetType() const; // 14: 0x82889EA0
        virtual void vf15(); // 15: 0x8288FB78
        virtual void vf16(); // 16: 0x827E56A8
        virtual void vf17(); // 17: 0x8288FB78
        virtual void vf18(); // 18: 0x827E56A8
        virtual void vf19(); // 19: 0x827E56A8
        virtual void vf23(); // 23: 0x827E56A8
        virtual void vf24(); // 24: 0x827E56A8
        virtual void vf25(); // 25: 0x8288FB78
        virtual void vf26(); // 26: 0x82889A60
        virtual void vf33(); // 33: 0x82889EA0
        virtual void vf39(); // 39: 0x8288FB78
        virtual void vf40(); // 40: 0x82854998
    public:
        CD2_LAYOUT_CHECKS(cRoadRaceGameModePrototype, CD2_SIZE(cRoadRaceGameModePrototype, 0x148))
    };
}

#endif
