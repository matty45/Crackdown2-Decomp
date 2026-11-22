// CHARACTER::cPlayerNetManager (Crackdown 2): STAND-IN for the net-player table only. RuffKing's static
// m_aNetPlayerList (16 characters) and RetNetCharacter, which CD2 inlines: cEquipment::CalculateLOD (0x826066B0)
// returns null from node 0xFF up and otherwise indexes the table at 0x83800A80, as RuffKing's body does.
#ifndef CHARACTER_CPLAYERNETMANAGER_H
#define CHARACTER_CPLAYERNETMANAGER_H

namespace CHARACTER
{
    class cCharacter;

    class cPlayerNetManager
    {
    public:
        static cCharacter *RetNetCharacter(unsigned int nPlayerID)
        {
            if (nPlayerID >= 0xFF)
                return 0;
            return m_aNetPlayerList[nPlayerID];
        }

    private:
        static cCharacter *m_aNetPlayerList[16];
    };
}

#endif // CHARACTER_CPLAYERNETMANAGER_H
