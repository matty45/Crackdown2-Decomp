
class AI::cPKDropPilot : public AI::cPilotBase { /* Size=0x180 */
  /* 0x0000: fields for AI::cPilotBase */
  /* 0x0170 */ private: AI::cTacticalObjective* m_pTOMission;
  public: static const char* pcPKDropPilotClassID;
  public: static const char m_cPKDropPilot_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcPKDropPilotClass;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: cPKDropPilot(const AI::cPKDropPilot&);
  public: cPKDropPilot(GOM::cObjectPrototype*);
  public: virtual void OnEnterReplicatedState(unsigned char);
  public: virtual void OnEnter();
  public: virtual void SetupAfterReplication();
  public: virtual void OnExit();
  public: virtual void OnDied(CHARACTER::cCharacter*, AI::cAIEvent*);
  public: virtual void DemoteDelivery();
  protected: virtual void RenderDebugInfo();
  protected: virtual void EnterState(char);
  protected: virtual void ExitState(char);
  protected: virtual void EnterDrop();
  protected: virtual void ExitDrop();
  protected: virtual void UpdateDrop();
  private: AI::cPilotBase::cPilotBasePrototype& RetPKDPrototype();
  public: virtual ~cPKDropPilot();
  public: AI::cPKDropPilot& operator=(const AI::cPKDropPilot&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
