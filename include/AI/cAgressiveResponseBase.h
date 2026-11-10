// STAND-IN: RuffKing base cChaseBehaviour; CD2 StaticCreateClass (0x824C90D8)
// gives 0x100 bytes, the same extent as the recovered chase base.
// Constructor 0x824C9180 (out of line, takes only this) calls cChaseBehaviour's and installs table 0x8210B510:
// 120 primary slots, one more than cChaseBehaviour's 119. Slot 119 (0x824C91F0) sets the flag at 0xF6 and calls
// SetState(2); RuffKing's cAgressiveResponseBase declares no new virtual, so its name is not known (vf119 is ours).
// cAgressiveResponseBasePrototype adds no storage (RuffKing: 144 bytes, like cChaseBehaviourPrototype).
#ifndef AI_CAGRESSIVERESPONSEBASE_H
#define AI_CAGRESSIVERESPONSEBASE_H
#include "AI/cChaseBehaviour.h"
namespace AI
{
    class cAgressiveResponseBase : public cChaseBehaviour
    {
    public:
        class cAgressiveResponseBasePrototype : public cChaseBehaviour::cChaseBehaviourPrototype
        {
        public:
            __forceinline cAgressiveResponseBasePrototype(const RWS::CAttributePacket &packet)
                : cChaseBehaviourPrototype(packet)
            {
            }
        };

        cAgressiveResponseBase();
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual void vf119();
        CD2_LAYOUT_CHECKS(cAgressiveResponseBase, CD2_SIZE(cAgressiveResponseBase, 0x100))
    };
}
#endif
