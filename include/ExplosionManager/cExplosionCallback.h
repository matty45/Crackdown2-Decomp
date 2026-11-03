// STAND-IN: RuffKing cexplosive.cpp: one pure virtual, no destructor; CD2 prop interface +0x7A0.
#ifndef CD2_EXPLOSIONMANAGER_CEXPLOSIONCALLBACK_H
#define CD2_EXPLOSIONMANAGER_CEXPLOSIONCALLBACK_H

class cGameBase;
namespace CHARACTER { class cCharacterInterface; }
namespace ExplosionManager
{
    class cExplosionCallback
    {
    public:
        virtual void NotifyDetonation(cGameBase *, CHARACTER::cCharacterInterface *, unsigned char) = 0;
    };
}
#endif
