// RPG::cPvPSkillsetProfile (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x82763828, from its registrars in CD2's
// initializer run); RuffKing names the class in cPvPSkillset.obj. No layout or virtuals are modelled yet.
#ifndef RPG_CPVPSKILLSETPROFILE_H
#define RPG_CPVPSKILLSETPROFILE_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include <xtl.h>

namespace RPG
{
    class cPvPLevelSetup;
    class cPvPSkillsetProfile;
    // Burn's cPvPSkillset.cpp names the singleton; CD2 0x82763828 stores it at 0x83800FDC.
    extern cPvPSkillsetProfile *g_pPvPSkillSetProfile;
    class cPvPSkillsetProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // Burn names the base and virtuals; CD2 table 0x82145F70 confirms slot 11.
        // CD2 inlines this constructor into MakeNew.
        cPvPSkillsetProfile(const RWS::CAttributePacket &);
        virtual ~cPvPSkillsetProfile();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual const char *RetClassName() const;
        virtual void Destruct();

    private:
        // Burn member names; CD2 factory clears the rank pointer at +0x18 and
        // the six skill pointers at +0x1C using a separate 24-byte fill call.
        cPvPLevelSetup *m_pRankLevelData;
        cPvPLevelSetup *m_apSkillLevelData[6];

        CD2_LAYOUT_CHECKS(cPvPSkillsetProfile,
            CD2_SIZE(cPvPSkillsetProfile, 0x34)
            CD2_OFFSET(cPvPSkillsetProfile, m_pRankLevelData, 0x18)
            CD2_OFFSET(cPvPSkillsetProfile, m_apSkillLevelData, 0x1C))
    };
}

#endif // RPG_CPVPSKILLSETPROFILE_H
