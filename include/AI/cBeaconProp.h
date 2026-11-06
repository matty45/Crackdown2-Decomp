#include "Prop/cProp.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// AI::cBeaconProp (Crackdown 2): STAND-IN for the class name only. Base AI::cMissionCriticalProp, as in RuffKing's
// header; RetClassName (0x8245C278) is slot 11 of the vtable at 0x82103748, as cNonGameBase's RetClassName.
#ifndef AI_CBEACONPROP_H
#define AI_CBEACONPROP_H

#include "AI/cMissionCriticalProp.h"

namespace AI
{
    class cBeaconProp : public AI::cMissionCriticalProp
    {
    public:
        // RuffKing: cBeaconPropPrototype : cMissionCriticalPropPrototype, 1280 bytes. CD2's MakeNew (0x8245C200)
        // allocates 0x500, calls cPropPrototype's constructor and stores this class's vptrs and the base's zero at
        // 0x4F0: both derived constructors are inline. Init is slot 5 (0x8245C460).
        class cBeaconPropPrototype : public cMissionCriticalProp::cMissionCriticalPropPrototype
        {
        public:
            __forceinline cBeaconPropPrototype(const RWS::CAttributePacket &packet)
                : cMissionCriticalProp::cMissionCriticalPropPrototype(packet) {}
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

            CD2_LAYOUT_CHECKS(cBeaconPropPrototype,
                CD2_SIZE(cBeaconPropPrototype, 0x500))
        };

        // CD2 spawning initializer 0x82F87CA8 names placement factory 0x8245c288.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x8245C470: the placement factory (0x8245C288) calls it out of line with the prototype.
        cBeaconProp(GOM::cObjectPrototype *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcBeaconPropClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // AI_CBEACONPROP_H
