#ifndef WorldManager_cWorldManager_H
#define WorldManager_cWorldManager_H

#include "cd2/layout.h"
#include "rws/attributes.h"
#include "fun_runtime/class.h"
#include "gom/non_game_base.h"
#include "GDb/cDebugPageHandler.h"

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
    public:
        // Out of line: CD2 0x82278B80 (MakeNew calls it).
        cWorldManager();

    private:
        unsigned char m_unmodelled80[0x5DA0 - 0x80];

        CD2_LAYOUT_CHECKS(cWorldManager, CD2_SIZE(cWorldManager, 0x5DA0))

    };
}

#endif
