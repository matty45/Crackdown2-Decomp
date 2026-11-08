// RPG::cAchievementTargetsInterface (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x827775C0, from its registrars in CD2's
// initializer run); RuffKing names the class in cAchievementTargets.obj. No layout or virtuals are modelled yet.
#ifndef RPG_CACHIEVEMENTTARGETSINTERFACE_H
#define RPG_CACHIEVEMENTTARGETSINTERFACE_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace RPG
{
    class cAchievementTargetsInterface
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // RPG_CACHIEVEMENTTARGETSINTERFACE_H
