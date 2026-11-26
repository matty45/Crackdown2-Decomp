#ifndef WorldManager_cWorldManager_H
#define WorldManager_cWorldManager_H

#include "cd2/layout.h"
#include "rws/attributes.h"
#include "fun_runtime/class.h"
#include "gom/non_game_base.h"
#include "GDb/cDebugPageHandler.h"
#include "WorldManager/cEnvironmentWorldMap.h"

namespace WorldManager
{
    // CD2 constructor 0x82278B80 calls cNonGameBase and constructs the debug
    // interface at +0x7C; the release build differs from Burn's base hierarchy.
    class cWorldManager : public cNonGameBase, public GDb::cDebugPageHandler
    {
    public:
        // CD2 constructor 0x82278B80 stores this at 0x83801548; getter name is ours.
        static cWorldManager *RetInstance();
    private:
        static cWorldManager *ms_pInstance;
    public:
        // CD2 0x82809B30: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcWorldManagerClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
        // CD2 0x82809A68 / 0x82809A78: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
    public:
        // Out of line: CD2 0x82278B80 (MakeNew calls it).
        cWorldManager();
        virtual ~cWorldManager(); // CD2 0x82809E00
        // RuffKing's overrides; CD2's tables hold this class's code for them (primary 0x82009368 slot 1: 0x82809ED8;
        // CEventHandler table 0x821558A8 slot 5: 0x8220A960).
        virtual void HandleAttributes(const RWS::CAttributePacket &attr);
        virtual void HandleEvents(RWS::CMsg &pMsg);

    private:
        unsigned char m_unmodelled80[0x970 - 0x80];
        // RuffKing's member (+0x9D0 there); CD2's destructor destroys it at +0x970.
        cEnvironmentWorldMap m_WorldMap;
        unsigned char m_unmodelled9A0[0x5DA0 - 0x9A0];

        CD2_LAYOUT_CHECKS(cWorldManager, CD2_SIZE(cWorldManager, 0x5DA0)
            CD2_OFFSET(cWorldManager, m_WorldMap, 0x970))

    };
}

#endif
