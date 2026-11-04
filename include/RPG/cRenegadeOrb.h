#include "rws/attributes.h"
// RPG::cRenegadeOrb (Crackdown 2): STAND-IN. Base PHYSICS::cBody (its inheritance registrar); fields not modelled.
// StaticCreateClass (0x82757018) builds cClass(0x67B, "cRenegadeOrb", 0x3B0); 0x3B0 is the size its registrar gives.
#ifndef RPG_CRENEGADEORB_H
#define RPG_CRENEGADEORB_H

#include "fun_runtime/class.h"
#include "PHYSICS/cBody.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"

namespace RPG
{
    class cRenegadeOrb : public PHYSICS::cBody
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcRenegadeOrbClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        // Out of line: CD2 0x827570B0 (SpawnFromPrototype tail-calls it).
        cRenegadeOrb();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);

    private:
        unsigned char m_unmodelled250[0x3B0 - 0x250];

        CD2_LAYOUT_CHECKS(cRenegadeOrb, CD2_SIZE(cRenegadeOrb, 0x3B0))
    };
}

#endif // RPG_CRENEGADEORB_H
