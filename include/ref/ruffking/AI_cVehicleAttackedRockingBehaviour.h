
class AI::cVehicleAttackedRockingBehaviour : public AI::NPCBehaviour { /* Size=0x110 */
  /* 0x0000: fields for AI::NPCBehaviour */
  /* 0x0100 */ private: AI::cVehicleAttackedRockingBehaviour::eSubState m_eState;
  /* 0x0104 */ private: float m_fCurrentTimer;
  public: static const char* pcVehicleAttackedRockingBehaviourClassID;
  public: static const char m_cVehicleAttackedRockingBehaviour_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcVehicleAttackedRockingBehaviourClass;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: cVehicleAttackedRockingBehaviour(const AI::cVehicleAttackedRockingBehaviour&);
  public: cVehicleAttackedRockingBehaviour(GOM::cObjectPrototype*);
  public: virtual void OnEnter();
  public: virtual void OnExit();
  public: virtual void Update(float);
  public: virtual void ChangeState(AI::cVehicleAttackedRockingBehaviour::eSubState);
  public: virtual void EnterState(AI::cVehicleAttackedRockingBehaviour::eSubState);
  public: virtual void ExitState();
  public: void OnUpdateRocking(float);
  public: void RockDrivenVehicle();
  public: virtual void RenderDebugInfo();
  private: AI::cVehicleAttackedRockingBehaviour::cVehicleAttackedRockingBehaviourPrototype& RetRockingPrototype();
  public: virtual ~cVehicleAttackedRockingBehaviour();
  public: AI::cVehicleAttackedRockingBehaviour& operator=(const AI::cVehicleAttackedRockingBehaviour&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
