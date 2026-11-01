#include "rws/attributes.h"
// RPG::cRenegadeOrb (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82757018) builds cClass(0x67B, "cRenegadeOrb", 0x3B0); 0x3B0 is the size its registrar gives.
#ifndef RPG_CRENEGADEORB_H
#define RPG_CRENEGADEORB_H

#include "fun_runtime/class.h"

namespace RPG
{
    class cRenegadeOrb
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcRenegadeOrbClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // RPG_CRENEGADEORB_H
