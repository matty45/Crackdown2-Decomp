#include "fun_runtime/class.h"
// STAND-IN: RuffKing base order; CD2 subobjects at 0x250, 0x294; positional proxy starts at 0x420.
#ifndef CD2_PHYSICS_CDYNAMICBODY_H
#define CD2_PHYSICS_CDYNAMICBODY_H
#include "PHYSICS/cBody.h"
#include "PHYSICS/cIgnitable.h"
#include "Havok/hkEntityActivationListener.h"
namespace PHYSICS
{
    class cDynamicBody : public cBody, public cIgnitable, public hkEntityActivationListener
    {
    public:
        // CD2 0x82684BA8: placement factory.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x82684BD0 registered as RetIsOnFire; cIgnitable owns the flag.
        bool RetIsOnFire() const;
        // CD2 0x82684BC0: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // Name and base from RuffKing. CD2's constructor (0x82686DD8) calls cBodyPrototype's (0x826845A8) and initializes
        // 0x1F0..0x27F; cVehiclePrototype's constructor (0x826D95B8) starts its own fields at 0x280, RuffKing's size.
        class cDynamicBodyPrototype : public cBody::cBodyPrototype
        {
        public:
            cDynamicBodyPrototype(const RWS::CAttributePacket &);

        private:
            unsigned char m_unmodelled1F0[0x280 - 0x1F0];

            CD2_LAYOUT_CHECKS(cDynamicBodyPrototype,
                CD2_SIZE(cDynamicBodyPrototype, 0x280))
        };

        // CD2 0x82684B50 builds the prototype above.
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // CD2 0x82684C80 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcDynamicBodyClass;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual ~cDynamicBody();
        virtual void entityDeactivatedCallback(hkEntity *);
        virtual void entityActivatedCallback(hkEntity *);
        // Primary slots 227..303: cDynamicBody's own virtuals. CD2's cDynamicBody table (0x8200D058, stored by the
        // constructor 0x82685050) has 304 slots. Names are not recovered yet; vfN is the slot index.
        virtual void vf227(); virtual void vf228(); virtual void vf229(); virtual void vf230(); virtual void vf231(); virtual void vf232();
        virtual void vf233(); virtual void vf234(); virtual void vf235(); virtual void vf236(); virtual void vf237(); virtual void vf238();
        virtual void vf239(); virtual void vf240(); virtual void vf241(); virtual void vf242(); virtual void vf243(); virtual void vf244();
        virtual void vf245(); virtual void vf246(); virtual void vf247(); virtual void vf248(); virtual void vf249(); virtual void vf250();
        virtual void vf251(); virtual void vf252(); virtual void vf253(); virtual void vf254(); virtual void vf255(); virtual void vf256();
        virtual void vf257(); virtual void vf258(); virtual void vf259(); virtual void vf260(); virtual void vf261(); virtual void vf262();
        virtual void vf263(); virtual void vf264(); virtual void vf265(); virtual void vf266(); virtual void vf267(); virtual void vf268();
        virtual void vf269(); virtual void vf270(); virtual void vf271(); virtual void vf272(); virtual void vf273(); virtual void vf274();
        virtual void vf275(); virtual void vf276(); virtual void vf277(); virtual void vf278(); virtual void vf279(); virtual void vf280();
        virtual void vf281(); virtual void vf282(); virtual void vf283(); virtual void vf284(); virtual void vf285(); virtual void vf286();
        virtual void vf287(); virtual void vf288(); virtual void vf289(); virtual void vf290(); virtual void vf291(); virtual void vf292();
        virtual void vf293(); virtual void vf294(); virtual void vf295(); virtual void vf296(); virtual void vf297(); virtual void vf298();
        virtual void vf299(); virtual void vf300(); virtual void vf301(); virtual void vf302(); virtual void vf303();
    private:
        unsigned char m_unknown298[0x420 - 0x298];
        CD2_LAYOUT_CHECKS(cDynamicBody, CD2_SIZE(cDynamicBody, 0x420))
    };
}
#endif
