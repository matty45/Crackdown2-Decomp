// CD2 constructor 0x8268A4A0 confirms the shared base constructor chain.
#include "gom/game_base.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::cPhantomBody (Crackdown 2): STAND-IN: constructor-confirmed base; remaining instance fields are not modelled.
// StaticCreateClass (0x8268A408) builds cClass(0x7, "cPhantomBody", 0x140); 0x140 is the size its registrar gives.
#ifndef UNKNOWN_CPHANTOMBODY_H
#define UNKNOWN_CPHANTOMBODY_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cPhantomBody : public cGameBase
    {
    public:
        // CD2 factory 0x8268A3F0 forwards only this, without a prototype argument.
        cPhantomBody();
        // CD2 0x8268A2F8: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x8268A3E0: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FE0118 names placement factory 0x8268a3f0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcPhantomBodyClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CPHANTOMBODY_H
