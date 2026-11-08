// Equip::cAcidBomblet (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x82200AE0, MakeNew 0x826187D0, SpawnFromPrototype 0x821FFD80, from its registrars in CD2's
// initializer run); RuffKing names the class in cAcidBomblet.obj. No layout or virtuals are modelled yet;
// base Equip::cCWSatchelCharge from CD2's inheritance registrar.
#ifndef EQUIP_CACIDBOMBLET_H
#define EQUIP_CACIDBOMBLET_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "gom/object_prototype.h"
#include "Equip/cCWSatchelCharge.h"

namespace Equip
{
    class cAcidBomblet : public cCWSatchelCharge
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcAcidBombletClass;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
    };
}

#endif // EQUIP_CACIDBOMBLET_H
