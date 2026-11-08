// VFX::cPlaceableLight (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x82801D78, MakeNew 0x82801E18, from its registrars in CD2's
// initializer run); RuffKing names the class in cPlaceableLight.obj. No layout or virtuals are modelled yet;
// base Activity::cSpawnPoint from CD2's inheritance registrar.
#ifndef VFX_CPLACEABLELIGHT_H
#define VFX_CPLACEABLELIGHT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSpawnPoint.h"

namespace VFX
{
    class cPlaceableLight : public Activity::cSpawnPoint
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcPlaceableLightClass;
    };
}

#endif // VFX_CPLACEABLELIGHT_H
