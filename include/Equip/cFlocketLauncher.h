// Equip::cFlocketLauncher (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82630F08) builds cClass(0x605F, "cFlocketLauncher", 0xA30); 0xA30 is the size its registrar gives.
#ifndef EQUIP_CFLOCKETLAUNCHER_H
#define EQUIP_CFLOCKETLAUNCHER_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cFlocketLauncher
    {
    public:
        static const Fun_Runtime::cClass *ms_pcFlocketLauncherClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CFLOCKETLAUNCHER_H
