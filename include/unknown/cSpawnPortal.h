#include "Prop/cHingedProp.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::cSpawnPortal (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8273E150) builds cClass(0x1025, "cSpawnPortal", 0xEC0); 0xEC0 is the size its registrar gives.
#ifndef UNKNOWN_CSPAWNPORTAL_H
#define UNKNOWN_CSPAWNPORTAL_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cSpawnPortal
    {
    public:
        // Prototype name ours, from cSpawnPortal::MakeNew (0x8273DFE8).
        // CD2 confirms the shared parent constructor and Init slot 5 (0x8273E538).
        // Interface only: this does not describe instance fields or allocation size.
        class cSpawnPortalPrototype : public Prop::cHingedProp::cHingedPropPrototype
        {
        public:
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        };

        // CD2 0x8273DF78: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x8273E058: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FF8CC8 names placement factory 0x8273e068.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcSpawnPortalClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CSPAWNPORTAL_H
