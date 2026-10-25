
class AI::ScroungerSlinger : public AI::Scrounger { /* Size=0x430 */
  /* 0x0000: fields for AI::Scrounger */
  /* 0x0420 */ private: unsigned int m_nNextSlingTime;
  /* 0x0424 */ private: unsigned int m_nSlingTimeout;
  /* 0x0428 */ private: bool m_bSniper;
  public: static const char* pScroungerSlingerClassID;
  public: static const char m_ScroungerSlinger_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pScroungerSlingerClass;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: ScroungerSlinger(const AI::ScroungerSlinger&);
  public: ScroungerSlinger(GOM::cObjectPrototype*);
  public: virtual void InitBehaviour();
  public: virtual void OnEnterReplicatedState(unsigned char);
  public: virtual void EnterStateCold(unsigned char);
  public: virtual unsigned char GetStateReplicationInfo() const;
  public: virtual AI::IBehaviourState* GetState(unsigned char);
  public: void STATE_Enter_Slinging();
  public: void STATE_Update_Slinging(float);
  public: void STATE_AnimEvent_Slinging(unsigned char, int, short);
  public: void STATE_Enter_Lobbing();
  public: void STATE_Enter_Retreating();
  public: void STATE_Update_Retreating(float);
  public: void STATE_ReachedDestination_Retreating(bool);
  public: virtual void STATE_Update_Chasing(float);
  public: void STATE_Update_Tracking(float);
  public: virtual void OnFullBodyAnimFinished();
  public: virtual void OnAttacked(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void OnCharacterEvent(unsigned char, unsigned char, unsigned char);
  public: virtual void OnDetectedEnemy(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void OnHeardSuspiciousSound(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void OnObjectApproached(CHARACTER::cCharacter*, PHYSICS::cDynamicBody*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void OnAttachSatchelCharge(Equip::cCWSatchelCharge*);
  public: void FireAcidAtTarget();
  public: virtual const char* RetStringForState(unsigned char);
  protected: virtual void OnRouteEvent(const AI::cBasePatrolRouteEvent&);
  private: void DetermineCombatState();
  private: const AI::ScroungerSlingerPrototype* RetSlingerPrototype() const;
  public: virtual ~ScroungerSlinger();
  public: AI::ScroungerSlinger& operator=(const AI::ScroungerSlinger&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
