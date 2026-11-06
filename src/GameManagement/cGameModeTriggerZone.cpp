// GameManagement::cGameModeTriggerZone: reference cGameModeTriggerZone.cpp and
// the CD2 constructor/table 0x82883AB8/0x82160110 establish this source object.
#include "GameManagement/cGameModeTriggerZone.h"
#include "GameManagement/cGameModeStartZone.h"
#include "GameManagement/cGameModeArena.h"
#include "GameManagement/cGameModePrototype.h"
#include "rw/rwmem.h"
#include "cd2/memory.h"
namespace GameManagement
{
    cGameModeTriggerZone::cGameModeTriggerZone()
        : cPlayerTriggerZone(false), m_pCheckPointVFX(0), m_bRenderCheckpoint(false),
          m_fFadeTimer(0.0f), m_fVFXHeightModifier(0.0f),
          m_eGameType(eGMT_Invalid), m_nCheckpointType(0)
    {
    }

    cGameModeTriggerZone::~cGameModeTriggerZone()
    {
        TermVFX();
    }

    void cGameModeTriggerZone::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cPlayerTriggerZone::HandleAttributes(packet);
        for (RWS::CAttributeCommandIterator it(packet, "cGameModeTriggerZone"); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case 0:
                m_sArenaName = Fun_Runtime::cString(it->GetAs_char_ptr());
                break;
            case 1:
                {
                    float value = it->GetAs_float();
                    RwMemNative32(&value, 4);
                    m_fVFXHeightModifier = value;
                }
                break;
            }
        }
        if (m_pCheckPointVFX && m_bRenderCheckpoint)
            SpawnVFX(m_eGameType, m_nCheckpointType);
    }

    etGameModeType cGameModeTriggerZone::RetGameType() const
    {
        // CD2 deliberately dispatches the prototype getter again after the null test.
        if (RetGameModePrototype())
            return RetGameModePrototype()->RetType();
        return eGMT_Invalid;
    }

    const cGameModeStartZone *cGameModeTriggerZone::RetStartZone() const
    {
        if (IsStartZone())
            return static_cast<const cGameModeStartZone *>(this);
        cGameModeArena *arena = cArenaLinker::GetArena(m_sArenaName);
        if (arena)
            return arena->RetStartZone();
        return 0;
    }
}
