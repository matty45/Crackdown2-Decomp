#include "rws/attributes.h"
// unknown::cExplosivesSkillProfile (Crackdown 2): STAND-IN with only what its matched functions need; its bases are not modelled yet.
// Its class-factory registrar (0x82FFD408) registers "cExplosivesSkillProfile" with MakeNew (0x827530D0) and size 0xA4.
#ifndef UNKNOWN_CEXPLOSIVESSKILLPROFILE_H
#define UNKNOWN_CEXPLOSIVESSKILLPROFILE_H

namespace unknown
{
    class cExplosivesSkillProfile
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // UNKNOWN_CEXPLOSIVESSKILLPROFILE_H
