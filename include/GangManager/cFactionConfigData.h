// Hierarchy update (2026-10-28): the historical cConfigBase/B1/B2/List model
// below is superseded by the shared cScriptHost and cSafeDeletable definitions.
// GangManager::cFactionConfigData: per-faction configuration (AR level triggers, faction id, targeting profile link),
// set from RWS attributes. CD2 layout (0x50 bytes), worked out from F07 (ctor), F14 (dtor) and F15:
//   0x00 CAttributeHandler (0x18)
//   0x18 cConfigBase (0x1C bytes): cConfigB1 {vptr, list head} at 0x18, cConfigB2 {vptr, bool} at 0x2C
//   0x34 float[5] level triggers   0x48 faction   0x4C targeting profile link (found by GUID)
// RuffKing's class is 0x34 (CAttributeHandler + DynamicAllocationPolicy + floats + faction + profile ptr); CD2 has a
// polymorphic second base instead. The names cConfigBase/B1/B2/List are ours; the real ones are unknown.
// Vptr evidence: the ctor stores 0x2C three times (B2, cConfigBase, final) and 0x18 twice, the dtor stores 0, 0x18, 0x2C
// and calls the out-of-line destructor of cConfigBase (0x8276F0C0) on this+0x18.
#ifndef GANGMANAGER_CFACTIONCONFIGDATA_H
#define GANGMANAGER_CFACTIONCONFIGDATA_H

#include "rws/attributes.h"
#include "cd2/layout.h"
#include "fun_runtime/scripthost.h"
#include "GangManager/eFactions.h"

namespace GangManager
{
    // Historical stand-in notes, superseded by the shared hierarchy:
    // Circular list head (vptr, next, prev, count); inline constructor in CD2.
    // Destructor of cConfigBase is out of line in CD2. B2 must have no constructor of its own (flag set in cConfigBase's
    // body) or the compiler leaves a dead this+0x2C address computation in the derived constructor.
    // Historical cConfigBase stand-in identified as cScriptHost by CD2's
    // descriptor at 0x8276ED30 and destructor at 0x8276F0C0.
    typedef Fun_Runtime::cScriptHost cConfigBase;
}

namespace AI
{
    class cFactionTargetingProfile;
}

namespace GangManager
{
    class cFactionConfigData : public RWS::CAttributeHandler, public cConfigBase
    {
    public:
        float m_afLevelTriggers[5];
        eFactions m_Faction;
        AI::cFactionTargetingProfile *m_pTargetingProfile;

        static const char *const pcFactionConfigDataClassID;

        virtual const char *RetClassName() const;
        virtual void Destruct();
        __forceinline cFactionConfigData(const RWS::CAttributePacket &) : m_pTargetingProfile(0) {}
        virtual ~cFactionConfigData();
        virtual void HandleAttributes(const RWS::CAttributePacket &);

        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const char *RetRWSClassName();

        CD2_LAYOUT_CHECKS(cFactionConfigData,
            CD2_SIZE(cFactionConfigData, 0x50)
            CD2_OFFSET(cFactionConfigData, m_afLevelTriggers, 0x34)
            CD2_OFFSET(cFactionConfigData, m_Faction, 0x48)
            CD2_OFFSET(cFactionConfigData, m_pTargetingProfile, 0x4C))
    };
}

#endif // GANGMANAGER_CFACTIONCONFIGDATA_H

