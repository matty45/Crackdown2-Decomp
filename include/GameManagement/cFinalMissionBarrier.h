#ifndef GameManagement_cFinalMissionBarrier_H
#define GameManagement_cFinalMissionBarrier_H

#include "rws/attributes.h"
#include "rws/systemcommands.h"
#include "fun_runtime/mtx.h"
#include "editor/guid_event_handler.h"
#include "GameManagement/cArenaBarrier.h"
#include "VFX/cBarrier.h"

namespace GameManagement
{
    // Burn's bases and members. CD2 MakeNew (0x8284F340, size 0x80) builds cArenaBarrier's pointers at 0x18/0x1C,
    // the identity transform at 0x20, the GUID handler at 0x64 and clears the barrier pointer at 0x78.
    // Table 0x8215BEF4: Create/Destroy at slots 13/14 override cArenaBarrier's.
    class cFinalMissionBarrier : public cArenaBarrier, public RWS::CSystemCommands
    {
    private:
        Fun_Runtime::Mtx m_mXForm;
        float m_fRadius;
        Editor::cGUIDEventHandler<cFinalMissionBarrier> m_EventHandler;
        VFX::cBarrier *m_pBarrier;
    public:
        // CD2 inlines the whole constructor chain into MakeNew.
        __forceinline cFinalMissionBarrier() : m_pBarrier(0) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual ~cFinalMissionBarrier() { Destroy(); }
        virtual void Create();
        virtual void Destroy()
        {
            if (m_pBarrier)
                m_pBarrier->Disable();
        }

        // CD2: cFinalMissionBarrier's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x8284F4E0
    public:
        CD2_LAYOUT_CHECKS(cFinalMissionBarrier,
            CD2_SIZE(cFinalMissionBarrier, 0x80)
            CD2_OFFSET(cFinalMissionBarrier, m_mXForm, 0x20)
            CD2_OFFSET(cFinalMissionBarrier, m_fRadius, 0x60)
            CD2_OFFSET(cFinalMissionBarrier, m_EventHandler, 0x64)
            CD2_OFFSET(cFinalMissionBarrier, m_pBarrier, 0x78))
    };
}

#endif
