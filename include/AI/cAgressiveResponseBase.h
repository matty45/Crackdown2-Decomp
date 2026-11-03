// STAND-IN: RuffKing base cChaseBehaviour; CD2 StaticCreateClass (0x824C90D8)
// gives 0x100 bytes, the same extent as the recovered chase base.
#ifndef AI_CAGRESSIVERESPONSEBASE_H
#define AI_CAGRESSIVERESPONSEBASE_H
#include "AI/cChaseBehaviour.h"
namespace AI
{
    class cAgressiveResponseBase : public cChaseBehaviour
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        CD2_LAYOUT_CHECKS(cAgressiveResponseBase, CD2_SIZE(cAgressiveResponseBase, 0x100))
    };
}
#endif
