
class AI::BreachPilot : public AI::cPilotBase { /* Size=0x190 */
  /* 0x0000: fields for AI::cPilotBase */
  /* 0x0170 */ protected: AI::cBreachHoleMission* m_pBreachHoleMission;
  /* 0x0174 */ protected: const AI::cPatrolRoute* m_pTravelRoute;
  /* 0x0178 */ protected: const AI::cPatrolRoute* m_pTargetRoute;
  /* 0x0180 */ private: Fun_Runtime::Vec3 m_vEndPos;
  public: static const char* pBreachPilotClassID;
  public: static const char m_BreachPilot_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pBreachPilotClass;
  private: static bool m_bShowDebugTargetting;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: BreachPilot(const AI::BreachPilot&);
  public: BreachPilot(GOM::cObjectPrototype*);
  public: virtual void OnEnterReplicatedState(unsigned char);
  public: virtual void OnEnter();
  public: virtual void SetupAfterReplication();
  public: virtual void OnExit();
  public: virtual void OnDied(CHARACTER::cCharacter*, AI::cAIEvent*);
  public: virtual void OnDetectedEnemy(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void DemoteDelivery();
  public: virtual void Update(float);
  protected: virtual void RenderDebugInfo();
  protected: virtual void EnterState(char);
  protected: virtual void ExitState(char);
  protected: virtual void UpdateHover();
  protected: virtual void UpdateAttacking();
  protected: virtual void UpdateOutbound();
  protected: virtual void EnterOutbound();
  protected: virtual void EnterHover();
  protected: virtual void EnterAttacking();
  protected: virtual void ExitAttacking();
  protected: void GetTargetTravelRoute();
  private: AI::cPilotBase::cPilotBasePrototype& RetBPPrototype();
  public: virtual ~BreachPilot();
  public: AI::BreachPilot& operator=(const AI::BreachPilot&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
