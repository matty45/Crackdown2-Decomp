// Activity::cActivityVolume (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x823D59F8, from its registrars in CD2's
// initializer run); RuffKing names the class in cActivityVolume.obj. No layout or virtuals are modelled yet.
#ifndef ACTIVITY_CACTIVITYVOLUME_H
#define ACTIVITY_CACTIVITYVOLUME_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace Activity
{
    class cActivityVolume
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcActivityVolumeClass;
    };
}

#endif // ACTIVITY_CACTIVITYVOLUME_H
