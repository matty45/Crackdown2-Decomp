// RPG::cPvPLevelSetup (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x82763730, from its registrars in CD2's
// initializer run); RuffKing names the class in cPvPSkillset.obj. No layout or virtuals are modelled yet.
#ifndef RPG_CPVPLEVELSETUP_H
#define RPG_CPVPLEVELSETUP_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace RPG
{
    class cPvPLevelSetup
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // RPG_CPVPLEVELSETUP_H
