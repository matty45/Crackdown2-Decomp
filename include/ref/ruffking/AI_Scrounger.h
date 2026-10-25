
class AI::Scrounger : public AI::FreakBase { /* Size=0x420 */
  /* 0x0000: fields for AI::FreakBase */
  /* 0x0410 */ protected: Anim::etCommonSkeletonBone m_eAttackBone;
  public: static const char* pScroungerClassID;
  public: static const char m_Scrounger_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pScroungerClass;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: Scrounger(const AI::Scrounger&);
  public: Scrounger(GOM::cObjectPrototype*);
  public: virtual void OnEnter();
  public: virtual void OnEnterReplicatedState(unsigned char);
  public: virtual void OnExit();
  public: virtual unsigned char GetStateReplicationInfo() const;
  public: virtual void EnterStateCold(unsigned char);
  public: virtual AI::IBehaviourState* GetState(unsigned char);
  public: virtual void STATE_Enter_Alerted();
  public: virtual void STATE_Enter_Idle();
  public: virtual void STATE_Enter_Chasing();
  public: virtual void STATE_Enter_Attacking();
  public: virtual void STATE_Enter_RushAttack();
  public: virtual void STATE_Enter_MoveToAttackVehicle();
  public: virtual void STATE_Update_PostSpawn(float);
  public: virtual void STATE_Update_Idle(float);
  public: virtual void STATE_Update_Chasing(float);
  public: virtual void STATE_Update_MoveToAttackVehicle(float);
  public: virtual void STATE_ReachedDestination_Chasing(bool);
  public: virtual void STATE_ReachedDestination_MoveToAttackVehicle(bool);
  public: virtual void STATE_AnimEvent_Attacking(unsigned char, int, short);
  public: virtual void STATE_Attacked_Ambient(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void Update(float);
  public: virtual void SetReactResupplyPoint(const Fun_Runtime::Vec3&, const Fun_Runtime::Vec3&);
  public: virtual void OnTargetLost();
  protected: virtual bool OnStuck();
  protected: virtual void OnFullBodyAnimFinished();
  protected: void TryAttack();
  protected: bool IsTargetInStandingMeleeRange() const;
  protected: bool CanExecuteRushAttack() const;
  protected: virtual float RetMaxTargetHeightDelta() const;
  protected: virtual void OnTargetUnreachable();
  protected: const Fun_Runtime::Vec3& GetBestFreeVehicleAttackPoint(Vehicle::cLandVehicle&) const;
  protected: AI::ScroungerPrototype* RetScroungerPrototype() const;
  protected: virtual const char* RetStringForState(unsigned char);
  public: virtual ~Scrounger();
  public: AI::Scrounger& operator=(const AI::Scrounger&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
