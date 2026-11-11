// Prop::cTurretBase (Crackdown 2): STAND-IN for the class name only. Base Prop::cProp, as in RuffKing's header;
// RetClassName (0x82747FD8) is slot 11 of the vtable at 0x82144C88, as cNonGameBase's RetClassName.
#ifndef PROP_CTURRETBASE_H
#define PROP_CTURRETBASE_H

#include "Prop/cProp.h"
#include "fun_runtime/safedeletablepointer.h"
#include "fun_runtime/retval.h"

namespace Equip { class cWeapon; }
namespace CHARACTER { class cCharacter; }

// Descriptive name: CD2 0x82887D38 removes the object's entry from both per-type registries,
// destroys its registration record, and returns whether an entry was found.
bool RemoveObjectTypeRegistration(int type, cNonGameBase *object);

namespace Prop
{
    class cTurretBase : public Prop::cProp
    {
    public:
        virtual ~cTurretBase();
        // CD2 placement factory 0x82747FE8 tail-calls constructor 0x82748248.
        cTurretBase(GOM::cObjectPrototype *);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // RuffKing names; CD2 MakeNew (0x82747F68) allocates 0x500 bytes and only
        // invokes cPropPrototype's constructor before installing the derived vtables.
        class cTurretBasePrototype : public cProp::cPropPrototype
        {
        public:
            cTurretBasePrototype(const RWS::CAttributePacket &packet) : cPropPrototype(packet) {}
            // CD2 prototype vtable slot 5, 0x827480A0.
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
            virtual void HandleAttributes(const RWS::CAttributePacket &);
            float m_fTurretRotAccel;
            float m_fGunRotAccel;
            float m_fTurretRotSpeed;
            float m_fGunRotSpeed;

            CD2_LAYOUT_CHECKS(cTurretBasePrototype,
                CD2_SIZE(cTurretBasePrototype, 0x500)
                CD2_OFFSET(cTurretBasePrototype, m_fTurretRotAccel, 0x4F0)
                CD2_OFFSET(cTurretBasePrototype, m_fGunRotAccel, 0x4F4)
                CD2_OFFSET(cTurretBasePrototype, m_fTurretRotSpeed, 0x4F8)
                CD2_OFFSET(cTurretBasePrototype, m_fGunRotSpeed, 0x4FC))
        };
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcTurretBaseClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;

    private:
        // RuffKing names; CD2 0x827485B0 destroys these safe pointers at 0xE40 then 0xE30.
        Fun_Runtime::cSafeDeletablePointer<Equip::cWeapon> m_pWeapon;
        Fun_Runtime::cSafeDeletablePointer<CHARACTER::cCharacter> m_pUsingCharacter;
        unsigned char m_unknownE50[0x1080 - 0xE50];

        // CD2: cTurretBase's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Term(); // 6: 0x827488D0
        virtual bool EnterPhysicalState(); // 7: 0x82748A08
        virtual void Slot14(); // 14: 0x827489C0
        virtual void Slot23(); // 23: 0x8274B008
        virtual bool EnterRenderableState(eResourcesType); // 31: 0x82748B10
        virtual void Slot61(); // 60: 0x8274BA40
        virtual void vf76(); // 76: 0x82748BB8
        virtual void vf196(); // 196: 0x82748940
        virtual unsigned short RetCollisionSystemGroup(); // 197: 0x82748990
        virtual void vf226(); // 226: 0x8274BB58
        virtual void vf235(); // 235: 0x8274BC28
        virtual void vf236(); // 236: 0x8274BBC8
        virtual void CalculateLOD(int); // cReplicatedClass 3: 0x8274BAF0
        virtual void ReplicateInitialFields(); // cReplicatedClass 8: 0x8274B0F0
        virtual void ReplicateFields(); // cReplicatedClass 9: 0x8274B2B0
        virtual void SetPingedFieldStatesForNode(unsigned char); // cReplicatedClass 20: 0x8274B268
        virtual unsigned int GetMaxReplicatedFields() const; // cReplicatedClass 23: 0x8288EA78
    private:
        // CD2: cTurretBase's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void vf272(); // 272: 0x82686318
    private:
        CD2_LAYOUT_CHECKS(cTurretBase,
            CD2_SIZE(cTurretBase, 0x1080)
            CD2_OFFSET(cTurretBase, m_pWeapon, 0xE30)
            CD2_OFFSET(cTurretBase, m_pUsingCharacter, 0xE40))

    public:
        // CD2 table 0x82144C88 differs from cProp at these inherited slots.
        virtual Fun_Runtime::RetVal Init(const GOM::cSpawner *); // slot 18: 0x827486E8
    };
}

#endif // PROP_CTURRETBASE_H
