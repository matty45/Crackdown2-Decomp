
class AI::cAmbientWanderAttackBehaviour : public AI::cAmbientTrafficBehaviour { /* Size=0x180 */
  /* 0x0000: fields for AI::cAmbientTrafficBehaviour */
  /* 0x0170 */ protected: unsigned int m_nLastWakeUpTime;
  /* 0x0174 */ protected: unsigned int m_nCurrentWakeUpInterval;
  /* 0x0178 */ protected: unsigned int m_nLastCrowdTargettingTime;
  /* 0x017c */ protected: AI::cFauxTarget* m_pFauxCrowdTarget;
  public: static const char* pcAmbientWanderAttackBehaviourClassID;
  public: static const char m_cAmbientWanderAttackBehaviour_ClassName[0];
  public: static const Fun_Runtime::cClass* ms_pcAmbientWanderAttackBehaviourClass;
  
  public: virtual const char* RetClassName() const;
  public: virtual void Destruct();
  public: virtual const Fun_Runtime::cClass& RetClass() const;
  public: virtual bool IsA(const Fun_Runtime::cClass&) const;
  public: cAmbientWanderAttackBehaviour(const AI::cAmbientWanderAttackBehaviour&);
  public: cAmbientWanderAttackBehaviour(GOM::cObjectPrototype*);
  public: virtual ~cAmbientWanderAttackBehaviour();
  public: virtual void OnEnter();
  public: virtual void OnDetectedEnemy(CHARACTER::cCharacter*, const Fun_Runtime::Vec3&, AI::cAIEvent*);
  public: virtual void OnEnterSubStateDrivingTraffic();
  public: virtual void UpdateDrivingTraffic(float);
  public: bool FindCrowdTargetPos(Fun_Runtime::Vec3&);
  public: void TryScareCrowd();
  protected: AI::cAmbientWanderAttackBehaviour::cAmbientWanderAttackBehaviourPrototype* RetAWABPrototype();
  public: AI::cAmbientWanderAttackBehaviour& operator=(const AI::cAmbientWanderAttackBehaviour&);
  public: virtual void* __vecDelDtor(unsigned int);
  
  public: static const char* RetRWSClassName();
  public: static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket&, bool);
  public: static RWS::CAttributeHandler* SpawnFromPrototype(GOM::cObjectPrototype*, void*);
  public: static Fun_Runtime::cClass& StaticCreateClass();
  public: static const Fun_Runtime::cClass& StaticRetClass();
};
