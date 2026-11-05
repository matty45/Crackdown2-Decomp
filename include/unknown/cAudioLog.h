#include "rws/attributes.h"
// unknown::cAudioLog (Crackdown 2): STAND-IN. RuffKing's PHYSICS::cAudioLog: base cPickupBase (0x150 bytes in CD2), then its
// GUID event handler, container pointer and two string keys; with CD2's smaller base they end exactly at the registrar's
// size, 0x1A0. CD2's destructor (0x8270EC18) destroys the keys (0x184, then 0x168) and the handler (0x150, through
// ~cGUIDEventHandlerBase 0x82886178) and calls cPickupBase's destructor (0x82709638).
// StaticCreateClass (0x8270ED30) builds cClass(0x115, "cAudioLog", 0x1A0).
#ifndef UNKNOWN_CAUDIOLOG_H
#define UNKNOWN_CAUDIOLOG_H

#include "PHYSICS/cPickupBase.h"
#include "editor/guid_event_handler.h"
#include "fun_runtime/stringc.h"
#include "fun_runtime/class.h"
#include "cd2/layout.h"

namespace unknown
{
    class cAudioLogContainer;

    class cAudioLog : public PHYSICS::cPickupBase
    {
    public:
        // CD2 0x8270EDC8: the allocation factory calls this constructor out of line.
        cAudioLog();
        // CD2 0x8270EC18.
        virtual ~cAudioLog();
        // CD2 0x8270EB50: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x8270EB60: registered-class virtual slot 1.
        virtual bool IsA(const Fun_Runtime::cClass &c) const;
        // CD2 0x8270EC08: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcAudioLogClass;
        static Fun_Runtime::cClass &StaticCreateClass();

    protected:
        Editor::cGUIDEventHandler<cAudioLog> m_EventHandler;
        cAudioLogContainer *m_pContainer;
        Fun_Runtime::cStringc m_nameKey;
        Fun_Runtime::cStringc m_textKey;

        CD2_LAYOUT_CHECKS(cAudioLog,
            CD2_SIZE(cAudioLog, 0x1A0)
            CD2_OFFSET(cAudioLog, m_EventHandler, 0x150)
            CD2_OFFSET(cAudioLog, m_pContainer, 0x164)
            CD2_OFFSET(cAudioLog, m_nameKey, 0x168)
            CD2_OFFSET(cAudioLog, m_textKey, 0x184))
    };
}

#endif // UNKNOWN_CAUDIOLOG_H
