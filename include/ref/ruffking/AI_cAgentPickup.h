
class AI::cAgentPickup : public AI::cPilotBase { /* Size=0x170 */
  /* 0x0000: fields for AI::cPilotBase */
  public: static const char* pcAgentPickupClassID;
  public: static const char m_cAgentPickup_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcAgentPickupClass;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: cAgentPickup(const AI::cAgentPickup&);
  public: cAgentPickup(GOM::cObjectPrototype*);
  public: virtual void OnEnterReplicatedState(unsigned char);
  public: virtual void OnEnter();
  public: virtual void SetupAfterReplication();
  public: virtual void OnExit();
  public: virtual void OnDied(CHARACTER::cCharacter*, AI::cAIEvent*);
  public: virtual void ActiveAgentComplete(unsigned int);
  public: virtual void Update(float);
  public: virtual void DemoteDelivery();
  protected: virtual void RenderDebugInfo();
  protected: virtual void EnterState(char);
  protected: virtual void ExitState(char);
  protected: virtual void UpdateInbound();
  protected: virtual void UpdateHover();
  protected: virtual void UpdateDroppingOff();
  protected: virtual void UpdateWaitingForExit();
  protected: virtual void UpdateAligningToTarget();
  protected: virtual void EnterHover();
  protected: virtual void EnterDroppingOff();
  protected: virtual void EnterWaitingForExit();
  protected: virtual void EnterAligningToTarget();
  private: AI::cPilotBase::cPilotBasePrototype& RetVCPrototype();
  public: virtual ~cAgentPickup();
  public: AI::cAgentPickup& operator=(const AI::cAgentPickup&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
