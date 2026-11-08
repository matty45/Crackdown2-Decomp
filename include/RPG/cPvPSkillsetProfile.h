// RPG::cPvPSkillsetProfile (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x82763828, from its registrars in CD2's
// initializer run); RuffKing names the class in cPvPSkillset.obj. No layout or virtuals are modelled yet.
#ifndef RPG_CPVPSKILLSETPROFILE_H
#define RPG_CPVPSKILLSETPROFILE_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace RPG
{
    class cPvPSkillsetProfile
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // RPG_CPVPSKILLSETPROFILE_H
