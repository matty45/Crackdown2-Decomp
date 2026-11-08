// GOM::cLimboListManager (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x826582A0, from its registrars in CD2's
// initializer run); RuffKing names the class in cLimboListManager.obj. No layout or virtuals are modelled yet;
// base GOM::cManagerBase from CD2's inheritance registrar.
#ifndef GOM_CLIMBOLISTMANAGER_H
#define GOM_CLIMBOLISTMANAGER_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "gom/cManagerBase.h"

namespace GOM
{
    class cLimboListManager : public cManagerBase
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcLimboListManagerClass;
    };
}

#endif // GOM_CLIMBOLISTMANAGER_H
