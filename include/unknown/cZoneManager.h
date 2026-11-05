#include "rws/attributes.h"
// unknown::cZoneManager (Crackdown 2): interface stand-in. CD2 destructor 0x8280BDE8
// restores cDebugPageHandler at +0x7C (base table 0x8212DC9C), then calls ~cNonGameBase.
// Instance fields are opaque; the allocation size is established by CD2's factory.
// StaticCreateClass (0x8280B9D8) builds cClass(0x60E, "cZoneManager", 0x84); 0x84 is the size its registrar gives.
#ifndef UNKNOWN_CZONEMANAGER_H
#define UNKNOWN_CZONEMANAGER_H

#include "fun_runtime/class.h"
#include "gom/non_game_base.h"
#include "GDb/cDebugPageHandler.h"
#include "unknown/cPopulationZonePool.h"

namespace unknown
{
    class cZoneManager : public cNonGameBase, public GDb::cDebugPageHandler
    {
    public:
        // CD2 0x8280BC48: the allocation factory calls this constructor out of line.
        cZoneManager();
        virtual ~cZoneManager(); // CD2 0x8280BDE8
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        // Descriptive names are ours. CD2 destructor 0x8280BDE8 clears this singleton.
        static cZoneManager *RetInstance();
    private:
        static cZoneManager *ms_pInstance;
    public:
        // CD2 0x8280B9C8: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 0x8280B900: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x8280B9B8: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcZoneManagerClass;
        static Fun_Runtime::cClass &StaticCreateClass();

    private:
        // Descriptor and factory allocation agree on the complete size; own fields remain unrecovered.
        cPopulationZonePool *m_pPopulationZonePool;
        CD2_LAYOUT_CHECKS(cZoneManager,
            CD2_SIZE(cZoneManager, 0x84)
            CD2_OFFSET(cZoneManager, m_pPopulationZonePool, 0x80))
    };
}

#endif // UNKNOWN_CZONEMANAGER_H
