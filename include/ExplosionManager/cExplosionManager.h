// ExplosionManager::cExplosionManager (Crackdown 2): STAND-IN. Bases cNonGameBase and GDb::cDebugPageHandler, as in
// RuffKing's header; RetClassName (0x8263EB98) is slot 11 of the vtable at 0x8212BAC8, as cNonGameBase's RetClassName,
// and the destructor (0x8263EBF8) restores the debug handler's three-slot table 0x8212BC28 at +0x7C. Fields are
// modelled up to the level-info vector only.
#ifndef EXPLOSIONMANAGER_CEXPLOSIONMANAGER_H
#define EXPLOSIONMANAGER_CEXPLOSIONMANAGER_H

#include "fun_runtime/class.h"
#include "gom/non_game_base.h"
#include "GDb/cDebugPageHandler.h"
#include "fun_runtime/vectorip.h"

namespace ExplosionManager
{
    class cExplosive;
    class cExplosionLevelInfo;

    class cExplosionManager : public cNonGameBase, public GDb::cDebugPageHandler
    {
    public:
        // RuffKing's (out of line there); CD2 inlines both: cExplosiveGrenade::RetDamageRadius (0x8261DAD0) reads the
        // singleton at 0x83800C30 and the level's entry of the vector whose storage starts at +0xA0.
        static cExplosionManager *RetExplosionManager() { return ms_pSingleton; }
        cExplosionLevelInfo *RetLevelInfo(unsigned int nLevel) { return m_vpExplosion[nLevel]; }
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcExplosionManagerClass;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        // CD2 0x8263EAE0 / 0x8263EAF0: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;

    private:
        static cExplosionManager *ms_pSingleton;
        // RuffKing's names and order after the bases; the destructor builds the list at +0x80.
        unsigned int m_lpExplosive[3];  // RuffKing: cList<cExplosive *>; not modelled
        Fun_Runtime::cVectorip<cExplosionLevelInfo *, 15> m_vpExplosion;

        CD2_LAYOUT_CHECKS(cExplosionManager,
            CD2_OFFSET(cExplosionManager, m_lpExplosive, 0x80)
            CD2_OFFSET(cExplosionManager, m_vpExplosion, 0x90))
    };
}

#endif // EXPLOSIONMANAGER_CEXPLOSIONMANAGER_H
