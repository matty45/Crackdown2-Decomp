
class AI::cChaseBehaviour::cChaseBehaviourPrototype : public AI::NPCBehaviourPrototype { /* Size=0x90 */
  /* 0x0000: fields for AI::NPCBehaviourPrototype */
  
  public: cChaseBehaviourPrototype(const AI::cChaseBehaviour::cChaseBehaviourPrototype&);
  public: cChaseBehaviourPrototype(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: virtual ~cChaseBehaviourPrototype();
  public: AI::cChaseBehaviour::cChaseBehaviourPrototype& operator=(const AI::cChaseBehaviour::cChaseBehaviourPrototype&);
  public: virtual void* __vecDelDtor(unsigned int);
};
