// GameManagement/cGameModeArena.cpp: game-mode arena definitions of Crackdown 2.
// 11 of the file's 13 mapped functions are exact (checked 2026-10-26; config/matched_functions.json).
// Work in progress: GetRandSpawnPointInList<T> (87.3%; register allocation in the modulo sequence).
#include <string.h>
#include "GameManagement/cGameModeArena.h"
#include "GameManagement/cNetGamePlayerSpawnPoint.h"
#include "GameManagement/cNetGamePickupSpawnPoint.h"
#include "editor/guid_event_handler.h"
#include "rws/classfactory.h"
#include "rw/rwmem.h"

namespace GameManagement
{
    RWS::RWSGUID GetListGUID(const void *list, unsigned int index);
    const char *const cGameModeArena::pcGameModeArenaClassID = "cGameModeArena";

    cGameModeArena::cGameModeArena()
    {
        m_pBarrier = 0;
        m_pUnknownE0 = 0;
        m_pCameraContainer = 0;
        m_fToDPhase = 0.0f;
        m_fToDPeriod = 0.0f;
        m_bForceToD = false;
        m_bToDActive = false;
        m_nWeatherMode = 0;
        m_nUnknown100 = 0;
        m_nUnknown104 = -1;
        m_nUnknown108 = -1;
    }

    cGameModeArena::~cGameModeArena()
    {
        UnregisterGMM(m_nHandle);
    }

    const char *cGameModeArena::RetClassName() const
    {
        return pcGameModeArenaClassID;
    }

    void cGameModeArena::OnShutDownLevel()
    {
        for (int i = 0; i < 2; i++)
            m_vPlayerTeamSpawnPoints[i].clear();
        for (int j = 0; j < 2; j++)
            m_vPickupSpawnPoints[j].clear();
        m_vPlayerSoloSpawnPoints.clear();
        m_vWeaponSpawnPoints.clear();
        m_vLaunchPads.clear();
        m_pCameraContainer = 0;
    }

    void cGameModeArena::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        union { void *p; float mem; } temp;
        cGMMResource::HandleAttributes(packet);
        for (RWS::CAttributeCommandIterator it(packet, pcGameModeArenaClassID); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case 0:
                {
                    const unsigned int *list = (const unsigned int *)it->GetAs_char_ptr();
                    unsigned int count = rwSwap32(*list);
                    for (unsigned int i = 0; i < count; i++)
                    {
                        RWS::RWSGUID g = GetListGUID(list, i);
                        temp.p = Editor::cGUIDLinker<cGameModePrototype>::LinkToObject(g);
                        if (temp.p)
                        {
                            m_lCompatibleGameModes.push_back(temp.p);
                            if (((cArenaEntity *)temp.p)->RetType() == 13)
                                { cEntityManager *m = RetEntityManager(13); m->m_nCount = m->m_nCount + 1; }
                        }
                    }
                }
                break;
            case 1:
                {
                    const RWS::CAttributeCommand *cmd = it.operator->();
                    cLocStringManager *mgr = RetLocStringManager();
                    m_nStringID = mgr->GetStringID(cmd->GetAs_char_ptr());
                }
                break;
            case 2:
                m_bForceToD = rwSwap32(it->GetAs_UInt32()) != 0;
                break;
            case 3:
                { temp.mem = it->GetAs_float(); RwMemNative32(&temp.mem, 4); m_fToDPhase = temp.mem; }
                break;
            case 4:
                { temp.mem = it->GetAs_float(); RwMemNative32(&temp.mem, 4); m_fToDPeriod = temp.mem; }
                break;
            case 5:
                m_bToDActive = rwSwap32(it->GetAs_UInt32()) != 0;
                break;
            case 7:
                switch (rwSwap32(it->GetAs_UInt32()))
                {
                case 0: m_nWeatherMode = 0; break;
                case 1: m_nWeatherMode = 1; break;
                case 2: m_nWeatherMode = 2; break;
                case 3: m_nWeatherMode = 3; break;
                }
                break;
            case 6:
                m_bForceWeather = rwSwap32(it->GetAs_UInt32()) != 0;
                break;
            case 8:
                m_nUnknown100 = rwSwap32(it->GetAs_UInt32());
                break;
            case 9:
                if ((int)rwSwap32(it->GetAs_UInt32()) == 1)
                    m_nUnknown104 = 1;
                else if ((int)rwSwap32(it->GetAs_UInt32()) == 2)
                    m_nUnknown104 = 2;
                break;
            case 10:
                m_nUnknown108 = rwSwap32(it->GetAs_UInt32());
                break;
            }
        }
        if (packet.IsInstanceCreationPacket())
            m_nHandle = RegisterGMM(this);
    }

    RWS::CAttributeHandler *cGameModeArena::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cGameModeArena();
    }

    template <class T>
    T *cGameModeArena::GetRandSpawnPointInList(const cVec<cGameModeSpawnPoint *> &list)
    {
        static Fun_Runtime::cRandGen s_RandGen(GetTime_msec());
        if (list.size() > 0)
        {
            return static_cast<T *>(list[s_RandGen.Rand(list.size())]);
        }
        return 0;
    }

    template cNetGamePlayerSpawnPoint *cGameModeArena::GetRandSpawnPointInList<cNetGamePlayerSpawnPoint>(const cVec<cGameModeSpawnPoint *> &);
    template cNetGamePickupSpawnPoint *cGameModeArena::GetRandSpawnPointInList<cNetGamePickupSpawnPoint>(const cVec<cGameModeSpawnPoint *> &);

    cGameModeArena *cArenaLinker::GetArena(const cString &name)
    {
        cEventId id;
        RegisterMsg(id, c_strc(name).c_str(), "cGameModeArena*");
        cMsg msg(id, 0);
        SendMsg(msg);
        void *pData = msg.m_pData;
        UnRegisterMsg(id);
        return (cGameModeArena *)pData;
    }

    static RWS::CClassFactory::CRegistrar cGameModeArenaRegistrar(
        "cGameModeArena", cGameModeArena::MakeNew, 0x10C, false);
}
