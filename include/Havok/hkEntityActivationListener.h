// STAND-IN: RuffKing Havok interface; CD2 three-slot table 0x8213FDE4 at object +0x294.
#ifndef CD2_HAVOK_HKENTITYACTIVATIONLISTENER_H
#define CD2_HAVOK_HKENTITYACTIVATIONLISTENER_H

class hkEntity;
class hkEntityActivationListener
{
public:
    virtual ~hkEntityActivationListener();
    virtual void entityDeactivatedCallback(hkEntity *) = 0;
    virtual void entityActivatedCallback(hkEntity *) = 0;
};
#endif
