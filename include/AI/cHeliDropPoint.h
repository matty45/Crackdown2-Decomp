// AI::cHeliDropPoint (Crackdown 2): RuffKing cTacticalObjective.h names the class, its bases (CSystemCommands,
// CAttributeHandler), its matrix at 0x20 and GUID handler at 0x60 (0x80 bytes). CD2 evidence: MakeNew 0x82475698
// allocates 0x80 and builds the identity matrix at 0x20 and the handler at 0x60; the primary table 0x82104460 has
// CAttributeHandler's 11 slots, then RetClass (11), IsA (12), RetClassName (13), Destruct (14) and
// HandleSystemCommands (15, called by HandleAttributes 0x82475908 through slot 15).
#ifndef AI_CHELIDROPPOINT_H
#define AI_CHELIDROPPOINT_H

#include "fun_runtime/class.h"
#include "fun_runtime/mtx.h"
#include "rws/attributes.h"
#include "rws/systemcommands.h"
#include "editor/guid_event_handler.h"

namespace AI
{
    class cHeliDropPoint : public RWS::CSystemCommands, public RWS::CAttributeHandler
    {
    public:
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcHeliDropPointClass;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void Destruct();
        cHeliDropPoint(const RWS::CAttributePacket &);
        // CD2's deleting destructor 0x824758A0 stores the primary vptr first: a user-declared destructor.
        virtual ~cHeliDropPoint() {}
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual void HandleSystemCommands(const RWS::CAttributePacket &);

    private:
        Fun_Runtime::Mtx m_mMat;
        Editor::cGUIDEventHandler<cHeliDropPoint> m_EventHandler;

        CD2_LAYOUT_CHECKS(cHeliDropPoint,
            CD2_SIZE(cHeliDropPoint, 0x80)
            CD2_OFFSET(cHeliDropPoint, m_mMat, 0x20)
            CD2_OFFSET(cHeliDropPoint, m_EventHandler, 0x60))
    };
}

#endif // AI_CHELIDROPPOINT_H
