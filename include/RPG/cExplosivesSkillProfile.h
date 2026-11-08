#include "fun_runtime/class.h"
#include "rws/attributes.h"
// RPG::cExplosivesSkillProfile (Crackdown 2): STAND-IN with only what its matched functions need; its bases are not modelled yet.
// Namespace from RuffKing's RPG/cExplosivesSkillProfile.h (base cNonGameBase there; CD2's inheritance registrar 0x82FFD3A0 agrees).
// Burn has it in CHARACTER without the cNonGameBase base, so CD2 follows RuffKing's version.
// Its class-factory registrar (0x82FFD408) registers "cExplosivesSkillProfile" with MakeNew (0x827530D0) and size 0xA4.
#ifndef RPG_CEXPLOSIVESSKILLPROFILE_H
#define RPG_CEXPLOSIVESSKILLPROFILE_H

namespace RPG
{
    class cExplosivesSkillProfile
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcExplosivesSkillProfileClass;
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // RPG_CEXPLOSIVESSKILLPROFILE_H
