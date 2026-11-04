#include "cd2/layout.h"
#include "rws/attributes.h"
// RPG::cSkillProfile (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's header;
// RetClassName (0x827534F8) is slot 11 of the vtable at 0x82145B70, as cNonGameBase's RetClassName.
#ifndef RPG_CSKILLPROFILE_H
#define RPG_CSKILLPROFILE_H

#include "gom/non_game_base.h"

namespace RPG
{
    class cSkillProfile : public cNonGameBase
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcSkillProfileClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x827535A0 (MakeNew calls it with the packet).
        cSkillProfile(const RWS::CAttributePacket &packet);

    private:
        unsigned char m_unmodelled7C[0x5A8 - 0x7C];

        CD2_LAYOUT_CHECKS(cSkillProfile, CD2_SIZE(cSkillProfile, 0x5A8))

    };
}

#endif // RPG_CSKILLPROFILE_H
