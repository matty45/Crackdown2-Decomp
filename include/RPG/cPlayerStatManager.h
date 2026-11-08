// RPG::cPlayerStatManager (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x82759848, from its registrars in CD2's
// initializer run); RuffKing names the class in cPlayerStatManager.obj. No layout or virtuals are modelled yet;
// base GDb::cDebugPageHandler from CD2's inheritance registrar.
#ifndef RPG_CPLAYERSTATMANAGER_H
#define RPG_CPLAYERSTATMANAGER_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "GDb/cDebugPageHandler.h"

namespace RPG
{
    class cPlayerStatManager : public GDb::cDebugPageHandler
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcPlayerStatManagerClass;
    };
}

#endif // RPG_CPLAYERSTATMANAGER_H
