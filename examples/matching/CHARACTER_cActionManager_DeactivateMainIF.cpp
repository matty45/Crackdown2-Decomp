// Crackdown 2 (Xbox 360, title update build) - byte-exact match
// Target : 0x82302E10, 152 bytes
// Author : Sonnet 5.5 (agent pilot P1), 2 harness runs
// Notes  : CHARACTER::cActionManager::DeactivateMainIF. RuffKing has the same function apart from its trace markers.
// Types below are minimal stand-ins written for this one function, not real headers.
// Verify : py -I verify.py <path to extracted default.exe>

struct cBaseAction {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void Deactivate();
    char pad[0x1E-4];
    unsigned char flags;
};
struct cActionManager {
    char pad0[0x1C];
    cBaseAction* m_MainActions[34];
    char pad1[0x124-0x1C-34*4];
    cBaseAction* m_pActiveMainIF;
    void DeactivateMainIF();
};
void cActionManager::DeactivateMainIF() {
    if (m_pActiveMainIF) {
        m_pActiveMainIF->Deactivate();
        m_pActiveMainIF = 0;
    }
    for (int i = 0; i < 34; i++) {
        if (m_MainActions[i] && (m_MainActions[i]->flags & 0x40))
            m_MainActions[i]->Deactivate();
    }
}

