// STAND-IN: reference class has no bases. CD2 constructor 0x82543408 constructs this member at character +0x1530
// and the following animation interface at +0x1B30, fixing size 0x600. Its reference-named state record starts
// at +0x150; the inventory is therefore character +0x1770. Other own fields remain opaque.
#ifndef CHARACTER_CACTIONMANAGER_H
#define CHARACTER_CACTIONMANAGER_H

#include "CHARACTER/cActionManagerCharacterStateInfo.h"
namespace CHARACTER
{
    class cActionManager
    {
    public:
        ~cActionManager();
        bool ForceOutOfVehicle(); // CD2 0x8257B850
        cActionManagerCharacterStateInfo &RetCharacterStateInfo() { return m_CharacterStateInfo; }
        const cActionManagerCharacterStateInfo &RetCharacterStateInfo() const { return m_CharacterStateInfo; }
    private:
        unsigned char m_unmodelled0[0x150];
        cActionManagerCharacterStateInfo m_CharacterStateInfo;
        unsigned char m_unmodelled5D0[0x600 - 0x5D0];
        CD2_LAYOUT_CHECKS(cActionManager,
            CD2_SIZE(cActionManager, 0x600)
            CD2_OFFSET(cActionManager, m_CharacterStateInfo, 0x150))
    };
}
#endif
