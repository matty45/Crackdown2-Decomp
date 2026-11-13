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
        virtual void vf269(); virtual void vf270(); virtual void EnterGhostState(); virtual void vf272(); virtual void vf273(); virtual void vf274();
        virtual void vf275(); virtual void vf276(); virtual void vf277(); virtual void vf278(); virtual void vf279(); virtual void vf280();
        virtual void vf281(); virtual void vf282(); virtual void vf283(); virtual void vf284(); virtual void vf285(); virtual void vf286();
        virtual void vf287(); virtual void vf288(); virtual void vf289(); virtual void vf290(); virtual void vf291(); virtual void vf292();
        virtual void vf293(); virtual void vf294(); virtual void vf295(); virtual void vf296(); virtual void vf297(); virtual void vf298();
        virtual void vf299(); virtual void vf300(); virtual void vf301(); virtual void vf302(); virtual void vf303();
    private:
        unsigned char m_unknown298[0x420 - 0x298];
        // CD2: cDynamicBody's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Term(); // 6: 0x822C5828
        virtual bool EnterPhysicalState(); // 7: 0x82605A38
        virtual void Slot13(); // 13: 0x82729CA8
        virtual void Slot14(); // 14: 0x8272C228
        virtual void Slot15(); // 15: 0x82608298
        virtual Fun_Runtime::RetVal Init(GOM::cSpawner const *); // 18: 0x8263ACD0
        virtual void Slot23(); // 23: 0x82325CF8
        virtual void Slot24(); // 24: 0x8272A7F8
        virtual void Slot27(); // 27: 0x821D0000
        virtual bool EnterRenderableState(eResourcesType); // 31: 0x822DC0B0
        virtual void LeaveRenderableState(); // 32: 0x8272A488
        virtual void Slot35(); // 35: 0x82686238
        virtual Fun_Runtime::RetVal Reinitialise(GOM::cSpawner const *); // 38: 0x82688148
        virtual Fun_Runtime::RetVal TermForReuse(); // 39: 0x82688198
        virtual Fun_Runtime::Vec3 RetPosition() const; // 46: 0x82686CE0
        virtual void Slot55(); // 54: 0x826862F0
        virtual void Slot64(); // 63: 0x82689C78
        virtual void vf76(); // 76: 0x8237D638
        virtual void vf86(); // 86: 0x8272B1F0
        virtual void vf87(); // 87: 0x8272B2B0
        virtual void vf91(); // 91: 0x8272B540
        virtual void vf92(); // 92: 0x8272B338
        virtual void vf101(); // 101: 0x82686D08
        virtual void vf102(); // 102: 0x82292150
        virtual void vf107(); // 107: 0x8236E830
        virtual void vf108(); // 108: 0x82269868
        virtual void vf109(); // 109: 0x82687860
        virtual void vf111(); // 111: 0x82209A98
        virtual void vf114(); // 114: 0x82685C48
        virtual void vf115(); // 115: 0x8229DA48
        virtual void vf117(); // 117: 0x8223F228
        virtual void vf118(); // 118: 0x82457988
        virtual void vf119(); // 119: 0x82686D20
        virtual void vf120(); // 120: 0x82271ED0
        virtual void vf121(); // 121: 0x82686D28
        virtual void vf122(); // 122: 0x82457A50
        virtual void vf123(); // 123: 0x8288FB78
        virtual void vf127(); // 127: 0x8272BC10
        virtual void vf134(); // 134: 0x82457A38
        virtual void vf153(); // 153: 0x8272ABE0
        virtual void vf154(); // 154: 0x8272AC18
        virtual void vf158(); // 158: 0x8272ADB0
        virtual void vf159(); // 159: 0x826865E0
        virtual void vf161(); // 161: 0x82686560
        virtual void vf162(); // 162: 0x826866B0
        virtual void vf166(); // 166: 0x8288FB78
        virtual void vf169(); // 169: 0x82685878
        virtual void vf170(); // 170: 0x826858C0
        virtual void vf183(); // 183: 0x82346D60
        virtual void vf204(); // 204: 0x824579F0
        virtual void vf205(); // 205: 0x824579F8
        virtual void vf206(); // 206: 0x82457A00
        virtual void vf207(); // 207: 0x82457A08
        virtual void vf208(); // 208: 0x82457A10
        virtual void vf209(); // 209: 0x82457A18
        virtual void vf210(); // 210: 0x82457A30
        virtual void vf211(); // 211: 0x822C5AB8
        virtual void vf216(); // 216: 0x82685D20
        virtual void vf217(); // 217: 0x82604F40
    protected:
        virtual void UpdateRenderMatrix(); // 26: 0x826DA5B8
    private:
        CD2_LAYOUT_CHECKS(cDynamicBody, CD2_SIZE(cDynamicBody, 0x420))
    };
}
#endif
