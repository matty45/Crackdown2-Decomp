
class AI::EquipmentDropBehaviour : public AI::cPilotBase { /* Size=0x170 */
  /* 0x0000: fields for AI::cPilotBase */
  public: static const char* pEquipmentDropBehaviourClassID;
  public: static const char m_EquipmentDropBehaviour_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pEquipmentDropBehaviourClass;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: EquipmentDropBehaviour(const AI::EquipmentDropBehaviour&);
  public: EquipmentDropBehaviour(GOM::cObjectPrototype*);
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
  protected: virtual void EnterHover();
  protected: virtual void UpdateInbound();
  private: AI::cPilotBase::cPilotBasePrototype& RetEDPrototype();
  public: virtual ~EquipmentDropBehaviour();
  public: AI::EquipmentDropBehaviour& operator=(const AI::EquipmentDropBehaviour&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
