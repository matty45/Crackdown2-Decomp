// STAND-IN: reference cGameModeTriggerZone base and checkpoint ID at 0x120.
// CD2 factory 0x82881C78 and registrar 0x8301FEA0 establish size 0x1C0.
// Audio storage beginning at 0x128 is not recovered and remains opaque.
#ifndef GAMEMANAGEMENT_CGAMEMODECHECKPOINT_H
#define GAMEMANAGEMENT_CGAMEMODECHECKPOINT_H
#include "GameManagement/cGameModeTriggerZone.h"
namespace GameManagement
{
    class cGameModeCheckpoint : public cGameModeTriggerZone
    {
    public:
        cGameModeCheckpoint(const RWS::CAttributePacket &);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void Destruct();
        virtual void OnPlayerEnter(CHARACTER::cCharacter *);
        virtual void OnPlayerLeave(CHARACTER::cCharacter *);
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual cGameModePrototype *RetGameModePrototype() const;
        // CD2 AddCheckpoint (0x8284E248) inlines this assignment after appending the pointer.
        void SetCheckpointID(int id) { m_nCheckpointID = id; }
    protected:
        int m_nCheckpointID;
        unsigned char m_unmodelled124[0x1C0 - 0x124];
        CD2_LAYOUT_CHECKS(cGameModeCheckpoint,
            CD2_SIZE(cGameModeCheckpoint, 0x1C0)
            CD2_OFFSET(cGameModeCheckpoint, m_nCheckpointID, 0x120))
    };
}
#endif
