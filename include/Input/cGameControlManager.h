// STAND-IN prefix, not a complete hierarchy/layout. Reference builds name the singleton,
// RetPrimaryController, and m_SPActionMap. CD2 0x82897E48 reads the singleton at 0x8377A9E8,
// calls RetPrimaryController at 0x8267B350, and indexes maps at +0x1C with stride 0x7F8.
// Known wrong, left for a structural fix: CD2 also registers it under GDb::cDebugPageHandler (inheritance registrar 0x82FDEA18), RuffKing's second base after CEventHandler. The
// stand-in lacks that base, so everything after its first base is not laid out as in CD2.
#ifndef INPUT_CGAMECONTROLMANAGER_H
#define INPUT_CGAMECONTROLMANAGER_H
#include "Input/cActionMap.h"
#include "Input/cGameController.h"
#include "rws/eventhandler.h"
namespace Input
{
    class cGameControlManager;
    extern cGameControlManager *g_GameControlManager;

    class cGameControlManager : public RWS::CEventHandler
    {
        unsigned char m_unmodelled4[0x1C - 4];
        cActionMap m_SPActionMap[2];
    public:
        static cGameControlManager *RetInstancePtr() { return g_GameControlManager; }
        cGameController *RetPrimaryController();
        cActionMap *RetSPActionMap(unsigned char index) { return &m_SPActionMap[index]; }

        CD2_LAYOUT_CHECKS(cGameControlManager,
            CD2_OFFSET(cGameControlManager, m_SPActionMap, 0x1C))
    };
}
#endif
