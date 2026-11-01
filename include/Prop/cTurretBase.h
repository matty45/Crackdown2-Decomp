// Prop::cTurretBase (Crackdown 2): STAND-IN for the class name only. Base Prop::cProp, as in RuffKing's header;
// RetClassName (0x82747FD8) is slot 11 of the vtable at 0x82144C88, as cNonGameBase's RetClassName.
#ifndef PROP_CTURRETBASE_H
#define PROP_CTURRETBASE_H

#include "Prop/cProp.h"
#include "fun_runtime/safedeletablepointer.h"

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
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
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
