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

        CD2_LAYOUT_CHECKS(cTurretBase,
            CD2_SIZE(cTurretBase, 0x1080)
            CD2_OFFSET(cTurretBase, m_pWeapon, 0xE30)
            CD2_OFFSET(cTurretBase, m_pUsingCharacter, 0xE40))
    };
}

#endif // PROP_CTURRETBASE_H
