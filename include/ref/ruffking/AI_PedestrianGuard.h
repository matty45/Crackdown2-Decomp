
class AI::PedestrianGuard : public AI::cPedestrianBase, public cNPCArmourySetup { /* Size=0x160 */
  /* 0x0000: fields for AI::cPedestrianBase */
  /* 0x0150: fields for cNPCArmourySetup */
  /* 0x0150 */ private: AI::cAIEventSubscription* m_nReloadSub;
  public: static const char* pPedestrianGuardClassID;
  public: static const char m_PedestrianGuard_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pPedestrianGuardClass;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: PedestrianGuard(const AI::PedestrianGuard&);
  public: PedestrianGuard(GOM::cObjectPrototype*);
  public: virtual void OnEnter();
  public: virtual void OnExit();
  public: virtual void OnDetectedEnemy(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void OnAttacked(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void OnHeardSuspiciousSound(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void OnObjectApproached(CHARACTER::cCharacter*, PHYSICS::cDynamicBody*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void OnDied(CHARACTER::cCharacter*, AI::cAIEvent*);
  public: virtual void Notify(AI::cAIEvent*);
  public: virtual void UpdateAmbient();
  public: virtual void Update(float);
  public: virtual void RenderDebugInfo();
  protected: virtual void EnterState(char);
  protected: virtual void ExitState(char);
  protected: void EnterAttacking();
  protected: void ExitAttacking();
  private: AI::PedestrianGuard::cPedestrianGuardPrototype& RetPedPrototype();
  public: virtual ~PedestrianGuard();
  public: AI::PedestrianGuard& operator=(const AI::PedestrianGuard&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
