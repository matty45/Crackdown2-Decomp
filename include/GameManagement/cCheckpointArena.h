// STAND-IN: RuffKing's cGameModeArena base and member order. CD2's factory
// 0x8284E0A8 inlines construction over 0x8284E4C0 and initializes the pointer
// vector at 0x10C; getters/setters establish m_pStartTriggerZone at 0x11C.
#ifndef GameManagement_cCheckpointArena_H
#define GameManagement_cCheckpointArena_H
#include "GameManagement/cGameModeArena.h"
#include "fun_runtime/vector.h"
namespace GameManagement
{
    class cCheckpointArena : public cGameModeArena
    {
    public:
        // CD2 inlines this constructor into the factory; the start-zone pointer stays uninitialized.
        __forceinline cCheckpointArena() {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void OnShutDownLevel();
        virtual cGameModeStartZone *RetStartZone() const;
        virtual unsigned int RetNumCheckpoints() const;
        virtual cGameModeCheckpoint *RetCheckpoint(unsigned int) const;
        virtual void AddStartZone(cGameModeStartZone *);
        virtual void AddCheckpoint(cGameModeCheckpoint *);
    protected:
        Fun_Runtime::cVector<cGameModeCheckpoint *> m_vCheckpoints;
        cGameModeStartZone *m_pStartTriggerZone;
        CD2_LAYOUT_CHECKS(cCheckpointArena,
            CD2_SIZE(cCheckpointArena, 0x120)
            CD2_OFFSET(cCheckpointArena, m_vCheckpoints, 0x10C)
            CD2_OFFSET(cCheckpointArena, m_pStartTriggerZone, 0x11C))
    };
}
#endif
