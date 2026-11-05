#include "rws/attributes.h"
// unknown::cScriptManager (Crackdown 2): interface stand-in. CD2 constructor 0x82770388
// calls cNonGameBase and installs cDebugPageHandler at +0x7C (base table 0x8212DC9C).
// String storage is recovered from its constructor/destructor; other fields remain opaque.
// StaticCreateClass (0x82770218) builds cClass(0x60B, "cScriptManager", 0x430); 0x430 is the size its registrar gives.
#ifndef UNKNOWN_CSCRIPTMANAGER_H
#define UNKNOWN_CSCRIPTMANAGER_H

#include "fun_runtime/class.h"
#include "gom/non_game_base.h"
#include "GDb/cDebugPageHandler.h"
#include "fun_runtime/stringc.h"
#include "fun_runtime/vector.h"
#include "rws/eventid.h"

namespace unknown
{
    // Names from CD2's constructor registrations; declaration scope is ours.
    extern RWS::CEventId iMsgScriptManagerBeginPlay;
    extern RWS::CEventId iMsgScriptManagerEndPlay;
    class cScriptManager : public cNonGameBase, public GDb::cDebugPageHandler
    {
    public:
        // CD2 0x82770388: the allocation factory calls this constructor out of line.
        cScriptManager();
        virtual ~cScriptManager(); // CD2 0x827705D8
        // CD2's installed tables identify these overrides, but their bodies at
        // 0x82770140/0x82770150 lie outside the scaffolded source range.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        // CD2 0x82770208: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 0x827701F8: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcScriptManagerClass;
        static Fun_Runtime::cClass &StaticCreateClass();

    private:
        // Descriptive member names are ours. Constructor/destructor strides prove
        // the 32 0x1C-byte strings and the string-vector layout at +0x418.
        Fun_Runtime::cStringc m_ScriptNames[32];
        unsigned char m_unmodelled400[0x418 - 0x400];
        std::vector<Fun_Runtime::cStringc> m_SearchPaths;
        unsigned char m_unmodelled428[8];
        static cScriptManager *ms_pInstance;
        CD2_LAYOUT_CHECKS(cScriptManager,
            CD2_SIZE(cScriptManager, 0x430)
            CD2_OFFSET(cScriptManager, m_ScriptNames, 0x80)
            CD2_OFFSET(cScriptManager, m_SearchPaths, 0x418))
    };
}

#endif // UNKNOWN_CSCRIPTMANAGER_H
