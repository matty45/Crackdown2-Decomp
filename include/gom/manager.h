// GOM prototype lookup: STAND-IN declaration for the CD2 entry at 0x82656920.
// CD2 takes a GUID in r3 and searches the GUID table of the global manager;
// it has no explicit manager argument. FindPrototypeById is Burn's name for
// the later cGameObjectManager member; the free-function spelling is ours.
#ifndef GOM_MANAGER_H
#define GOM_MANAGER_H

#include "rws/attributes.h"

namespace Fun_Runtime { class cClass; }

namespace GOM
{
    class cObjectPrototype;
    cObjectPrototype *FindPrototypeById(const RWS::RWSGUID &);
    // CD2 0x82656808 takes only the name and class filter (r3/r4).
    // RuffKing names the later manager member FindPrototypeByName.
    cObjectPrototype *FindPrototypeByName(const char *, const Fun_Runtime::cClass *);
}

#endif
