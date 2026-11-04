#include "gom/game_base.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::cSupplyEntryPoint (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8273FC98) builds cClass(0x101F, "cSupplyEntryPoint", 0x140); 0x140 is the size its registrar gives.
#ifndef UNKNOWN_CSUPPLYENTRYPOINT_H
#define UNKNOWN_CSUPPLYENTRYPOINT_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cSupplyEntryPoint
    {
    public:
        // Prototype name ours, from cSupplyEntryPoint::MakeNew (0x8273FB08).
        // CD2 confirms the shared parent constructor and Init slot 5 (0x82740858).
        // Interface only: this does not describe instance fields or allocation size.
        class cSupplyEntryPointPrototype : public cGameBase::cGameBasePrototype
        {
        public:
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        };

        // CD2 0x8273FA98: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x8273FB98: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FF9598 names placement factory 0x8273fbc0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcSupplyEntryPointClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CSUPPLYENTRYPOINT_H
