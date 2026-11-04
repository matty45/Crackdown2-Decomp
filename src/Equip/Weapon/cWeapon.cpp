// Script registrar source ownership: CD2 initializer 0x82FCBE80 names cWeapon,
// and cleanup 0x8303F398 destroys the same descriptor. Shared interface names are ours.
#include "Equip/cWeapon.h"
#include "fun_runtime/script_type_registrar.h"

namespace Equip
{
    static Fun_Runtime::cScriptTypeRegistrar<cWeapon> cWeaponScriptRegistrar(
        "cWeapon", "cEquipment");
}

#include "cd2/memory.h"

namespace Equip
{
    Fun_Runtime::cClass &cWeapon::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x80, "cWeapon", 0x8C0);
        return *descriptor;
    }
}

namespace Equip
{
    const Fun_Runtime::cClass *cWeapon::ms_pcWeaponClass = &cWeapon::StaticCreateClass();

    const Fun_Runtime::cClass &cWeapon::RetClass() const
    {
        return *ms_pcWeaponClass;
    }
}
