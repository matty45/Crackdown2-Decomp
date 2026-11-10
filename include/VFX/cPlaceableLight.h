// VFX::cPlaceableLight (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x82801D78, MakeNew 0x82801E18, from its registrars in CD2's
// initializer run); RuffKing names the class in cPlaceableLight.obj. No layout or virtuals are modelled yet;
// base Activity::cSpawnPoint from CD2's inheritance registrar.
// Reconstruction update: the shared spawn-point chain and the light's own two fields are now modelled below.
#ifndef VFX_CPLACEABLELIGHT_H
#define VFX_CPLACEABLELIGHT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSpawnPoint.h"

namespace VFX
{
    class cGlobalLight;
    class cPlaceableLight : public Activity::cSpawnPoint
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcPlaceableLightClass;
        // CD2 0x82801E18 calls cSpawnPoint() and initializes these two own fields.
        cPlaceableLight();
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual ~cPlaceableLight();
        virtual cNonGameBase *Spawn();
        virtual void SetInAV(Activity::cActivityVolume *, bool);

    protected:
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // RuffKing member names; CD2 stores the type at +0x70 and light pointer at +0x74.
        char m_nLightType;
        cGlobalLight *m_pLight;

        CD2_LAYOUT_CHECKS(cPlaceableLight,
            CD2_SIZE(cPlaceableLight, 0x80)
            CD2_OFFSET(cPlaceableLight, m_nLightType, 0x70)
            CD2_OFFSET(cPlaceableLight, m_pLight, 0x74))
    };
}

#endif // VFX_CPLACEABLELIGHT_H
