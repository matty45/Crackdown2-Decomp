
class AI::cTrainingHeliPilot : public AI::cPilotBase { /* Size=0x180 */
  /* 0x0000: fields for AI::cPilotBase */
  /* 0x0170 */ private: AI::cTrainingMission* m_pTrainingMission;
  /* 0x0174 */ private: AI::cAIEventSubscription* m_pPatrolEventHandle;
  public: static const char* pcTrainingHeliPilotClassID;
  public: static const char m_cTrainingHeliPilot_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcTrainingHeliPilotClass;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: cTrainingHeliPilot(const AI::cTrainingHeliPilot&);
  public: cTrainingHeliPilot(GOM::cObjectPrototype*);
  public: virtual void OnEnter();
  public: virtual void OnExit();
  public: virtual void Notify(AI::cAIEvent*);
  public: virtual void Update(float);
  public: virtual void DemoteDelivery();
  public: virtual void ActiveAgentComplete(unsigned int);
  protected: virtual void RenderDebugInfo();
  protected: virtual void EnterState(char);
  protected: virtual void ExitState(char);
  protected: virtual void UpdateInbound();
  protected: virtual void UpdateHover();
  protected: virtual void UpdateDroppingOff();
  protected: virtual void UpdateWaitingForExit();
  protected: virtual void UpdateAligningToTarget();
  protected: virtual void UpdateAwaitDrop();
  protected: virtual void EnterHover();
  protected: virtual void EnterDroppingOff();
  protected: virtual void EnterWaitingForExit();
  protected: virtual void EnterAligningToTarget();
  protected: virtual void EnterAwaitDrop();
  protected: void LinkToMission();
  private: AI::cTrainingHeliPilot::cPilotTrainingPrototype& RetTHPPrototype();
  public: virtual ~cTrainingHeliPilot();
  public: AI::cTrainingHeliPilot& operator=(const AI::cTrainingHeliPilot&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
