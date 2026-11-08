// RPG::cSkillSet (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x827539D0, from its registrars in CD2's
// initializer run); RuffKing names the class in cSkillSet.obj. No layout or virtuals are modelled yet;
// base GDb::cDebugPageHandler from CD2's inheritance registrar.
#ifndef RPG_CSKILLSET_H
#define RPG_CSKILLSET_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "GDb/cDebugPageHandler.h"

namespace RPG
{
    class cSkillSet : public GDb::cDebugPageHandler
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcSkillSetClass;
    };
}

#endif // RPG_CSKILLSET_H
