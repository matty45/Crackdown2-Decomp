#include "Prop/cPrismaticProp.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::cAgencyGaragePlatform (Crackdown 2): STAND-IN; derived storage is not modelled yet.
// Base cPrismaticProp: the destructor 0x82736538 calls cPrismaticProp's (0x8273BC98).
// StaticCreateClass (0x827363B0) builds cClass(0x1024, "cAgencyGaragePlatform", 0xEE0); 0xEE0 is the size its registrar gives.
#ifndef UNKNOWN_CAGENCYGARAGEPLATFORM_H
#define UNKNOWN_CAGENCYGARAGEPLATFORM_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cAgencyGaragePlatform : public Prop::cPrismaticProp
    {
    public:
        // CD2 0x827362C0: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 0x82736538.
        virtual ~cAgencyGaragePlatform();
        // CD2 spawning initializer 0x82FF6CA0 names placement factory 0x827362d0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcAgencyGaragePlatformClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2: cAgencyGaragePlatform's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual bool EnterPhysicalState(); // 7: 0x82736628
        virtual void Slot13(); // 13: 0x827365F0
        virtual void vf76(); // 76: 0x82457958
        virtual Fun_Runtime::cClass const & RetClass() const; // cBody 0: 0x82736D40
        virtual bool IsA(Fun_Runtime::cClass const &) const; // cBody 1: 0x82736D48
    protected:
        virtual Fun_Runtime::State * RetSTATE_Min() const; // 351: 0x82736448
        virtual Fun_Runtime::State * RetSTATE_Min(); // 352: 0x82736448
        virtual Fun_Runtime::State * RetSTATE_Max() const; // 353: 0x82736498
        virtual Fun_Runtime::State * RetSTATE_Max(); // 354: 0x82736498
    };
}

#endif // UNKNOWN_CAGENCYGARAGEPLATFORM_H
