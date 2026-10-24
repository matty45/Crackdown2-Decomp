
class AI::NPCBehaviourPrototype : public AI::AIBehaviourPrototype { /* Size=0x90 */
  /* 0x0000: fields for AI::AIBehaviourPrototype */
  /* 0x0070 */ public: RWS::RWSGUID mPrimary;
  /* 0x0080 */ public: Fun_Runtime::cVector<RWS::RWSGUID,Fun_Runtime::cAllocator<RWS::RWSGUID,39,&AI::NPCBehaviourPrototype::tSecondaryWeapons_FL> > mSecondaries;
  
  public: NPCBehaviourPrototype(const AI::NPCBehaviourPrototype&);
  public: NPCBehaviourPrototype(const RWS::CAttributePacket&);
  public: virtual void HandleAttributes(const RWS::CAttributePacket&);
  public: void SetupArmoury(const RWS::CAttributePacket&);
  public: void SetupWeapons(AI::cAiPlayer*) const;
  public: virtual const RWS::RWSGUID& RetPrimaryWeapon() const;
  public: virtual ~NPCBehaviourPrototype();
  public: AI::NPCBehaviourPrototype& operator=(const AI::NPCBehaviourPrototype&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static Fun_Runtime::cFileLine tSecondaryWeapons_FL();
};
