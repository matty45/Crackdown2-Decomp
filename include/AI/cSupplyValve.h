#include "gom/object_prototype.h"
#include "rws/attributes.h"
// AI::cSupplyValve (Crackdown 2): STAND-IN for the class name only. Base Prop::cSpinningProp, as in RuffKing's header;
// RetClassName (0x82457C10) is slot 11 of the vtable at 0x82102438, as cNonGameBase's RetClassName.
#ifndef AI_CSUPPLYVALVE_H
#define AI_CSUPPLYVALVE_H

#include "Prop/cSpinningProp.h"

namespace AI
{
    class cSupplyValve : public Prop::cSpinningProp
    {
    public:
        // Prototype interface from RuffKing; CD2 slot 5 at 0x82457DE0. Instance fields are not modelled.
        class cSupplyValvePrototype : public Prop::cSpinningProp::cSpinningPropPrototype
        {
        public:
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        };

        // CD2 spawning initializer 0x82F866D0 names placement factory 0x82457c20.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcSupplyValveClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
        // CD2 0x822C8900.
        virtual ~cSupplyValve();
    };
}

#endif // AI_CSUPPLYVALVE_H
