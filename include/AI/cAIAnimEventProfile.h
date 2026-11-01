// AI::cAIAnimEventProfile: reference-header bases and members, with CD2 offsets confirmed by the
// deleting destructor (0x8243D398): event handler at 0x18, registered class at 0x1C,
// wide string at 0x28, return-self event at 0x44, total size 0x4C.
#ifndef AI_CAIANIMEVENTPROFILE_H
#define AI_CAIANIMEVENTPROFILE_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"
#include "rws/eventhandler.h"
#include "rws/eventid.h"
#include "rws/dynamicallocationpolicy.h"
#include "fun_runtime/string.h"

namespace AI
{
    enum etAIAnimEventType { eInvalid = 0, eFootstep, eVocal };

    class cAIAnimEventProfile : public RWS::CAttributeHandler, public RWS::CEventHandler,
        public RWS::DynamicAllocationPolicy, public Fun_Runtime::cRegisteredClass
    {
    public:
        // CD2's factory inlines this complete construction, including the default string and event ID.
        __forceinline cAIAnimEventProfile()
        {
            m_nAIAnimEventType = eInvalid;
            m_fRadius = 10.0f;
        }
        // CD2's deleting destructor contains this cleanup and member destruction inline.
        virtual __forceinline ~cAIAnimEventProfile()
        {
            UnLinkMsg(m_Msg_Return_Self);
            UnRegisterMsg(m_Msg_Return_Self);
        }
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // CD2 0x8243D450: attribute-handler vtable slot 5, returning Ret_OK.
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcAIAnimEventProfileClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
        virtual void Destruct();
        virtual Fun_Runtime::RetVal Term();
        virtual void HandleEvents(RWS::CMsg &);
        virtual void HandleAttributes(const RWS::CAttributePacket &);

    protected:
        float m_fRadius;
        etAIAnimEventType m_nAIAnimEventType;
        Fun_Runtime::cString m_sProfileName;
        RWS::CEventId m_Msg_Return_Self;

        CD2_LAYOUT_CHECKS(cAIAnimEventProfile,
            CD2_SIZE(cAIAnimEventProfile, 0x4C)
            CD2_OFFSET(cAIAnimEventProfile, m_fRadius, 0x20)
            CD2_OFFSET(cAIAnimEventProfile, m_nAIAnimEventType, 0x24)
            CD2_OFFSET(cAIAnimEventProfile, m_sProfileName, 0x28)
            CD2_OFFSET(cAIAnimEventProfile, m_Msg_Return_Self, 0x44))
    };
}

#endif // AI_CAIANIMEVENTPROFILE_H
