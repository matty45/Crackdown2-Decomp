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
        virtual ~cSkillProfile(); // CD2 0x82753888
        // RuffKing's overrides; CD2's primary table 0x82145B70 holds this class's code for them (slot 1: 0x82366F30;
        // slot 9: the shared return-true body 0x8288FB78, where cNonGameBase's table 0x8212CDC0 returns false).
        virtual void HandleAttributes(const RWS::CAttributePacket &attr);
        virtual bool HandleDataInNewDesignBuild() { return true; }

    private:
        unsigned char m_unmodelled7C[0x5A8 - 0x7C];

        CD2_LAYOUT_CHECKS(cSkillProfile, CD2_SIZE(cSkillProfile, 0x5A8))

    };

    // RuffKing's profile pointers (cSkillProfile.cpp, in this order); the destructor (0x82753888) clears the ones at
    // 0x83800FBC, 0x83800FC0, 0x83800FC4 and 0x83800FC8 that point at the dying profile, as RuffKing's does.
    extern cSkillProfile *G_pSkillProfile;
    extern cSkillProfile *G_pFullGameSkillProfile;
    extern cSkillProfile *G_pDemoSkillProfile;
    extern cSkillProfile *G_pDLCSkillProfile;
}

#endif // RPG_CSKILLPROFILE_H
