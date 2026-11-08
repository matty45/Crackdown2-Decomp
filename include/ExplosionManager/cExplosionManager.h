// ExplosionManager::cExplosionManager (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in
// RuffKing's header; RetClassName (0x8263EB98) is slot 11 of the vtable at 0x8212BAC8, as cNonGameBase's RetClassName.
#ifndef EXPLOSIONMANAGER_CEXPLOSIONMANAGER_H
#define EXPLOSIONMANAGER_CEXPLOSIONMANAGER_H

#include "fun_runtime/class.h"
#include "gom/non_game_base.h"

namespace ExplosionManager
{
    class cExplosionManager : public cNonGameBase
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcExplosionManagerClass;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif // EXPLOSIONMANAGER_CEXPLOSIONMANAGER_H
