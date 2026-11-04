#include "Prop/cPrismaticProp.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::cLift (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82738F88) builds cClass(0x102B, "cLift", 0xF30); 0xF30 is the size its registrar gives.
#ifndef UNKNOWN_CLIFT_H
#define UNKNOWN_CLIFT_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cLift
    {
    public:
        // Prototype name ours, from cLift::MakeNew (0x82738E98).
        // CD2 confirms the shared parent constructor and Init slot 5 (0x8273A680).
        // Interface only: this does not describe instance fields or allocation size.
        class cLiftPrototype : public Prop::cPrismaticProp::cPrismaticPropPrototype
        {
        public:
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        };

        // CD2 0x82738E28: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x82738F18: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FF7828 names placement factory 0x82738f28.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcLiftClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CLIFT_H
