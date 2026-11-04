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
        // Prototype name ours, from cBeaconProp::MakeNew (0x8245C200).
        // CD2 confirms the shared parent constructor and Init slot 5 (0x8245C460).
        // Interface only: this does not describe instance fields or allocation size.
        class cBeaconPropPrototype : public Prop::cProp::cPropPrototype
        {
        public:
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        };

        // CD2 spawning initializer 0x82F87CA8 names placement factory 0x8245c288.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcBeaconPropClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // AI_CBEACONPROP_H
