// STAND-IN: RuffKing cPickupBase's base order; CD2 descriptor 0x82709340 gives
// size 0x150. Fields beyond the shared non-game base are not yet recovered.
#ifndef PHYSICS_CPICKUPBASE_H
#define PHYSICS_CPICKUPBASE_H
#include "gom/non_game_base.h"
#include "rws/systemcommands.h"
namespace PHYSICS
{
    class cPickupBase : public RWS::CSystemCommands, public cNonGameBase
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
    private:
        unsigned char m_unmodelled7C[0x150 - 0x7C];
        CD2_LAYOUT_CHECKS(cPickupBase, CD2_SIZE(cPickupBase, 0x150))
    };
}
#endif
