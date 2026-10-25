
class AI::cVehicleCollectionBehaviour : public AI::cPilotBase { /* Size=0x190 */
  /* 0x0000: fields for AI::cPilotBase */
  /* 0x0170 */ private: Fun_Runtime::Vec3 m_vOriginalPos;
  /* 0x0180 */ private: Fun_Runtime::cSafeDeletablePointer<PHYSICS::cDynamicBody> m_pCollectionObj;
  public: static const char* pcVehicleCollectionBehaviourClassID;
  public: static const char m_cVehicleCollectionBehaviour_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcVehicleCollectionBehaviourClass;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: cVehicleCollectionBehaviour(const AI::cVehicleCollectionBehaviour&);
  public: cVehicleCollectionBehaviour(GOM::cObjectPrototype*);
  public: virtual void OnEnterReplicatedState(unsigned char);
  public: virtual void OnEnter();
  public: virtual void SetupAfterReplication();
  public: virtual void OnExit();
  public: virtual void OnDied(CHARACTER::cCharacter*, AI::cAIEvent*);
  public: virtual void DemoteDelivery();
  public: void GetHoverPos();
  public: virtual void ActiveAgentComplete(unsigned int);
  protected: virtual void RenderDebugInfo();
  protected: virtual void EnterState(char);
  protected: virtual void ExitState(char);
  protected: virtual void Update(float);
  protected: virtual void UpdateInbound();
  protected: virtual void UpdateHover();
  protected: virtual void UpdateAligningToTarget();
  protected: virtual void EnterInbound();
  protected: virtual void EnterOutbound();
  protected: virtual void EnterHover();
  protected: virtual void EnterAligningToTarget();
  protected: void GetCollectionVehicle();
  protected: void CheckCollectionVehicleValidity();
  protected: void UpdateLegStateForTargetVehicle(PHYSICS::cDynamicBody*, Vehicle::cHelicopter*);
  private: AI::cPilotBase::cPilotBasePrototype& RetVCPrototype();
  public: virtual ~cVehicleCollectionBehaviour();
  public: AI::cVehicleCollectionBehaviour& operator=(const AI::cVehicleCollectionBehaviour&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
