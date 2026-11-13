// SNetGlobalData (Crackdown 2): the network session flags, with RuffKing's names and layout (gNetGlobalDataVar,
// SNetGlobalData). CD2's copy is at 0x8392A7F8; cTacticalObjective::InitReplication (0x82475D88) expands IsHost
// into a test of its first byte (m_bNetEnabled) and a read of its second (m_bHost). RuffKing's out-of-line IsHost
// also checks the skip-lobby flags; CD2's inline form does not.
#ifndef CD2_NETWORK_SNETGLOBALDATA_H
#define CD2_NETWORK_SNETGLOBALDATA_H

#include "cd2/layout.h"

struct SNetGlobalData
{
    bool m_bNetEnabled;
    bool m_bHost;
    bool m_bSecure;
    bool m_bSkipLobby;
    bool m_bSkipLobbyHost;
    unsigned int m_nNetworkValid;
    unsigned int m_nSharedTimeOffset;
    unsigned int m_nLocalTime;
    bool m_bHasValidSharedTime;

    CD2_LAYOUT_CHECKS(SNetGlobalData,
        CD2_OFFSET(SNetGlobalData, m_bHost, 0x1)
        CD2_OFFSET(SNetGlobalData, m_nNetworkValid, 0x8))
};

extern SNetGlobalData gNetGlobalDataVar;

namespace Network
{
    inline bool IsNetworkEnabled()
    {
        return gNetGlobalDataVar.m_bNetEnabled;
    }

    inline bool IsHost()
    {
        if (IsNetworkEnabled())
            return gNetGlobalDataVar.m_bHost;
        return true;
    }

    // RuffKing's name; CD2 0x82812AF8 (outside the scaffolded files).
    unsigned char RetLocalNodeID();
}

#endif // CD2_NETWORK_SNETGLOBALDATA_H
