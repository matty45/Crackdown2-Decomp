// STAND-IN: reference inheritance and fields, confirmed by the CD2 constructor and getters.
#ifndef GameManagement_cGameModeStartZone_H
#define GameManagement_cGameModeStartZone_H

#include "cd2/layout.h"
#include "GameManagement/cGameModeTriggerZone.h"
#include "network/cReplicatedClass.h"

namespace GameManagement
{
    class cGameModeSession;
    class cGameModeStartZone : public cGameModeTriggerZone, public cReplicatedClass
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void Destruct();
        virtual void TickStartZone(float);
        virtual unsigned char RetMaxNumParticipants() const;
        // CD2 primary table 0x82160018 ends with CreateGameSession at slot 30.
        virtual cGameModeSession *CreateGameSession();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual void OnPlayerEnter(CHARACTER::cCharacter *);
        virtual void OnPlayerLeave(CHARACTER::cCharacter *);
        virtual bool IsStartZone() const;
        virtual cGameModePrototype *RetGameModePrototype() const;
        virtual unsigned char RetMinimumAgilityLevel() const;
        virtual unsigned char RetMinNumParticipants() const;
        // Reference overrides for the CD2 replication interface at +0x120.
        virtual bool IsSequential() const;
        virtual bool IsOwnedLocally();
        virtual void SetPingedFieldStatesForNode(unsigned char);
        virtual SNetworkHeader::etNetworkDataType GetReplicatedObjectType() const;
        virtual unsigned int GetMaxReplicatedFields() const;
        // CD2 replication table 0x82160098, slot 16; folded getter at 0x82882258.
        virtual unsigned int GetNumObjectIDBits() const;
    public:
        // Out of line: CD2 0x821D2840 (MakeNew calls it).
        cGameModeStartZone();

    private:
        Fun_Runtime::cString m_sGameModeName;
        cGameModePrototype *m_pGameModePrototype;
        unsigned char m_nMinimumAgilityLevel;
        unsigned char m_nMinNumParticipants;
        unsigned char m_nMaxNumParticipants;
        unsigned char m_unmodelled373[0x3D0 - 0x373];

        CD2_LAYOUT_CHECKS(cGameModeStartZone, CD2_SIZE(cGameModeStartZone, 0x3D0)
            CD2_OFFSET(cGameModeStartZone, m_sGameModeName, 0x350)
            CD2_OFFSET(cGameModeStartZone, m_pGameModePrototype, 0x36C)
            CD2_OFFSET(cGameModeStartZone, m_nMinimumAgilityLevel, 0x370)
            CD2_OFFSET(cGameModeStartZone, m_nMinNumParticipants, 0x371)
            CD2_OFFSET(cGameModeStartZone, m_nMaxNumParticipants, 0x372))

    };
}

#endif
