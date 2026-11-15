// STAND-IN: standalone manager type from RuffKing, with one virtual destructor.
// CD2's descriptor factory 0x82677F58 names cGangManager and gives size 0x50;
// table 0x8212EA48 contains its deleting destructor at 0x82677FF0.
// CD2 cFactionConfigData::HandleAttributes indexes the faction pointers at 0x30.
#ifndef GANGMANAGER_CGANGMANAGER_H
#define GANGMANAGER_CGANGMANAGER_H
#include "fun_runtime/class.h"
#include "cd2/layout.h"
namespace GangManager
{
    class cFactionInfo;
    __declspec(align(16)) class cGangManager
    {
    public:
        virtual ~cGangManager();
        static Fun_Runtime::cClass &StaticCreateClass();
        static cGangManager *sm_pGangManager;
        static cGangManager *RetGangManager() { return sm_pGangManager; }
    private:
        unsigned char m_unmodelled4[0x30 - 4];
    public:
        cFactionInfo *m_apFactions[6];
    private:
        unsigned char m_unmodelled48[0x50 - 0x48];
        CD2_LAYOUT_CHECKS(cGangManager, CD2_OFFSET(cGangManager, m_apFactions, 0x30) CD2_SIZE(cGangManager, 0x50))
    };
}
#endif
