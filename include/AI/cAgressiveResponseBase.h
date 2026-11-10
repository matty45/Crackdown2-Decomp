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
            // CD2: cAgressiveResponseBasePrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x824CC6F8
        };

        cAgressiveResponseBase();
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual void vf119();
        // CD2: cAgressiveResponseBase's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void OnEnter(); // 68: 0x824C9530
        virtual void OnExit(); // 69: 0x824C96F0
        virtual void Slot72(); // 72: 0x824C9638
        virtual void OnEvent74(AI::NPCTarget *); // 74: 0x824CB058
        virtual void OnEvent75(AI::NPCTarget *); // 75: 0x824CB118
        virtual void Slot76(); // 76: 0x824CB610
        virtual void Slot77(); // 77: 0x824CB530
        virtual void Slot79(); // 79: 0x824C9770
        virtual void Slot82(); // 82: 0x824CAFA8
        virtual void Update(float); // 96: 0x824C97E0
        virtual void GetState(int); // 100: 0x824CBF08
        virtual void V102(); // 102: 0x824C9A70
        virtual void Slot109(); // 109: 0x824CAA60
        virtual void Slot112(); // 112: 0x824CAC70
        virtual void V118(); // 118: 0x824CB938
        virtual void Slot2(); // cSafeDeletable 2: 0x824CBAA0
    public:
        CD2_LAYOUT_CHECKS(cAgressiveResponseBase, CD2_SIZE(cAgressiveResponseBase, 0x100))
    };
}
#endif
