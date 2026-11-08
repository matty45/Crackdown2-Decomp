// GOM::cManagerBase (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x82658DB8, from its registrars in CD2's
// initializer run); RuffKing names the class in cManagerBase.obj. No layout or virtuals are modelled yet.
#ifndef GOM_CMANAGERBASE_H
#define GOM_CMANAGERBASE_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace GOM
{
    class cManagerBase
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcManagerBaseClass;
    };
}

#endif // GOM_CMANAGERBASE_H
