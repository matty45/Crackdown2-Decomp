// CD2 constructor 0x827570B0 confirms the shared base constructor chain.
#include "PHYSICS/cBody.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// RPG::cRenegadeOrb (Crackdown 2): STAND-IN: constructor-confirmed base; remaining instance fields are not modelled.
// StaticCreateClass (0x82757018) builds cClass(0x67B, "cRenegadeOrb", 0x3B0); 0x3B0 is the size its registrar gives.
#ifndef RPG_CRENEGADEORB_H
#define RPG_CRENEGADEORB_H

#include "fun_runtime/class.h"

namespace RPG
{
    class cRenegadeOrb : public PHYSICS::cBody
    {
    public:
        // CD2 factory 0x82757000 forwards only this, without a prototype argument.
        cRenegadeOrb();
        // CD2 0x82756FF0: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FFE5C8 names placement factory 0x82757000.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcRenegadeOrbClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // RPG_CRENEGADEORB_H
