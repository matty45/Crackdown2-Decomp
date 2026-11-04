// STAND-IN: RuffKing names cGrenade as the base; CD2 constructor 0x8260B288 (inlined factory)
// confirms that constructor chain. Descriptor 0x822F33C8 gives complete size 0x9C0.
// Instance data beyond the recovered base is opaque; no field offsets are inferred from it.
#ifndef EQUIP_CCLOAKINGDEVICE_H
#define EQUIP_CCLOAKINGDEVICE_H
#include "Equip/cGrenade.h"
namespace Equip
{
    class cCloakingDevice : public cGrenade
    {
    public:
        // RuffKing prototype name/base; CD2 Init is primary slot 5 (0x8260BA80).
        // Interface only: instance fields and allocation size remain unrecovered.
        class cCloakingDevicePrototype : public cGrenade::cGrenadePrototype
        {
        public:
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        };

        // CD2 0x8260B278: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcCloakingDeviceClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        CD2_LAYOUT_CHECKS(cCloakingDevice, CD2_SIZE(cCloakingDevice, 0x9C0))
    };
}
#endif
