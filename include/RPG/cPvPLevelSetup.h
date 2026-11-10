// RPG::cPvPLevelSetup (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x82763730, from its registrars in CD2's
// initializer run); RuffKing names the class in cPvPSkillset.obj. No layout or virtuals are modelled yet.
#ifndef RPG_CPVPLEVELSETUP_H
#define RPG_CPVPLEVELSETUP_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "editor/guid_event_handler.h"
#include "fun_runtime/stringc.h"
#include <xtl.h>

namespace RPG
{
    class cPvPLevelSetup : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // Burn names the base and virtuals; CD2 table 0x82145F3C confirms slot 11.
        // CD2 inlines construction and preserves its external array-fill call.
        __forceinline cPvPLevelSetup(const RWS::CAttributePacket &)
        {
            XMemSet(m_aLevelThresholds, 0, sizeof(m_aLevelThresholds));
        }
        virtual ~cPvPLevelSetup();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual const char *RetClassName() const;
        virtual void Destruct();

    private:
        // Burn's named layout agrees with CD2 0x82763730: GUID handler, 49
        // thresholds cleared at +0x2C, then the default narrow string at +0xF0.
        Editor::cGUIDEventHandler<cPvPLevelSetup> m_EventHandler;
        unsigned int m_aLevelThresholds[49];
        Fun_Runtime::cStringc m_sLocPartialName;

        CD2_LAYOUT_CHECKS(cPvPLevelSetup,
            CD2_SIZE(cPvPLevelSetup, 0x10C)
            CD2_OFFSET(cPvPLevelSetup, m_EventHandler, 0x18)
            CD2_OFFSET(cPvPLevelSetup, m_aLevelThresholds, 0x2C)
            CD2_OFFSET(cPvPLevelSetup, m_sLocPartialName, 0xF0))
    };
}

#endif // RPG_CPVPLEVELSETUP_H
