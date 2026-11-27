#ifndef WorldManager_cWorldManager_H
#define WorldManager_cWorldManager_H

#include "cd2/layout.h"
#include "rws/attributes.h"
#include "fun_runtime/class.h"
#include "gom/non_game_base.h"
#include "GDb/cDebugPageHandler.h"
#include "WorldManager/cEnvironmentWorldMap.h"
#include "fun_runtime/vectorip.h"
#include <algorithm>

namespace WorldManager
{
    class cLOD4Environment;

    // CD2 constructor 0x82278B80 calls cNonGameBase and constructs the debug
    // interface at +0x7C; the release build differs from Burn's base hierarchy.
    class cWorldManager : public cNonGameBase, public GDb::cDebugPageHandler
    {
    public:
        // Returns g_pWorldManager; getter name is ours.
        static cWorldManager *RetInstance();
        // RuffKing's (out of line there, 0x82994CC8: std::find, then erase); CD2 expands it in cLOD4Environment's
        // destructor (0x82807A38).
        void UnregisterLOD4Block(cLOD4Environment *pLOD4Block)
        {
            cLOD4Environment **it = std::find(m_vpLOD4Blocks.begin(), m_vpLOD4Blocks.end(), pLOD4Block);
            if (it != m_vpLOD4Blocks.end())
                m_vpLOD4Blocks.erase(it);
        }
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
        unsigned char m_unmodelled80[0x860 - 0x80];
        // RuffKing's members (+0x8C0 and +0x9D0 there): cLOD4Environment's destructor searches the blocks from +0x870
        // to the end pointer at +0x860; CD2's destructor destroys the map at +0x970.
        Fun_Runtime::cVectorip<cLOD4Environment *, 64> m_vpLOD4Blocks;
        cEnvironmentWorldMap m_WorldMap;
        unsigned char m_unmodelled9A0[0x5DA0 - 0x9A0];

        CD2_LAYOUT_CHECKS(cWorldManager, CD2_SIZE(cWorldManager, 0x5DA0)
            CD2_OFFSET(cWorldManager, m_vpLOD4Blocks, 0x860)
            CD2_OFFSET(cWorldManager, m_WorldMap, 0x970))

    };

    // RuffKing's name (WorldManager::g_pWorldManager); CD2's constructor 0x82278B80 stores the manager at 0x83801548
    // and its destructor clears it.
    extern cWorldManager *g_pWorldManager;
}

#endif
