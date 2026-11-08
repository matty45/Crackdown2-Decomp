// AI::cAttachableLight (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x82456260, MakeNew 0x82456300, from its registrars in CD2's
// initializer run); RuffKing names the class in cAttachableLight.obj. No layout or virtuals are modelled yet;
// base VFX::cPlaceableLight from CD2's inheritance registrar.
#ifndef AI_CATTACHABLELIGHT_H
#define AI_CATTACHABLELIGHT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "VFX/cPlaceableLight.h"

namespace AI
{
    class cAttachableLight : public VFX::cPlaceableLight
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcAttachableLightClass;
    };
}

#endif // AI_CATTACHABLELIGHT_H
