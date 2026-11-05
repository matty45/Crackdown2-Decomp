// STAND-IN: Havok's collision-listener interface, slot order from RuffKing's Havok headers. CD2's table 0x82114980
// has the three pure callbacks, the shared empty body 0x82580578 (contactProcessCallback) and the destructor; cBody's
// destructor (0x826837D8) restores it inline.
#ifndef CD2_HAVOK_HKCOLLISIONLISTENER_H
#define CD2_HAVOK_HKCOLLISIONLISTENER_H

class hkContactPointAddedEvent;
class hkContactPointConfirmedEvent;
class hkContactPointRemovedEvent;
class hkContactProcessEvent;

class hkCollisionListener
{
public:
    virtual void contactPointAddedCallback(hkContactPointAddedEvent &) = 0;
    virtual void contactPointConfirmedCallback(hkContactPointConfirmedEvent &) = 0;
    virtual void contactPointRemovedCallback(hkContactPointRemovedEvent &) = 0;
    virtual void contactProcessCallback(hkContactProcessEvent &) {}
    virtual ~hkCollisionListener() {}
};
#endif
