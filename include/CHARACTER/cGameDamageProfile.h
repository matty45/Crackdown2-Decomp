#ifndef CHARACTER_cGameDamageProfile_H
#define CHARACTER_cGameDamageProfile_H

#include "rws/attributes.h"
#include "editor/guid_event_handler.h"
#include "rws/dynamicallocationpolicy.h"
#include "cd2/layout.h"

namespace CHARACTER
{
    class cGameDamageProfile : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        // CD2 primary table 0x82003134 slot 12; reference name.
        virtual void Destruct();
        // RuffKing field names/order; CD2 factory 0x82555F60 establishes these offsets.
        __forceinline cGameDamageProfile(const RWS::CAttributePacket &)
        {
            m_fPlayerToAIDamageModifier = 0.0f;
            m_fAIToPlayerDamageModifier = 0.0f;
            m_fAIToAIDamageModifier = 0.0f;
            m_fPlayerToPlayerDamageModifier = 0.0f;
        }
        // CD2 deleting wrapper 0x82556038 restores the derived primary table before member cleanup.
        virtual ~cGameDamageProfile() {}
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual bool HandleDataInNewDesignBuild() { return true; }
        enum LoadParameterTypes
        {
            CMD_PLAYER_TO_AI_DAMAGE_MODIFIER = 0, CMD_AI_TO_PLAYER_DAMAGE_MODIFIER,
            CMD_AI_TO_AI_DAMAGE_MODIFIER, CMD_PLAYER_TO_PLAYER_DAMAGE_MODIFIER
        };

    private:
        float m_fPlayerToAIDamageModifier;
        float m_fAIToPlayerDamageModifier;
        float m_fAIToAIDamageModifier;
        float m_fPlayerToPlayerDamageModifier;
        Editor::cGUIDEventHandler<cGameDamageProfile> m_EventHandler;

        CD2_LAYOUT_CHECKS(cGameDamageProfile,
            CD2_SIZE(cGameDamageProfile, 0x3C)
            CD2_OFFSET(cGameDamageProfile, m_fPlayerToAIDamageModifier, 0x18)
            CD2_OFFSET(cGameDamageProfile, m_fAIToPlayerDamageModifier, 0x1C)
            CD2_OFFSET(cGameDamageProfile, m_fAIToAIDamageModifier, 0x20)
            CD2_OFFSET(cGameDamageProfile, m_fPlayerToPlayerDamageModifier, 0x24)
            CD2_OFFSET(cGameDamageProfile, m_EventHandler, 0x28))
    };
}

#endif
