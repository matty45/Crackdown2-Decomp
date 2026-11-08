#include "fun_runtime/class.h"
#include "rws/attributes.h"
// Activity::cLongDistancePropManager (Crackdown 2): STAND-IN. Bases cNonGameBase and GDb::cDebugPageHandler (at 0x7C) as in
// RuffKing's header. CD2's MakeNew (0x823DA790) inlines the constructor: cNonGameBase's constructor, the cDebugPageHandler
// vptr then this class's vptrs, an empty spawn-point vector at 0x80, m_nMaxProps at 0x90, a link to RWS::iMsgRunningTick
// and the g_pLongDistancePropManager store; the destructor (0x823DA8D8) unlinks the message and destroys the vector.
// RetClassName (0x823DA878) is slot 11 of the vtable at 0x820FA250.
#ifndef ACTIVITY_CLONGDISTANCEPROPMANAGER_H
#define ACTIVITY_CLONGDISTANCEPROPMANAGER_H

#include "gom/non_game_base.h"
#include "GDb/cDebugPageHandler.h"
#include "fun_runtime/vector.h"
#include "rws/logic.h"
#include "cd2/layout.h"

namespace Activity
{
    class cSpawnPoint;
    class cLongDistancePropManager;

    // RuffKing's singleton pointer (CD2 0x83739060, set by the constructor).
    extern cLongDistancePropManager *g_pLongDistancePropManager;

    class cLongDistancePropManager : public cNonGameBase, public GDb::cDebugPageHandler
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        // __forceinline: CD2's MakeNew inlines this constructor; /Ob1 declines a plain inline constructor with this many
        // stores (docs/matching-notes.md, Inlining).
        __forceinline cLongDistancePropManager(const RWS::CAttributePacket &) : m_nMaxProps(0)
        {
            LinkMsg(RWS::iMsgRunningTick, 0, 0x8000);
            g_pLongDistancePropManager = this;
        }
        virtual ~cLongDistancePropManager();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // CD2 registered-class vtable 0x820FA378 slot 0, descriptor at 0x83802BF8.
        static const Fun_Runtime::cClass *ms_pcLongDistancePropManagerClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x823DA730: registered-class virtual slot 1.
        virtual bool IsA(const Fun_Runtime::cClass &c) const;
        virtual const char *RetClassName() const;

    protected:
        Fun_Runtime::cVector<cSpawnPoint *> m_vpSpawnPoints;
        unsigned short m_nMaxProps;

        CD2_LAYOUT_CHECKS(cLongDistancePropManager,
            CD2_SIZE(cLongDistancePropManager, 0x94)
            CD2_OFFSET(cLongDistancePropManager, m_vpSpawnPoints, 0x80)
            CD2_OFFSET(cLongDistancePropManager, m_nMaxProps, 0x90))
    };
}

#endif // ACTIVITY_CLONGDISTANCEPROPMANAGER_H
